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

#include "plog/Log.h"
#include "http/HttpClient.h"
#include "HttpCommon.h"
#include "http/HttpRequest.h"
#include "http/HttpResponse.h"
#include "StringUtils.h"
#include <algorithm>

using namespace QingStor;
using namespace QingStor::Http;
using namespace QingStor::Utils;

struct QsWriteCallbackContext
{
    QsWriteCallbackContext(const HttpClient *client,
                           HttpRequest *request,
                           HttpResponse *response) : m_client(client),
        m_request(request),
        m_response(response),
        m_numBytesResponseReceived(0) {}

    const HttpClient *m_client;
    HttpRequest *m_request;
    HttpResponse *m_response;
    int64_t m_numBytesResponseReceived;
};

struct QsReadCallbackContext
{
    QsReadCallbackContext(const HttpClient *client, HttpRequest *request) : m_client(client), m_request(request), m_hasBeenRead(0) {}
    const HttpClient *m_client;
    HttpRequest *m_request;
    size_t m_hasBeenRead;
};

void SetOptCodeForHttpMethod(CURL *requestHandle, const HttpRequest &request)
{
    switch (request.GetMethod())
    {
    case HTTP_GET:
        curl_easy_setopt(requestHandle, CURLOPT_HTTPGET, 1L);
        break;
    case HTTP_PUT:
        if (!request.HasHeader(CONTENT_LENGTH_HEADER) || request.GetHeaderValue(CONTENT_LENGTH_HEADER) == "0")
        {
            curl_easy_setopt(requestHandle, CURLOPT_CUSTOMREQUEST, "PUT");
        }
        else
        {
            curl_easy_setopt(requestHandle, CURLOPT_PUT, 1L);
        }
        break;
    case HTTP_POST:
        if (!request.HasHeader(CONTENT_LENGTH_HEADER) || request.GetHeaderValue(CONTENT_LENGTH_HEADER) == "0")
        {
            curl_easy_setopt(requestHandle, CURLOPT_CUSTOMREQUEST, "POST");
        }
        else
        {
            curl_easy_setopt(requestHandle, CURLOPT_POST, 1L);
        }
        break;
    case HTTP_HEAD:
        curl_easy_setopt(requestHandle, CURLOPT_HTTPGET, 1L);
        curl_easy_setopt(requestHandle, CURLOPT_NOBODY, 1L);
        break;
    case HTTP_DELETE:
        curl_easy_setopt(requestHandle, CURLOPT_CUSTOMREQUEST, "DELETE");
        break;
    case HTTP_PATCH:
        if (!request.HasHeader(CONTENT_LENGTH_HEADER) || request.GetHeaderValue(CONTENT_LENGTH_HEADER) == "0")
        {
            curl_easy_setopt(requestHandle, CURLOPT_CUSTOMREQUEST, "PATCH");
        }
        else
        {
            curl_easy_setopt(requestHandle, CURLOPT_POST, 1L);
            curl_easy_setopt(requestHandle, CURLOPT_CUSTOMREQUEST, "PATCH");
        }
        break;
    default:
        curl_easy_setopt(requestHandle, CURLOPT_CUSTOMREQUEST, "GET");
        break;
    }
}

void HttpClient::CreateGlobaleCurlPool()
{
    gCurlPool = new CurlHandlerPool(gCurlPoolSize);
    if (!gCurlPool->Init())
    {
        LOG_FATAL << "Create CurlPool faild...";
    }
}

void HttpClient::DestroyGlobaleCurlPool()
{
    if(!gCurlPool)
    {
        return;
    }
    if(!gCurlPool->Destroy())
    {
        LOG_FATAL << "Festroy CurlPool faild...";
    }
    delete gCurlPool;
    gCurlPool = NULL;
}

