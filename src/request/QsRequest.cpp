// +-------------------------------------------------------------------------
// | Copyright (C) 2017 Yunify, Inc.
// +-------------------------------------------------------------------------
// | Licensed under the Apache License, Version 2.0 (the "License");
// | you may not use this work except in compliance with the License.
// | You may obtain a copy of the License in the LICENSE file, or at:
// |
// | http://www.apache.org/licenses/LICENSE-2.0
// |
// | Unless required by applicable law or agreed to in writing, software
// | distributed under the License is distributed on an "AS IS" BASIS,
// | WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// | See the License for the specific language governing permissions and
// | limitations under the License.
// +-------------------------------------------------------------------------

#ifdef _WIN32
#define sleep(x) Sleep((x)*1000)
#include <memory>
#else //linux
#include <memory.h>
#endif

#include "plog/Log.h"
#include "QsErrors.h"
#include "http/HttpRequest.h"
#include "HttpCommon.h"
#include "http/HttpResponse.h"
#include "request/QsRequest.h"
#include <iostream>

using namespace QingStor::Utils;
using namespace QingStor::Http;

static const char *QS_REQUEST_HEADER_REQUESTID = "X-Qs-Request-Id";

static const int countToEncode = 3;
static std::string headersToEncode[countToEncode] =
{
    "X-QS-Fetch-Source",
    "X-QS-Copy-Source",
    "X-QS-Move-Source",
};

void QsRequest::AddHeadersToRequest(QingStor::Http::HttpRequest* httpRequest)
{
    Http::HeaderValueCollection headerValues = m_pReqBuilder->GetHeaderValueCollection();
    for(HeaderValueCollection::iterator it = headerValues.begin(); it != headerValues.end(); it++)
    {
        if ("" == it->second)
        {
            continue;
        }
        bool bInHeadersToEncode = false;
        for(int i =0; i < countToEncode; i++)
        {
            if (it->first == headersToEncode[i])
            {
                bInHeadersToEncode = true;
                break;
            }
        }
        // Headers in "headersToEncode", need URL transcoding.
        if(bInHeadersToEncode)
        {
            httpRequest->SetHeaderValue(it->first, URI::URLEncodePath(it->second));
        }
        else
        {
            httpRequest->SetHeaderValue(it->first, it->second.c_str());
        }
    }
}

void QsRequest::AddContentBodyToRequest(QingStor::Http::HttpRequest* httpRequest)
{
    std::iostream* requestStream = NULL;
    requestStream = m_pReqBuilder->GetRequestBody();
    httpRequest->AddContentBody(requestStream);
    //If there is no body, content length should be 0.
    if (!requestStream)
    {
        LOG_DEBUG << "No content body, set content-length header to 0.";
        if (httpRequest->GetMethod() == HTTP_POST || httpRequest->GetMethod() == HTTP_PUT)
        {
            httpRequest->SetHeaderValue(Http::CONTENT_LENGTH_HEADER, "0");
        }
        else
        {
            httpRequest->DeleteHeader(Http::CONTENT_LENGTH_HEADER);
        }
    }
    else if (!httpRequest->HasHeader(Http::CONTENT_LENGTH_HEADER))
    {
        LOG_DEBUG << "Found body, but content-length has not been set, attempting to compute content-length.";
        requestStream->seekg(0, requestStream->end);
        size_t streamSize = requestStream->tellg();
        requestStream->seekg(0, requestStream->beg);
        std::stringstream ss;
        ss << streamSize;
        httpRequest->SetContentLength(ss.str());
    }
}

void QsRequest::AddQueryStringParameters(HttpRequest* httpRequest)
{
    Http::QueryParamCollection queryParameters = m_pReqBuilder->GetQueryParamCollection();
    for(QueryParamCollection::iterator it = queryParameters.begin(); it != queryParameters.end(); it++)
    {
        httpRequest->SetQueryStringParameter(it->first.c_str(), it->second);
    }
}

