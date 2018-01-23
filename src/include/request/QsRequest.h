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

#pragma once

#include "QsSdkOption.h"
#include "QsErrors.h"
#include "QsConfig.h"
#include "signer/QsSigner.h"
#include "HttpCommon.h"
#include "http/HttpClient.h"
#include "http/HttpRequest.h"
#include "http/HttpResponse.h"
#include "Types.h"
#include "request/QsRequestBuilder.h"
#include "request/QsResponseUnparker.h"
#include <memory>

using namespace QingStor;
using namespace QingStor::Http;

class Operation
{
public:
    Operation(QsConfig *pConfig, Properties properties, std::string strApiName, HttpMethod strReqMethod, std::string strReqURI) : m_pConfig(pConfig), m_properties(properties), m_strApiName(strApiName),
        m_strReqMethod(strReqMethod), m_strReqURI(strReqURI) {};

    virtual ~Operation() {};

    inline const QsConfig *GetConfig() const
    {
        return m_pConfig;
    };
    inline const Properties GetProperties() const
    {
        return m_properties;
    };
    inline const std::string GetApiName() const
    {
        return m_strApiName;
    }
    inline const HttpMethod GetReqMethod() const
    {
        return m_strReqMethod;
    }

    inline const std::string GetReqURI() const
    {
        return m_strReqURI;
    };

private:
    QsConfig *m_pConfig;
    Properties m_properties;
    std::string m_strApiName;
    HttpMethod m_strReqMethod;
    std::string m_strReqURI;
};

class QS_SDK_API QsRequest
{
public:
    QsRequest(const Operation &operation, QsRequestBuilder *pReqBuilder, QsResponseUnparker *pRespUnparker)
        : m_operation(operation),
          m_signer(operation.GetConfig()->accessKeyId, operation.GetConfig()->secretAccessKey),
          m_pReqBuilder(pReqBuilder), m_pRespUnpacker(pRespUnparker),
          m_httpClient(operation.GetConfig()->timeOutPeriod),
          httpRequest(NULL),httpResponse(NULL) {};

    virtual ~QsRequest() {};

    QsError GetResponse();

protected:
    Operation m_operation;
    QingStor::QsSigner m_signer;
    QsRequestBuilder *m_pReqBuilder;
    QsResponseUnparker *m_pRespUnpacker;
    HttpClient m_httpClient;
    HttpRequest* httpRequest;
    HttpResponse* httpResponse;

    HttpRequest* BuildHttpRequest();
    QsError SendReqAndWait4Resp();
    void AddHeadersToRequest( Http::HttpRequest * httpRequest);
    void AddContentBodyToRequest( Http::HttpRequest * httpRequest);
    void AddQueryStringParameters( Http::HttpRequest * httpRequest);
    QsError PareseResponse( HttpResponse* httpResponse);
};