HttpResponse * HttpClient::SendRequest(HttpRequest *request) const
{
    std::string url = request->GetURIString();
    LOG_DEBUG << "Making request to " << url;
    struct curl_slist *headers = NULL;
    std::stringstream headerStream;
    HeaderValueCollection requestHeaders = request->GetHeaders();
    for(HeaderValueCollection::iterator it = requestHeaders.begin(); it != requestHeaders.end(); it++)
    {
        headerStream.str("");
        headerStream << it->first << ":" << it->second;
        std::string headerString = headerStream.str();
        LOG_DEBUG << "Including header:" << headerString;
        headers = curl_slist_append(headers, headerString.c_str());
    }
    headers = curl_slist_append(headers, "transfer-encoding:");
    if (!request->HasHeader(Http::CONTENT_LENGTH_HEADER))
    {
        headers = curl_slist_append(headers, "content-length:");
    }
    if (!request->HasHeader(Http::CONTENT_TYPE_HEADER))
    {
        headers = curl_slist_append(headers, "content-type:");
    }
    HttpResponse * response = NULL;
    CURL * connectionHandle  = gCurlPool->GetHandler();
    if (connectionHandle)
    {
        curl_easy_reset(connectionHandle);
        LOG_DEBUG << "Obtained connection handle: " << connectionHandle;
        if (headers)
        {
            curl_easy_setopt(connectionHandle, CURLOPT_HTTPHEADER, headers);
        }
        response = new HttpResponse();
        QsWriteCallbackContext writeContext(this, request, response);
        QsReadCallbackContext readContext(this, request);
        SetOptCodeForHttpMethod(connectionHandle, *request);
        curl_easy_setopt(connectionHandle, CURLOPT_TCP_NODELAY, 1L);
        curl_easy_setopt(connectionHandle, CURLOPT_NOSIGNAL, 1L);
        curl_easy_setopt(connectionHandle, CURLOPT_TIMEOUT, 600L);
        if(m_timeOutPeriod > 0)
        {
            curl_easy_setopt(connectionHandle, CURLOPT_CONNECTTIMEOUT, m_timeOutPeriod);
        }
        else
        {
            curl_easy_setopt(connectionHandle, CURLOPT_CONNECTTIMEOUT, 3);
        }
        curl_easy_setopt(connectionHandle, CURLOPT_URL, url.c_str());
        curl_easy_setopt(connectionHandle, CURLOPT_WRITEFUNCTION, &HttpClient::WriteData);
        curl_easy_setopt(connectionHandle, CURLOPT_WRITEDATA, &writeContext);
        curl_easy_setopt(connectionHandle, CURLOPT_HEADERFUNCTION, &HttpClient::WriteHeader);
        curl_easy_setopt(connectionHandle, CURLOPT_HEADERDATA, response);
        curl_easy_setopt(connectionHandle, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(connectionHandle, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(connectionHandle, CURLOPT_FOLLOWLOCATION, 0L);
        // If config enable Curl dbg option, print to stdin.
        if (plog::get<PLOG_DEFAULT_INSTANCE>() && plog::get<PLOG_DEFAULT_INSTANCE>()->checkSeverity(plog::verbose))
        {
            curl_easy_setopt(connectionHandle, CURLOPT_VERBOSE, true);
        }
        if (request->GetContentBody())
        {
            curl_easy_setopt(connectionHandle, CURLOPT_READFUNCTION, &HttpClient::ReadBody);
            curl_easy_setopt(connectionHandle, CURLOPT_READDATA, &readContext);
        }
        CURLcode curlResponseCode = curl_easy_perform(connectionHandle);
        if (curlResponseCode != CURLE_OK)
        {
            if(response)
            {
                response->ReleaseResponseBody();
                delete response;
                response = NULL;
            }
            LOG_DEBUG << "Curl returned error code: " << curlResponseCode;
        }
        else
        {
            long responseCode;
            curl_easy_getinfo(connectionHandle, CURLINFO_RESPONSE_CODE, &responseCode);
            response->SetResponseCode(static_cast<HttpResponseCode>(responseCode));
            LOG_DEBUG << "Returned http response code: " << responseCode;
            char *contentType = NULL;
            curl_easy_getinfo(connectionHandle, CURLINFO_CONTENT_TYPE, &contentType);
            if (contentType)
            {
                response->SetContentType(contentType);
                LOG_DEBUG << "Returned content type: " << contentType;
            }
            if (request->GetMethod() != HTTP_HEAD &&
                    response->HasHeader(CONTENT_LENGTH_HEADER))
            {
                const std::string &contentLength = response->GetHeader(CONTENT_LENGTH_HEADER);
                int64_t numBytesResponseReceived = writeContext.m_numBytesResponseReceived;
                LOG_DEBUG << "Response content-length header: " << contentLength;
                LOG_DEBUG << "Response body length: " << numBytesResponseReceived;
                if (StringUtils::ConvertToInt64(contentLength.c_str()) != numBytesResponseReceived)
                {
                    if(response)
                    {
                        response->ReleaseResponseBody();
                        delete response;
                        response = NULL;
                    }
                    LOG_DEBUG << "Response body length doesn't match the content-length header.";
                }
            }
            LOG_DEBUG << "Releasing curl handle: " << connectionHandle;
        }
        gCurlPool->ReleaseHandler(connectionHandle);
        connectionHandle = NULL;
        //go ahead and flush the response body stream
        if (response)
        {
            response->GetResponseBody()->flush();
        }
    }
    if (headers)
    {
        curl_slist_free_all(headers);
    }
    return response;
}

size_t HttpClient::WriteData(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    if (ptr)
    {
        QsWriteCallbackContext *context = reinterpret_cast<QsWriteCallbackContext *>(userdata);
        HttpResponse *response = context->m_response;
        size_t sizeToWrite = size * nmemb;
        response->GetResponseBody()->write(ptr, static_cast<std::streamsize>(sizeToWrite));
        LOG_DEBUG << sizeToWrite << " bytes written to response.";
        context->m_numBytesResponseReceived += sizeToWrite;
        return sizeToWrite;
    }
    return 0;
}

size_t HttpClient::WriteHeader(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    if (ptr)
    {
        HttpResponse *response = (HttpResponse *)userdata;
        std::string headerLine(ptr);
        std::vector<std::string> keyValuePair = StringUtils::Split(headerLine, ':');
        if (keyValuePair.size() > 1)
        {
            std::string headerName = keyValuePair[0];
            headerName = StringUtils::Trim(headerName.c_str());
            std::string headerValue = headerLine.substr(headerName.length() + 1).c_str();
            headerValue = StringUtils::Trim(headerValue.c_str());
            response->AddHeader(headerName, headerValue);
        }
        return size * nmemb;
    }
    return 0;
}

size_t HttpClient::ReadBody(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    QsReadCallbackContext *context = reinterpret_cast<QsReadCallbackContext *>(userdata);
    if (context == NULL)
    {
        return 0;
    }
    HttpRequest *request = context->m_request;
    std::iostream * ioStream = request->GetContentBody();
    if (ioStream != NULL && size * nmemb)
    {
        size_t amountToRead = size * nmemb;
        size_t needToRead = 0;
        std::string contentLength = request->GetHeaderValue("Content-Length");
        if ("" != contentLength)
        {
            needToRead = Utils::StringUtils::ConvertToInt64(contentLength.c_str()) - context->m_hasBeenRead;
        }
        if (0 != amountToRead && needToRead < amountToRead)
        {
            amountToRead = needToRead;
        }
        ioStream->read(ptr, amountToRead);
        size_t amountRead = static_cast<size_t>(ioStream->gcount());
        context->m_hasBeenRead += amountRead;
        return amountRead;
    }
    return 0;
}