HttpRequest* QsRequest::BuildHttpRequest()
{
    Properties props = m_operation.GetProperties();
    const QsConfig *pConfig = m_operation.GetConfig();
    std::string strZone = props.Zone;
    std::string strBucketName = props.BucketName;
    std::string strObjectKey = props.ObjectKey;
    std::stringstream endpoint;
    endpoint << pConfig->protocol << "://";
    if (strZone != "")
    {
        endpoint << strZone << ".";
    }
    endpoint << pConfig->host;
    if (pConfig->port != 443 && pConfig->port != 80)
    {
        endpoint << ":" << pConfig->port;
    }
    std::string path = m_operation.GetReqURI();
    std::string queryString;
    size_t queryBegin = path.find('?');
    if (queryBegin != std::string::npos)
    {
        queryString = path.substr(queryBegin, path.length());
        path = path.substr(0, queryBegin);
    }
    StringUtils::Replace(path, "<bucket-name>", strBucketName.c_str());
    StringUtils::Replace(path, "<object-key>", strObjectKey.c_str());
    StringUtils::Replace(path, "<zone>", strZone.c_str());
    URI uri(endpoint.str(), path, queryString);
    HttpRequest* httpRequest = new HttpRequest(m_operation.GetReqMethod(), uri);
    AddQueryStringParameters(httpRequest);
    //do headers first since the request likely will set content-length as it's own header.
    AddHeadersToRequest(httpRequest);
    //would not compute content Md5
    AddContentBodyToRequest(httpRequest);
    return httpRequest;
}

QsError QsRequest::PareseResponse(HttpResponse* httpResponse)
{
    QsError reqErr = QS_ERR_NO_ERROR;
    if (m_pRespUnpacker)
    {
        // check if response code is in line with expectation.
        if(!m_pRespUnpacker->CheckIfResponseExpected(httpResponse->GetResponseCode()))
        {
            reqErr = QS_ERR_UNEXCEPTED_RESPONSE;
            m_pRespUnpacker->ParseResponseErrInfo(httpResponse->GetResponseBody());
        }
        else
        {
            m_pRespUnpacker->ParseResponseHeaders(httpResponse->GetHeaders());
            m_pRespUnpacker->ParseResponseBody(httpResponse->GetResponseBody());
            m_pRespUnpacker->ParseRequestID(httpResponse->GetHeader(QS_REQUEST_HEADER_REQUESTID));
        }
    }
    return reqErr;
}

QsError QsRequest::SendReqAndWait4Resp()
{
    QsError reqErr = QS_ERR_NO_ERROR;
    long maxRetries = m_operation.GetConfig()->connectionRetries;
    long retries = 0;
    // 1.build request content
    httpRequest = BuildHttpRequest();
    do
    {
        // 2. sign the request
        reqErr = m_signer.SignRequest(httpRequest);
        if (reqErr != QS_ERR_NO_ERROR)
        {
            LOG_ERROR << "Sign request failed. Returning error.";
            break;
        }
        // 3. send http request and get http response
        std::iostream * reqBodyStream = httpRequest->GetContentBody();
        // record the starting position of the stream, it will be uesd in retry process.
        // we can not suppose retry should begin form zero position.
        size_t startingPosition = 0;
        if(reqBodyStream)
        {
            startingPosition = reqBodyStream->tellg();
        }
        httpResponse = m_httpClient.SendRequest(httpRequest);
        if (httpResponse)
        {
            LOG_DEBUG << "Request successful returning.";
            reqErr = QS_ERR_NO_ERROR;
            break;
        }
        else
        {
            // if request failed, we just retry "maxRetries" times.
            // We  haven't implement the speed limit feature yet, so just sleep 1000ms between each retry
            retries++;
            LOG_WARNING << "Request failed, now attempting again."
                        << "retries :" << retries << "maxRetries :" << maxRetries;
            if (reqBodyStream)
            {
                reqBodyStream->clear();
                reqBodyStream->seekg(startingPosition);
            }
        }
    }
    while (retries < maxRetries);
    if(retries == maxRetries)
    {
        reqErr = QS_ERR_SEND_REQUEST_ERROR;
    }
    if (QS_ERR_NO_ERROR == reqErr)
    {
        LOG_DEBUG << "Get response and begin to parese.";
        // 4.parese the response
        reqErr = PareseResponse(httpResponse);
    }
    else
    {
        LOG_ERROR << "Send request failed. Returning error.";
    }
    return reqErr;
}

QsError QsRequest::GetResponse()
{
    // Ckeck input.
    if (!m_pReqBuilder->CkeckIfInputIsVaild())
    {
        LOG_ERROR << "Some required parameters in request not specified. Returning error.";
        return QS_ERR_NO_REQUIRED_PARAMETER;
    }
    // Send request and wait for response.
    QsError reqErr = SendReqAndWait4Resp();
    // Clean resource.
    if(httpRequest)
    {
        if(m_pReqBuilder->CkeckIfNeedReleaseBody())
        {
            httpRequest->ReleaseResponseBody();
        }
        delete httpRequest;
        httpRequest = NULL;
    }
    if(httpResponse)
    {
        if(m_pRespUnpacker->CkeckIfNeedReleaseBody())
        {
            httpResponse->ReleaseResponseBody();
        }
        delete httpResponse;
        httpResponse = NULL;
    }
    return reqErr;
}