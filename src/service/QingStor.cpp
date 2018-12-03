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

#include "QingStor.h"
#include "Bucket.h"
#include "QsConfig.h"
#include "request/QsRequest.h"
#include "http/HttpResponse.h"
#include "external/plog/Log.h"
#include "external/json/json.h"

using namespace QingStor;

void QingStor::InitializeSDK(const SDKOptions & options)
{
    //Init log systom
    LOG_DEBUG << "Initializing SDK...";
    std::string logName = options.logPath;
    logName += "qingstor_sdk_log.txt";
    plog::init((plog::Severity) options.logLevel, logName.c_str(), 1000000, 5);
    if (options.initAndCleanupCurl)
    {
        //InitHttp
        curl_global_init(CURL_GLOBAL_ALL);
        LOG_DEBUG << "curl_global_init done";
    }
    HttpClient::CreateGlobaleCurlPool();
}

void QingStor::ShutdownSDK(const SDKOptions & options)
{
    LOG_DEBUG << "Shutdowning SDK...";
    if (options.initAndCleanupCurl)
    {
        //InitHttp
        curl_global_cleanup();
        LOG_DEBUG << "curl_global_cleanup done";
    }
    HttpClient::DestroyGlobaleCurlPool();
}

QingStorService::QingStorService(const QsConfig & qsConfig):m_qsConfig(qsConfig)
{
}

// +--------------------------------------------------------------------
// |           RequestBuilderSource and ResponseUnparkerSource
// +--------------------------------------------------------------------
class ListBucketsBuilder:public QsDefaultRequestBuilder < ListBucketsInput >
{
public:
    ListBucketsBuilder(ListBucketsInput * input):QsDefaultRequestBuilder <
        ListBucketsInput > (input)
    {
    };

    virtual ~ ListBucketsBuilder()
    {
    };

    virtual bool CkeckIfInputIsVaild()
    {
        return m_input->CheckIfInputIsVaild();
    };
    virtual Http::HeaderValueCollection GetHeaderValueCollection();
};

// ListBucketsRequest GetRequestSpecificHeaders.
Http::HeaderValueCollection ListBucketsBuilder::GetHeaderValueCollection()
{
    //TO DO;
    Http::HeaderValueCollection headers;
    std::stringstream ss;
    std::vector < std::string >::iterator it;
    if (m_input->IsPropHasBeenSet(SETTING_INPUT_LIST_BUCKETS_LOCATION_FLAG))
    {
        ss << m_input->GetLocation();
        headers.insert(Http::HeaderValuePair("Location", ss.str()));
        ss.str("");
    }
    return headers;
}

class ListBucketsUnparker:public QsDefaultResponseUnparker < ListBucketsOutput >
{
public:
    ListBucketsUnparker(ListBucketsOutput * output):QsDefaultResponseUnparker <
        ListBucketsOutput > (output)
    {
    };

    virtual ~ ListBucketsUnparker()
    {
    };

    virtual bool CkeckIfOutputIsVaild()
    {
        return m_output->IsVaild();
    };

    virtual bool CheckIfResponseExpected(Http::HttpResponseCode responseCode)
    {
        m_output->SetResponseCode(responseCode);
        // Expected response codes.
        int expectedRespCode[1] = { 200, };
        bool isExpected = false;
        for (int i = 0; i < 1; i++)
        {
            if (expectedRespCode[i] == responseCode)
            {
                isExpected = true;
                break;
            }
        }
        return isExpected;
    };
    virtual void ParseResponseBody(std::iostream * responseBody);
};

void ListBucketsUnparker::ParseResponseBody(std::iostream * responseBody)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(*responseBody, jsonContent);
    if (jsonContent.isMember("buckets"))
    {
        std::vector < BucketType > vecBuckets;
        for (unsigned i = 0; i < jsonContent["buckets"].size(); ++i)
        {
            vecBuckets.push_back(jsonContent["buckets"][i].toStyledString());
        }
        m_output->SetBuckets(vecBuckets);
    }
    if (jsonContent.isMember("count"))
    {
        m_output->SetCount(jsonContent["count"].asInt());
    }
    m_bNeedReleaseBody = true;
}

// +--------------------------------------------------------------------
// |           SDK API Operation Source
// +--------------------------------------------------------------------

QsError QingStorService::ListBuckets(ListBucketsInput & input,
                                     ListBucketsOutput & output)
{
    Properties properties(m_properties);
    Operation operation(&m_qsConfig, properties, "Get Service", HTTP_GET, "/");
    ListBucketsBuilder bulider(&input);
    ListBucketsUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}
