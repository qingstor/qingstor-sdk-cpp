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

#include "Bucket.h"
#include "StringUtils.h"
#include "request/QsRequest.h"
#include "http/HttpResponse.h"
#include "external/json/json.h"
#include <vector>
#include <algorithm>

using namespace QingStor;
using namespace QingStor::Utils;

#ifdef _WIN32
#define GetObject  GetObject
#endif

Bucket::Bucket(const QsConfig & qsConfig, const std::string & strBucketName, const std::string & strZone):m_qsConfig
    (qsConfig)
{
    m_properties.BucketName = strBucketName;
    m_properties.Zone = strZone;
}

// +--------------------------------------------------------------------
// |           RequestBuilderSource and ResponseUnparkerSource
// +--------------------------------------------------------------------
typedef QsDefaultRequestBuilder < DeleteBucketInput > DeleteBucketBuilder;

typedef QsDefaultResponseUnparker < DeleteBucketOutput > DeleteBucketUnparker;

typedef QsDefaultRequestBuilder < DeleteBucketCORSInput >
DeleteBucketCORSBuilder;

typedef QsDefaultResponseUnparker < DeleteBucketCORSOutput >
DeleteBucketCORSUnparker;

typedef QsDefaultRequestBuilder < DeleteBucketExternalMirrorInput >
DeleteBucketExternalMirrorBuilder;

typedef QsDefaultResponseUnparker < DeleteBucketExternalMirrorOutput >
DeleteBucketExternalMirrorUnparker;

typedef QsDefaultRequestBuilder < DeleteBucketPolicyInput >
DeleteBucketPolicyBuilder;

typedef QsDefaultResponseUnparker < DeleteBucketPolicyOutput >
DeleteBucketPolicyUnparker;

class DeleteMultipleObjectsBuilder:public QsDefaultRequestBuilder <
    DeleteMultipleObjectsInput >
{
public:
    DeleteMultipleObjectsBuilder(DeleteMultipleObjectsInput *
                                 input):QsDefaultRequestBuilder <
        DeleteMultipleObjectsInput > (input)
    {
    };

    virtual ~ DeleteMultipleObjectsBuilder()
    {
    };

    virtual bool CkeckIfInputIsVaild()
    {
        return m_input->CheckIfInputIsVaild();
    };
    virtual Http::HeaderValueCollection GetHeaderValueCollection();
    virtual std::iostream * GetRequestBody();
};

// DeleteMultipleObjectsRequest GetRequestSpecificHeaders.
Http::HeaderValueCollection DeleteMultipleObjectsBuilder::
GetHeaderValueCollection()
{
    //TO DO;
    Http::HeaderValueCollection headers;
    std::stringstream ss;
    std::vector < std::string >::iterator it;
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_DELETE_MULTIPLE_OBJECTS_CONTENT_MD5_FLAG))
    {
        ss << m_input->GetContentMD5();
        headers.insert(Http::HeaderValuePair("Content-MD5", ss.str()));
        ss.str("");
    }
    return headers;
}

// DeleteMultipleObjectsRequest GetRequestBody.
std::iostream * DeleteMultipleObjectsBuilder::GetRequestBody()
{
    //TO DO;
    Json::FastWriter jsonWriter;
    Json::Value jsonContent;
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_DELETE_MULTIPLE_OBJECTS_OBJECTS_FLAG))
    {
        Json::Value arrayObjects;
        std::vector < KeyType > objects = m_input->GetObjects();
        for (std::vector < KeyType >::iterator it = objects.begin();
                it != objects.end(); it++)
        {
            Json::Reader jsonReader;
            Json::Value itemJsonValue;
            jsonReader.parse(it->Serialize(), itemJsonValue);
            arrayObjects.append(itemJsonValue);
        }
        jsonContent["objects"] = arrayObjects;
    }
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_DELETE_MULTIPLE_OBJECTS_QUIET_FLAG))
    {
        jsonContent["quiet"] = m_input->GetQuiet();
    }
    m_bNeedReleaseBody = true;
    return new std::stringstream(jsonWriter.write(jsonContent));
}

class DeleteMultipleObjectsUnparker:public QsDefaultResponseUnparker <
    DeleteMultipleObjectsOutput >
{
public:
    DeleteMultipleObjectsUnparker(DeleteMultipleObjectsOutput *
                                  output):QsDefaultResponseUnparker <
        DeleteMultipleObjectsOutput > (output)
    {
    };

    virtual ~ DeleteMultipleObjectsUnparker()
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

void DeleteMultipleObjectsUnparker::ParseResponseBody(std::iostream *
        responseBody)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(*responseBody, jsonContent);
    if (jsonContent.isMember("deleted"))
    {
        std::vector < KeyType > vecDeleted;
        for (unsigned i = 0; i < jsonContent["deleted"].size(); ++i)
        {
            vecDeleted.push_back(jsonContent["deleted"][i].toStyledString());
        }
        m_output->SetDeleted(vecDeleted);
    }
    if (jsonContent.isMember("errors"))
    {
        std::vector < KeyDeleteErrorType > vecErrors;
        for (unsigned i = 0; i < jsonContent["errors"].size(); ++i)
        {
            vecErrors.push_back(jsonContent["errors"][i].toStyledString());
        }
        m_output->SetErrors(vecErrors);
    }
    m_bNeedReleaseBody = true;
}

typedef QsDefaultRequestBuilder < GetBucketACLInput > GetBucketACLBuilder;

class GetBucketACLUnparker:public QsDefaultResponseUnparker <
    GetBucketACLOutput >
{
public:
    GetBucketACLUnparker(GetBucketACLOutput *
                         output):QsDefaultResponseUnparker <
        GetBucketACLOutput > (output)
    {
    };

    virtual ~ GetBucketACLUnparker()
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

void GetBucketACLUnparker::ParseResponseBody(std::iostream * responseBody)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(*responseBody, jsonContent);
    if (jsonContent.isMember("acl"))
    {
        std::vector < ACLType > vecACL;
        for (unsigned i = 0; i < jsonContent["acl"].size(); ++i)
        {
            vecACL.push_back(jsonContent["acl"][i].toStyledString());
        }
        m_output->SetACL(vecACL);
    }
    if (jsonContent.isMember("owner"))
    {
        m_output->SetOwner(jsonContent["owner"].toStyledString());
    }
    m_bNeedReleaseBody = true;
}

typedef QsDefaultRequestBuilder < GetBucketCORSInput > GetBucketCORSBuilder;

class GetBucketCORSUnparker:public QsDefaultResponseUnparker <
    GetBucketCORSOutput >
{
public:
    GetBucketCORSUnparker(GetBucketCORSOutput *
                          output):QsDefaultResponseUnparker <
        GetBucketCORSOutput > (output)
    {
    };

    virtual ~ GetBucketCORSUnparker()
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

void GetBucketCORSUnparker::ParseResponseBody(std::iostream * responseBody)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(*responseBody, jsonContent);
    if (jsonContent.isMember("cors_rules"))
    {
        std::vector < CORSRuleType > vecCORSRules;
        for (unsigned i = 0; i < jsonContent["cors_rules"].size(); ++i)
        {
            vecCORSRules.push_back(jsonContent["cors_rules"][i].
                                   toStyledString());
        }
        m_output->SetCORSRules(vecCORSRules);
    }
    m_bNeedReleaseBody = true;
}

typedef QsDefaultRequestBuilder < GetBucketExternalMirrorInput >
GetBucketExternalMirrorBuilder;

class GetBucketExternalMirrorUnparker:public QsDefaultResponseUnparker <
    GetBucketExternalMirrorOutput >
{
public:
    GetBucketExternalMirrorUnparker(GetBucketExternalMirrorOutput *
                                    output):QsDefaultResponseUnparker <
        GetBucketExternalMirrorOutput > (output)
    {
    };

    virtual ~ GetBucketExternalMirrorUnparker()
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

void GetBucketExternalMirrorUnparker::ParseResponseBody(std::iostream *
        responseBody)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(*responseBody, jsonContent);
    if (jsonContent.isMember("source_site"))
    {
        m_output->SetSourceSite(jsonContent["source_site"].asString());
    }
    m_bNeedReleaseBody = true;
}

typedef QsDefaultRequestBuilder < GetBucketPolicyInput > GetBucketPolicyBuilder;

class GetBucketPolicyUnparker:public QsDefaultResponseUnparker <
    GetBucketPolicyOutput >
{
public:
    GetBucketPolicyUnparker(GetBucketPolicyOutput *
                            output):QsDefaultResponseUnparker <
        GetBucketPolicyOutput > (output)
    {
    };

    virtual ~ GetBucketPolicyUnparker()
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

void GetBucketPolicyUnparker::ParseResponseBody(std::iostream * responseBody)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(*responseBody, jsonContent);
    if (jsonContent.isMember("statement"))
    {
        std::vector < StatementType > vecStatement;
        for (unsigned i = 0; i < jsonContent["statement"].size(); ++i)
        {
            vecStatement.push_back(jsonContent["statement"][i].
                                   toStyledString());
        }
        m_output->SetStatement(vecStatement);
    }
    m_bNeedReleaseBody = true;
}

typedef QsDefaultRequestBuilder < GetBucketStatisticsInput >
GetBucketStatisticsBuilder;

class GetBucketStatisticsUnparker:public QsDefaultResponseUnparker <
    GetBucketStatisticsOutput >
{
public:
    GetBucketStatisticsUnparker(GetBucketStatisticsOutput *
                                output):QsDefaultResponseUnparker <
        GetBucketStatisticsOutput > (output)
    {
    };

    virtual ~ GetBucketStatisticsUnparker()
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

void GetBucketStatisticsUnparker::ParseResponseBody(std::iostream *
        responseBody)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(*responseBody, jsonContent);
    if (jsonContent.isMember("count"))
    {
        m_output->SetCount(jsonContent["count"].asInt64());
    }
    if (jsonContent.isMember("created"))
    {
        m_output->SetCreated(jsonContent["created"].asString());
    }
    if (jsonContent.isMember("location"))
    {
        m_output->SetLocation(jsonContent["location"].asString());
    }
    if (jsonContent.isMember("name"))
    {
        m_output->SetName(jsonContent["name"].asString());
    }
    if (jsonContent.isMember("size"))
    {
        m_output->SetSize(jsonContent["size"].asInt64());
    }
    if (jsonContent.isMember("status"))
    {
        m_output->SetStatus(jsonContent["status"].asString());
    }
    if (jsonContent.isMember("url"))
    {
        m_output->SetURL(jsonContent["url"].asString());
    }
    m_bNeedReleaseBody = true;
}

typedef QsDefaultRequestBuilder < HeadBucketInput > HeadBucketBuilder;

typedef QsDefaultResponseUnparker < HeadBucketOutput > HeadBucketUnparker;

class ListMultipartUploadsBuilder:public QsDefaultRequestBuilder <
    ListMultipartUploadsInput >
{
public:
    ListMultipartUploadsBuilder(ListMultipartUploadsInput *
                                input):QsDefaultRequestBuilder <
        ListMultipartUploadsInput > (input)
    {
    };

    virtual ~ ListMultipartUploadsBuilder()
    {
    };

    virtual bool CkeckIfInputIsVaild()
    {
        return m_input->CheckIfInputIsVaild();
    };
    virtual Http::QueryParamCollection GetQueryParamCollection();
};

// ListMultipartUploadsRequest AddQueryStringParameters.
Http::QueryParamCollection ListMultipartUploadsBuilder::
GetQueryParamCollection()
{
    Http::QueryParamCollection queryParameters;
    std::stringstream ss;
    std::vector < std::string >::iterator it;
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_LIST_MULTIPART_UPLOADS_DELIMITER_FLAG))
    {
        ss << m_input->GetDelimiter();
        queryParameters.insert(Http::HeaderValuePair("delimiter", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_LIST_MULTIPART_UPLOADS_KEY_MARKER_FLAG))
    {
        ss << m_input->GetKeyMarker();
        queryParameters.insert(Http::HeaderValuePair("key_marker", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_LIST_MULTIPART_UPLOADS_LIMIT_FLAG))
    {
        ss << m_input->GetLimit();
        queryParameters.insert(Http::HeaderValuePair("limit", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_LIST_MULTIPART_UPLOADS_PREFIX_FLAG))
    {
        ss << m_input->GetPrefix();
        queryParameters.insert(Http::HeaderValuePair("prefix", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_LIST_MULTIPART_UPLOADS_UPLOAD_ID_MARKER_FLAG))
    {
        ss << m_input->GetUploadIDMarker();
        queryParameters.
        insert(Http::HeaderValuePair("upload_id_marker", ss.str()));
        ss.str("");
    }
    return queryParameters;
}

class ListMultipartUploadsUnparker:public QsDefaultResponseUnparker <
    ListMultipartUploadsOutput >
{
public:
    ListMultipartUploadsUnparker(ListMultipartUploadsOutput *
                                 output):QsDefaultResponseUnparker <
        ListMultipartUploadsOutput > (output)
    {
    };

    virtual ~ ListMultipartUploadsUnparker()
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

void ListMultipartUploadsUnparker::ParseResponseBody(std::iostream *
        responseBody)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(*responseBody, jsonContent);
    if (jsonContent.isMember("common_prefixes"))
    {
        std::vector < std::string > vecCommonPrefixes;
        for (unsigned i = 0; i < jsonContent["common_prefixes"].size(); ++i)
        {
            vecCommonPrefixes.push_back(jsonContent["common_prefixes"][i].
                                        asString());
        }
        m_output->SetCommonPrefixes(vecCommonPrefixes);
    }
    if (jsonContent.isMember("delimiter"))
    {
        m_output->SetDelimiter(jsonContent["delimiter"].asString());
    }
    if (jsonContent.isMember("limit"))
    {
        m_output->SetLimit(jsonContent["limit"].asInt());
    }
    if (jsonContent.isMember("marker"))
    {
        m_output->SetMarker(jsonContent["marker"].asString());
    }
    if (jsonContent.isMember("name"))
    {
        m_output->SetName(jsonContent["name"].asString());
    }
    if (jsonContent.isMember("next_key_marker"))
    {
        m_output->SetNextKeyMarker(jsonContent["next_key_marker"].asString());
    }
    if (jsonContent.isMember("next_upload_id_marker"))
    {
        m_output->SetNextUploadIDMarker(jsonContent["next_upload_id_marker"].
                                        asString());
    }
    if (jsonContent.isMember("prefix"))
    {
        m_output->SetPrefix(jsonContent["prefix"].asString());
    }
    if (jsonContent.isMember("uploads"))
    {
        std::vector < UploadsType > vecUploads;
        for (unsigned i = 0; i < jsonContent["uploads"].size(); ++i)
        {
            vecUploads.push_back(jsonContent["uploads"][i].toStyledString());
        }
        m_output->SetUploads(vecUploads);
    }
    m_bNeedReleaseBody = true;
}

class ListObjectsBuilder:public QsDefaultRequestBuilder < ListObjectsInput >
{
public:
    ListObjectsBuilder(ListObjectsInput * input):QsDefaultRequestBuilder <
        ListObjectsInput > (input)
    {
    };

    virtual ~ ListObjectsBuilder()
    {
    };

    virtual bool CkeckIfInputIsVaild()
    {
        return m_input->CheckIfInputIsVaild();
    };
    virtual Http::QueryParamCollection GetQueryParamCollection();
};

// ListObjectsRequest AddQueryStringParameters.
Http::QueryParamCollection ListObjectsBuilder::GetQueryParamCollection()
{
    Http::QueryParamCollection queryParameters;
    std::stringstream ss;
    std::vector < std::string >::iterator it;
    if (m_input->IsPropHasBeenSet(SETTING_INPUT_LIST_OBJECTS_DELIMITER_FLAG))
    {
        ss << m_input->GetDelimiter();
        queryParameters.insert(Http::HeaderValuePair("delimiter", ss.str()));
        ss.str("");
    }
    if (m_input->IsPropHasBeenSet(SETTING_INPUT_LIST_OBJECTS_LIMIT_FLAG))
    {
        ss << m_input->GetLimit();
        queryParameters.insert(Http::HeaderValuePair("limit", ss.str()));
        ss.str("");
    }
    if (m_input->IsPropHasBeenSet(SETTING_INPUT_LIST_OBJECTS_MARKER_FLAG))
    {
        ss << m_input->GetMarker();
        queryParameters.insert(Http::HeaderValuePair("marker", ss.str()));
        ss.str("");
    }
    if (m_input->IsPropHasBeenSet(SETTING_INPUT_LIST_OBJECTS_PREFIX_FLAG))
    {
        ss << m_input->GetPrefix();
        queryParameters.insert(Http::HeaderValuePair("prefix", ss.str()));
        ss.str("");
    }
    return queryParameters;
}

class ListObjectsUnparker:public QsDefaultResponseUnparker < ListObjectsOutput >
{
public:
    ListObjectsUnparker(ListObjectsOutput * output):QsDefaultResponseUnparker <
        ListObjectsOutput > (output)
    {
    };

    virtual ~ ListObjectsUnparker()
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

void ListObjectsUnparker::ParseResponseBody(std::iostream * responseBody)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(*responseBody, jsonContent);
    if (jsonContent.isMember("common_prefixes"))
    {
        std::vector < std::string > vecCommonPrefixes;
        for (unsigned i = 0; i < jsonContent["common_prefixes"].size(); ++i)
        {
            vecCommonPrefixes.push_back(jsonContent["common_prefixes"][i].
                                        asString());
        }
        m_output->SetCommonPrefixes(vecCommonPrefixes);
    }
    if (jsonContent.isMember("delimiter"))
    {
        m_output->SetDelimiter(jsonContent["delimiter"].asString());
    }
    if (jsonContent.isMember("keys"))
    {
        std::vector < KeyType > vecKeys;
        for (unsigned i = 0; i < jsonContent["keys"].size(); ++i)
        {
            vecKeys.push_back(jsonContent["keys"][i].toStyledString());
        }
        m_output->SetKeys(vecKeys);
    }
    if (jsonContent.isMember("limit"))
    {
        m_output->SetLimit(jsonContent["limit"].asInt());
    }
    if (jsonContent.isMember("marker"))
    {
        m_output->SetMarker(jsonContent["marker"].asString());
    }
    if (jsonContent.isMember("name"))
    {
        m_output->SetName(jsonContent["name"].asString());
    }
    if (jsonContent.isMember("next_marker"))
    {
        m_output->SetNextMarker(jsonContent["next_marker"].asString());
    }
    if (jsonContent.isMember("owner"))
    {
        m_output->SetOwner(jsonContent["owner"].toStyledString());
    }
    if (jsonContent.isMember("prefix"))
    {
        m_output->SetPrefix(jsonContent["prefix"].asString());
    }
    m_bNeedReleaseBody = true;
}

typedef QsDefaultRequestBuilder < PutBucketInput > PutBucketBuilder;

typedef QsDefaultResponseUnparker < PutBucketOutput > PutBucketUnparker;

class PutBucketACLBuilder:public QsDefaultRequestBuilder < PutBucketACLInput >
{
public:
    PutBucketACLBuilder(PutBucketACLInput * input):QsDefaultRequestBuilder <
        PutBucketACLInput > (input)
    {
    };

    virtual ~ PutBucketACLBuilder()
    {
    };

    virtual bool CkeckIfInputIsVaild()
    {
        return m_input->CheckIfInputIsVaild();
    };
    virtual std::iostream * GetRequestBody();
};

// PutBucketACLRequest GetRequestBody.
std::iostream * PutBucketACLBuilder::GetRequestBody()
{
    //TO DO;
    Json::FastWriter jsonWriter;
    Json::Value jsonContent;
    if (m_input->IsPropHasBeenSet(SETTING_INPUT_PUT_BUCKET_ACL_ACL_FLAG))
    {
        Json::Value arrayACL;
        std::vector < ACLType > acl = m_input->GetACL();
        for (std::vector < ACLType >::iterator it = acl.begin();
                it != acl.end(); it++)
        {
            Json::Reader jsonReader;
            Json::Value itemJsonValue;
            jsonReader.parse(it->Serialize(), itemJsonValue);
            arrayACL.append(itemJsonValue);
        }
        jsonContent["acl"] = arrayACL;
    }
    m_bNeedReleaseBody = true;
    return new std::stringstream(jsonWriter.write(jsonContent));
}

typedef QsDefaultResponseUnparker < PutBucketACLOutput > PutBucketACLUnparker;

class PutBucketCORSBuilder:public QsDefaultRequestBuilder < PutBucketCORSInput >
{
public:
    PutBucketCORSBuilder(PutBucketCORSInput * input):QsDefaultRequestBuilder <
        PutBucketCORSInput > (input)
    {
    };

    virtual ~ PutBucketCORSBuilder()
    {
    };

    virtual bool CkeckIfInputIsVaild()
    {
        return m_input->CheckIfInputIsVaild();
    };
    virtual std::iostream * GetRequestBody();
};

// PutBucketCORSRequest GetRequestBody.
std::iostream * PutBucketCORSBuilder::GetRequestBody()
{
    //TO DO;
    Json::FastWriter jsonWriter;
    Json::Value jsonContent;
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_PUT_BUCKET_CORS_CORS_RULES_FLAG))
    {
        Json::Value arrayCORSRules;
        std::vector < CORSRuleType > corsRules = m_input->GetCORSRules();
        for (std::vector < CORSRuleType >::iterator it = corsRules.begin();
                it != corsRules.end(); it++)
        {
            Json::Reader jsonReader;
            Json::Value itemJsonValue;
            jsonReader.parse(it->Serialize(), itemJsonValue);
            arrayCORSRules.append(itemJsonValue);
        }
        jsonContent["cors_rules"] = arrayCORSRules;
    }
    m_bNeedReleaseBody = true;
    return new std::stringstream(jsonWriter.write(jsonContent));
}

typedef QsDefaultResponseUnparker < PutBucketCORSOutput > PutBucketCORSUnparker;

class PutBucketExternalMirrorBuilder:public QsDefaultRequestBuilder <
    PutBucketExternalMirrorInput >
{
public:
    PutBucketExternalMirrorBuilder(PutBucketExternalMirrorInput *
                                   input):QsDefaultRequestBuilder <
        PutBucketExternalMirrorInput > (input)
    {
    };

    virtual ~ PutBucketExternalMirrorBuilder()
    {
    };

    virtual bool CkeckIfInputIsVaild()
    {
        return m_input->CheckIfInputIsVaild();
    };
    virtual std::iostream * GetRequestBody();
};

// PutBucketExternalMirrorRequest GetRequestBody.
std::iostream * PutBucketExternalMirrorBuilder::GetRequestBody()
{
    //TO DO;
    Json::FastWriter jsonWriter;
    Json::Value jsonContent;
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_PUT_BUCKET_EXTERNAL_MIRROR_SOURCE_SITE_FLAG))
    {
        jsonContent["source_site"] = m_input->GetSourceSite();
    }
    m_bNeedReleaseBody = true;
    return new std::stringstream(jsonWriter.write(jsonContent));
}

typedef QsDefaultResponseUnparker < PutBucketExternalMirrorOutput >
PutBucketExternalMirrorUnparker;

class PutBucketPolicyBuilder:public QsDefaultRequestBuilder <
    PutBucketPolicyInput >
{
public:
    PutBucketPolicyBuilder(PutBucketPolicyInput *
                           input):QsDefaultRequestBuilder <
        PutBucketPolicyInput > (input)
    {
    };

    virtual ~ PutBucketPolicyBuilder()
    {
    };

    virtual bool CkeckIfInputIsVaild()
    {
        return m_input->CheckIfInputIsVaild();
    };
    virtual std::iostream * GetRequestBody();
};

// PutBucketPolicyRequest GetRequestBody.
std::iostream * PutBucketPolicyBuilder::GetRequestBody()
{
    //TO DO;
    Json::FastWriter jsonWriter;
    Json::Value jsonContent;
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_PUT_BUCKET_POLICY_STATEMENT_FLAG))
    {
        Json::Value arrayStatement;
        std::vector < StatementType > statement = m_input->GetStatement();
        for (std::vector < StatementType >::iterator it = statement.begin();
                it != statement.end(); it++)
        {
            Json::Reader jsonReader;
            Json::Value itemJsonValue;
            jsonReader.parse(it->Serialize(), itemJsonValue);
            arrayStatement.append(itemJsonValue);
        }
        jsonContent["statement"] = arrayStatement;
    }
    m_bNeedReleaseBody = true;
    return new std::stringstream(jsonWriter.write(jsonContent));
}

typedef QsDefaultResponseUnparker < PutBucketPolicyOutput >
PutBucketPolicyUnparker;

// +--------------------------------------------------------------------
// |           RequestBuilderSource and ResponseUnparkerSource
// +--------------------------------------------------------------------
class AbortMultipartUploadBuilder:public QsDefaultRequestBuilder <
    AbortMultipartUploadInput >
{
public:
    AbortMultipartUploadBuilder(AbortMultipartUploadInput *
                                input):QsDefaultRequestBuilder <
        AbortMultipartUploadInput > (input)
    {
    };

    virtual ~ AbortMultipartUploadBuilder()
    {
    };

    virtual bool CkeckIfInputIsVaild()
    {
        return m_input->CheckIfInputIsVaild();
    };
    virtual Http::QueryParamCollection GetQueryParamCollection();
};

// AbortMultipartUploadRequest AddQueryStringParameters.
Http::QueryParamCollection AbortMultipartUploadBuilder::
GetQueryParamCollection()
{
    Http::QueryParamCollection queryParameters;
    std::stringstream ss;
    std::vector < std::string >::iterator it;
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_ABORT_MULTIPART_UPLOAD_UPLOAD_ID_FLAG))
    {
        ss << m_input->GetUploadID();
        queryParameters.insert(Http::HeaderValuePair("upload_id", ss.str()));
        ss.str("");
    }
    return queryParameters;
}

typedef QsDefaultResponseUnparker < AbortMultipartUploadOutput >
AbortMultipartUploadUnparker;

class CompleteMultipartUploadBuilder:public QsDefaultRequestBuilder <
    CompleteMultipartUploadInput >
{
public:
    CompleteMultipartUploadBuilder(CompleteMultipartUploadInput *
                                   input):QsDefaultRequestBuilder <
        CompleteMultipartUploadInput > (input)
    {
    };

    virtual ~ CompleteMultipartUploadBuilder()
    {
    };

    virtual bool CkeckIfInputIsVaild()
    {
        return m_input->CheckIfInputIsVaild();
    };
    virtual Http::HeaderValueCollection GetHeaderValueCollection();
    virtual Http::QueryParamCollection GetQueryParamCollection();
    virtual std::iostream * GetRequestBody();
};

// CompleteMultipartUploadRequest GetRequestSpecificHeaders.
Http::HeaderValueCollection CompleteMultipartUploadBuilder::
GetHeaderValueCollection()
{
    //TO DO;
    Http::HeaderValueCollection headers;
    std::stringstream ss;
    std::vector < std::string >::iterator it;
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_COMPLETE_MULTIPART_UPLOAD_ETAG_FLAG))
    {
        ss << m_input->GetETag();
        headers.insert(Http::HeaderValuePair("ETag", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_COMPLETE_MULTIPART_UPLOAD_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG))
    {
        ss << m_input->GetXQSEncryptionCustomerAlgorithm();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Encryption-Customer-Algorithm",
                               ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_COMPLETE_MULTIPART_UPLOAD_X_QS_ENCRYPTION_CUSTOMER_KEY_FLAG))
    {
        ss << m_input->GetXQSEncryptionCustomerKey();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Encryption-Customer-Key", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_COMPLETE_MULTIPART_UPLOAD_X_QS_ENCRYPTION_CUSTOMER_KEY_MD5_FLAG))
    {
        ss << m_input->GetXQSEncryptionCustomerKeyMD5();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Encryption-Customer-Key-MD5",
                               ss.str()));
        ss.str("");
    }
    return headers;
}

// CompleteMultipartUploadRequest AddQueryStringParameters.
Http::QueryParamCollection CompleteMultipartUploadBuilder::
GetQueryParamCollection()
{
    Http::QueryParamCollection queryParameters;
    std::stringstream ss;
    std::vector < std::string >::iterator it;
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_COMPLETE_MULTIPART_UPLOAD_UPLOAD_ID_FLAG))
    {
        ss << m_input->GetUploadID();
        queryParameters.insert(Http::HeaderValuePair("upload_id", ss.str()));
        ss.str("");
    }
    return queryParameters;
}

// CompleteMultipartUploadRequest GetRequestBody.
std::iostream * CompleteMultipartUploadBuilder::GetRequestBody()
{
    //TO DO;
    Json::FastWriter jsonWriter;
    Json::Value jsonContent;
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_COMPLETE_MULTIPART_UPLOAD_OBJECT_PARTS_FLAG))
    {
        Json::Value arrayObjectParts;
        std::vector < ObjectPartType > objectParts = m_input->GetObjectParts();
        for (std::vector < ObjectPartType >::iterator it = objectParts.begin();
                it != objectParts.end(); it++)
        {
            Json::Reader jsonReader;
            Json::Value itemJsonValue;
            jsonReader.parse(it->Serialize(), itemJsonValue);
            arrayObjectParts.append(itemJsonValue);
        }
        jsonContent["object_parts"] = arrayObjectParts;
    }
    m_bNeedReleaseBody = true;
    return new std::stringstream(jsonWriter.write(jsonContent));
}

class CompleteMultipartUploadUnparker:public QsDefaultResponseUnparker <
    CompleteMultipartUploadOutput >
{
public:
    CompleteMultipartUploadUnparker(CompleteMultipartUploadOutput *
                                    output):QsDefaultResponseUnparker <
        CompleteMultipartUploadOutput > (output)
    {
    };

    virtual ~ CompleteMultipartUploadUnparker()
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
        int expectedRespCode[1] = { 201, };
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
    virtual void ParseResponseHeaders(const Http::
                                      HeaderValueCollection &
                                      headerValueCollection);
};

// CompleteMultipartUploadRequest ParseResponseHeaders.
void CompleteMultipartUploadUnparker::ParseResponseHeaders(const Http::
        HeaderValueCollection
        &
        headerValueCollection)
{
    const HeaderValueCollection & headers = headerValueCollection;
    HeaderValueCollection::const_iterator XQSEncryptionCustomerAlgorithmIter =
        headers.find("x-qs-encryption-customer-algorithm");
    if (XQSEncryptionCustomerAlgorithmIter != headers.end())
    {
        m_output->
        SetXQSEncryptionCustomerAlgorithm
        (XQSEncryptionCustomerAlgorithmIter->second);
    }
}

typedef QsDefaultRequestBuilder < DeleteObjectInput > DeleteObjectBuilder;

typedef QsDefaultResponseUnparker < DeleteObjectOutput > DeleteObjectUnparker;

class GetObjectBuilder:public QsDefaultRequestBuilder < GetObjectInput >
{
public:
    GetObjectBuilder(GetObjectInput * input):QsDefaultRequestBuilder <
        GetObjectInput > (input)
    {
    };

    virtual ~ GetObjectBuilder()
    {
    };

    virtual bool CkeckIfInputIsVaild()
    {
        return m_input->CheckIfInputIsVaild();
    };
    virtual Http::HeaderValueCollection GetHeaderValueCollection();
    virtual Http::QueryParamCollection GetQueryParamCollection();
};

// GetObjectRequest GetRequestSpecificHeaders.
Http::HeaderValueCollection GetObjectBuilder::GetHeaderValueCollection()
{
    //TO DO;
    Http::HeaderValueCollection headers;
    std::stringstream ss;
    std::vector < std::string >::iterator it;
    if (m_input->IsPropHasBeenSet(SETTING_INPUT_GET_OBJECT_IF_MATCH_FLAG))
    {
        ss << m_input->GetIfMatch();
        headers.insert(Http::HeaderValuePair("If-Match", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_GET_OBJECT_IF_MODIFIED_SINCE_FLAG))
    {
        ss << m_input->GetIfModifiedSince();
        headers.insert(Http::HeaderValuePair("If-Modified-Since", ss.str()));
        ss.str("");
    }
    if (m_input->IsPropHasBeenSet(SETTING_INPUT_GET_OBJECT_IF_NONE_MATCH_FLAG))
    {
        ss << m_input->GetIfNoneMatch();
        headers.insert(Http::HeaderValuePair("If-None-Match", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_GET_OBJECT_IF_UNMODIFIED_SINCE_FLAG))
    {
        ss << m_input->GetIfUnmodifiedSince();
        headers.insert(Http::HeaderValuePair("If-Unmodified-Since", ss.str()));
        ss.str("");
    }
    if (m_input->IsPropHasBeenSet(SETTING_INPUT_GET_OBJECT_RANGE_FLAG))
    {
        ss << m_input->GetRange();
        headers.insert(Http::HeaderValuePair("Range", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_GET_OBJECT_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG))
    {
        ss << m_input->GetXQSEncryptionCustomerAlgorithm();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Encryption-Customer-Algorithm",
                               ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_GET_OBJECT_X_QS_ENCRYPTION_CUSTOMER_KEY_FLAG))
    {
        ss << m_input->GetXQSEncryptionCustomerKey();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Encryption-Customer-Key", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_GET_OBJECT_X_QS_ENCRYPTION_CUSTOMER_KEY_MD5_FLAG))
    {
        ss << m_input->GetXQSEncryptionCustomerKeyMD5();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Encryption-Customer-Key-MD5",
                               ss.str()));
        ss.str("");
    }
    return headers;
}

// GetObjectRequest AddQueryStringParameters.
Http::QueryParamCollection GetObjectBuilder::GetQueryParamCollection()
{
    Http::QueryParamCollection queryParameters;
    std::stringstream ss;
    std::vector < std::string >::iterator it;
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_GET_OBJECT_RESPONSE_CACHE_CONTROL_FLAG))
    {
        ss << m_input->GetResponseCacheControl();
        queryParameters.
        insert(Http::HeaderValuePair("response-cache-control", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_GET_OBJECT_RESPONSE_CONTENT_DISPOSITION_FLAG))
    {
        ss << m_input->GetResponseContentDisposition();
        queryParameters.
        insert(Http::
               HeaderValuePair("response-content-disposition", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_GET_OBJECT_RESPONSE_CONTENT_ENCODING_FLAG))
    {
        ss << m_input->GetResponseContentEncoding();
        queryParameters.
        insert(Http::
               HeaderValuePair("response-content-encoding", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_GET_OBJECT_RESPONSE_CONTENT_LANGUAGE_FLAG))
    {
        ss << m_input->GetResponseContentLanguage();
        queryParameters.
        insert(Http::
               HeaderValuePair("response-content-language", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_GET_OBJECT_RESPONSE_CONTENT_TYPE_FLAG))
    {
        ss << m_input->GetResponseContentType();
        queryParameters.
        insert(Http::HeaderValuePair("response-content-type", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_GET_OBJECT_RESPONSE_EXPIRES_FLAG))
    {
        ss << m_input->GetResponseExpires();
        queryParameters.
        insert(Http::HeaderValuePair("response-expires", ss.str()));
        ss.str("");
    }
    return queryParameters;
}

class GetObjectUnparker:public QsDefaultResponseUnparker < GetObjectOutput >
{
public:
    GetObjectUnparker(GetObjectOutput * output):QsDefaultResponseUnparker <
        GetObjectOutput > (output)
    {
    };

    virtual ~ GetObjectUnparker()
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
        int expectedRespCode[4] = { 200, 206, 304, 412, };
        bool isExpected = false;
        for (int i = 0; i < 4; i++)
        {
            if (expectedRespCode[i] == responseCode)
            {
                isExpected = true;
                break;
            }
        }
        return isExpected;
    };
    virtual void ParseResponseHeaders(const Http::
                                      HeaderValueCollection &
                                      headerValueCollection);
    virtual void ParseResponseBody(std::iostream * responseBody);

};

// GetObjectRequest ParseResponseHeaders.
void GetObjectUnparker::ParseResponseHeaders(const Http::
        HeaderValueCollection &
        headerValueCollection)
{
    const HeaderValueCollection & headers = headerValueCollection;
    HeaderValueCollection::const_iterator CacheControlIter =
        headers.find("cache-control");
    if (CacheControlIter != headers.end())
    {
        m_output->SetCacheControl(CacheControlIter->second);
    }
    HeaderValueCollection::const_iterator ContentDispositionIter =
        headers.find("content-disposition");
    if (ContentDispositionIter != headers.end())
    {
        m_output->SetContentDisposition(ContentDispositionIter->second);
    }
    HeaderValueCollection::const_iterator ContentEncodingIter =
        headers.find("content-encoding");
    if (ContentEncodingIter != headers.end())
    {
        m_output->SetContentEncoding(ContentEncodingIter->second);
    }
    HeaderValueCollection::const_iterator ContentLanguageIter =
        headers.find("content-language");
    if (ContentLanguageIter != headers.end())
    {
        m_output->SetContentLanguage(ContentLanguageIter->second);
    }
    HeaderValueCollection::const_iterator ContentLengthIter =
        headers.find("content-length");
    if (ContentLengthIter != headers.end())
    {
        m_output->
        SetContentLength(StringUtils::
                         ConvertToInt64(ContentLengthIter->second.c_str()));
    }
    HeaderValueCollection::const_iterator ContentRangeIter =
        headers.find("content-range");
    if (ContentRangeIter != headers.end())
    {
        m_output->SetContentRange(ContentRangeIter->second);
    }
    HeaderValueCollection::const_iterator ContentTypeIter =
        headers.find("content-type");
    if (ContentTypeIter != headers.end())
    {
        m_output->SetContentType(ContentTypeIter->second);
    }
    HeaderValueCollection::const_iterator ETagIter = headers.find("etag");
    if (ETagIter != headers.end())
    {
        m_output->SetETag(ETagIter->second);
    }
    HeaderValueCollection::const_iterator ExpiresIter = headers.find("expires");
    if (ExpiresIter != headers.end())
    {
        m_output->SetExpires(ExpiresIter->second);
    }
    HeaderValueCollection::const_iterator LastModifiedIter =
        headers.find("last-modified");
    if (LastModifiedIter != headers.end())
    {
        m_output->SetLastModified(LastModifiedIter->second);
    }
    HeaderValueCollection::const_iterator XQSEncryptionCustomerAlgorithmIter =
        headers.find("x-qs-encryption-customer-algorithm");
    if (XQSEncryptionCustomerAlgorithmIter != headers.end())
    {
        m_output->
        SetXQSEncryptionCustomerAlgorithm
        (XQSEncryptionCustomerAlgorithmIter->second);
    }
}

void GetObjectUnparker::ParseResponseBody(std::iostream * responseBody)
{
    m_output->SetBody(responseBody);
}

class HeadObjectBuilder:public QsDefaultRequestBuilder < HeadObjectInput >
{
public:
    HeadObjectBuilder(HeadObjectInput * input):QsDefaultRequestBuilder <
        HeadObjectInput > (input)
    {
    };

    virtual ~ HeadObjectBuilder()
    {
    };

    virtual bool CkeckIfInputIsVaild()
    {
        return m_input->CheckIfInputIsVaild();
    };
    virtual Http::HeaderValueCollection GetHeaderValueCollection();
};

// HeadObjectRequest GetRequestSpecificHeaders.
Http::HeaderValueCollection HeadObjectBuilder::GetHeaderValueCollection()
{
    //TO DO;
    Http::HeaderValueCollection headers;
    std::stringstream ss;
    std::vector < std::string >::iterator it;
    if (m_input->IsPropHasBeenSet(SETTING_INPUT_HEAD_OBJECT_IF_MATCH_FLAG))
    {
        ss << m_input->GetIfMatch();
        headers.insert(Http::HeaderValuePair("If-Match", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_HEAD_OBJECT_IF_MODIFIED_SINCE_FLAG))
    {
        ss << m_input->GetIfModifiedSince();
        headers.insert(Http::HeaderValuePair("If-Modified-Since", ss.str()));
        ss.str("");
    }
    if (m_input->IsPropHasBeenSet(SETTING_INPUT_HEAD_OBJECT_IF_NONE_MATCH_FLAG))
    {
        ss << m_input->GetIfNoneMatch();
        headers.insert(Http::HeaderValuePair("If-None-Match", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_HEAD_OBJECT_IF_UNMODIFIED_SINCE_FLAG))
    {
        ss << m_input->GetIfUnmodifiedSince();
        headers.insert(Http::HeaderValuePair("If-Unmodified-Since", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_HEAD_OBJECT_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG))
    {
        ss << m_input->GetXQSEncryptionCustomerAlgorithm();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Encryption-Customer-Algorithm",
                               ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_HEAD_OBJECT_X_QS_ENCRYPTION_CUSTOMER_KEY_FLAG))
    {
        ss << m_input->GetXQSEncryptionCustomerKey();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Encryption-Customer-Key", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_HEAD_OBJECT_X_QS_ENCRYPTION_CUSTOMER_KEY_MD5_FLAG))
    {
        ss << m_input->GetXQSEncryptionCustomerKeyMD5();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Encryption-Customer-Key-MD5",
                               ss.str()));
        ss.str("");
    }
    return headers;
}

class HeadObjectUnparker:public QsDefaultResponseUnparker < HeadObjectOutput >
{
public:
    HeadObjectUnparker(HeadObjectOutput * output):QsDefaultResponseUnparker <
        HeadObjectOutput > (output)
    {
    };

    virtual ~ HeadObjectUnparker()
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
    virtual void ParseResponseHeaders(const Http::
                                      HeaderValueCollection &
                                      headerValueCollection);
};

// HeadObjectRequest ParseResponseHeaders.
void HeadObjectUnparker::ParseResponseHeaders(const Http::
        HeaderValueCollection &
        headerValueCollection)
{
    const HeaderValueCollection & headers = headerValueCollection;
    HeaderValueCollection::const_iterator ContentLengthIter =
        headers.find("content-length");
    if (ContentLengthIter != headers.end())
    {
        m_output->
        SetContentLength(StringUtils::
                         ConvertToInt64(ContentLengthIter->second.c_str()));
    }
    HeaderValueCollection::const_iterator ContentTypeIter =
        headers.find("content-type");
    if (ContentTypeIter != headers.end())
    {
        m_output->SetContentType(ContentTypeIter->second);
    }
    HeaderValueCollection::const_iterator ETagIter = headers.find("etag");
    if (ETagIter != headers.end())
    {
        m_output->SetETag(ETagIter->second);
    }
    HeaderValueCollection::const_iterator LastModifiedIter =
        headers.find("last-modified");
    if (LastModifiedIter != headers.end())
    {
        m_output->SetLastModified(LastModifiedIter->second);
    }
    HeaderValueCollection::const_iterator XQSEncryptionCustomerAlgorithmIter =
        headers.find("x-qs-encryption-customer-algorithm");
    if (XQSEncryptionCustomerAlgorithmIter != headers.end())
    {
        m_output->
        SetXQSEncryptionCustomerAlgorithm
        (XQSEncryptionCustomerAlgorithmIter->second);
    }
}

class ImageProcessBuilder:public QsDefaultRequestBuilder < ImageProcessInput >
{
public:
    ImageProcessBuilder(ImageProcessInput * input):QsDefaultRequestBuilder <
        ImageProcessInput > (input)
    {
    };

    virtual ~ ImageProcessBuilder()
    {
    };

    virtual bool CkeckIfInputIsVaild()
    {
        return m_input->CheckIfInputIsVaild();
    };
    virtual Http::HeaderValueCollection GetHeaderValueCollection();
    virtual Http::QueryParamCollection GetQueryParamCollection();
};

// ImageProcessRequest GetRequestSpecificHeaders.
Http::HeaderValueCollection ImageProcessBuilder::GetHeaderValueCollection()
{
    //TO DO;
    Http::HeaderValueCollection headers;
    std::stringstream ss;
    std::vector < std::string >::iterator it;
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_IMAGE_PROCESS_IF_MODIFIED_SINCE_FLAG))
    {
        ss << m_input->GetIfModifiedSince();
        headers.insert(Http::HeaderValuePair("If-Modified-Since", ss.str()));
        ss.str("");
    }
    return headers;
}

// ImageProcessRequest AddQueryStringParameters.
Http::QueryParamCollection ImageProcessBuilder::GetQueryParamCollection()
{
    Http::QueryParamCollection queryParameters;
    std::stringstream ss;
    std::vector < std::string >::iterator it;
    if (m_input->IsPropHasBeenSet(SETTING_INPUT_IMAGE_PROCESS_ACTION_FLAG))
    {
        ss << m_input->GetAction();
        queryParameters.insert(Http::HeaderValuePair("action", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_IMAGE_PROCESS_RESPONSE_CACHE_CONTROL_FLAG))
    {
        ss << m_input->GetResponseCacheControl();
        queryParameters.
        insert(Http::HeaderValuePair("response-cache-control", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_IMAGE_PROCESS_RESPONSE_CONTENT_DISPOSITION_FLAG))
    {
        ss << m_input->GetResponseContentDisposition();
        queryParameters.
        insert(Http::
               HeaderValuePair("response-content-disposition", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_IMAGE_PROCESS_RESPONSE_CONTENT_ENCODING_FLAG))
    {
        ss << m_input->GetResponseContentEncoding();
        queryParameters.
        insert(Http::
               HeaderValuePair("response-content-encoding", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_IMAGE_PROCESS_RESPONSE_CONTENT_LANGUAGE_FLAG))
    {
        ss << m_input->GetResponseContentLanguage();
        queryParameters.
        insert(Http::
               HeaderValuePair("response-content-language", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_IMAGE_PROCESS_RESPONSE_CONTENT_TYPE_FLAG))
    {
        ss << m_input->GetResponseContentType();
        queryParameters.
        insert(Http::HeaderValuePair("response-content-type", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_IMAGE_PROCESS_RESPONSE_EXPIRES_FLAG))
    {
        ss << m_input->GetResponseExpires();
        queryParameters.
        insert(Http::HeaderValuePair("response-expires", ss.str()));
        ss.str("");
    }
    return queryParameters;
}

class ImageProcessUnparker:public QsDefaultResponseUnparker <
    ImageProcessOutput >
{
public:
    ImageProcessUnparker(ImageProcessOutput *
                         output):QsDefaultResponseUnparker <
        ImageProcessOutput > (output)
    {
    };

    virtual ~ ImageProcessUnparker()
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
        int expectedRespCode[2] = { 200, 304, };
        bool isExpected = false;
        for (int i = 0; i < 2; i++)
        {
            if (expectedRespCode[i] == responseCode)
            {
                isExpected = true;
                break;
            }
        }
        return isExpected;
    };
    virtual void ParseResponseHeaders(const Http::
                                      HeaderValueCollection &
                                      headerValueCollection);
    virtual void ParseResponseBody(std::iostream * responseBody);

};

// ImageProcessRequest ParseResponseHeaders.
void ImageProcessUnparker::ParseResponseHeaders(const Http::
        HeaderValueCollection &
        headerValueCollection)
{
    const HeaderValueCollection & headers = headerValueCollection;
    HeaderValueCollection::const_iterator ContentLengthIter =
        headers.find("content-length");
    if (ContentLengthIter != headers.end())
    {
        m_output->
        SetContentLength(StringUtils::
                         ConvertToInt64(ContentLengthIter->second.c_str()));
    }
}

void ImageProcessUnparker::ParseResponseBody(std::iostream * responseBody)
{
    m_output->SetBody(responseBody);
}

class InitiateMultipartUploadBuilder:public QsDefaultRequestBuilder <
    InitiateMultipartUploadInput >
{
public:
    InitiateMultipartUploadBuilder(InitiateMultipartUploadInput *
                                   input):QsDefaultRequestBuilder <
        InitiateMultipartUploadInput > (input)
    {
    };

    virtual ~ InitiateMultipartUploadBuilder()
    {
    };

    virtual bool CkeckIfInputIsVaild()
    {
        return m_input->CheckIfInputIsVaild();
    };
    virtual Http::HeaderValueCollection GetHeaderValueCollection();
};

// InitiateMultipartUploadRequest GetRequestSpecificHeaders.
Http::HeaderValueCollection InitiateMultipartUploadBuilder::
GetHeaderValueCollection()
{
    //TO DO;
    Http::HeaderValueCollection headers;
    std::stringstream ss;
    std::vector < std::string >::iterator it;
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_INITIATE_MULTIPART_UPLOAD_CONTENT_TYPE_FLAG))
    {
        ss << m_input->GetContentType();
        headers.insert(Http::HeaderValuePair("Content-Type", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_INITIATE_MULTIPART_UPLOAD_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG))
    {
        ss << m_input->GetXQSEncryptionCustomerAlgorithm();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Encryption-Customer-Algorithm",
                               ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_INITIATE_MULTIPART_UPLOAD_X_QS_ENCRYPTION_CUSTOMER_KEY_FLAG))
    {
        ss << m_input->GetXQSEncryptionCustomerKey();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Encryption-Customer-Key", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_INITIATE_MULTIPART_UPLOAD_X_QS_ENCRYPTION_CUSTOMER_KEY_MD5_FLAG))
    {
        ss << m_input->GetXQSEncryptionCustomerKeyMD5();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Encryption-Customer-Key-MD5",
                               ss.str()));
        ss.str("");
    }
    return headers;
}

class InitiateMultipartUploadUnparker:public QsDefaultResponseUnparker <
    InitiateMultipartUploadOutput >
{
public:
    InitiateMultipartUploadUnparker(InitiateMultipartUploadOutput *
                                    output):QsDefaultResponseUnparker <
        InitiateMultipartUploadOutput > (output)
    {
    };

    virtual ~ InitiateMultipartUploadUnparker()
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
    virtual void ParseResponseHeaders(const Http::
                                      HeaderValueCollection &
                                      headerValueCollection);
    virtual void ParseResponseBody(std::iostream * responseBody);
};

// InitiateMultipartUploadRequest ParseResponseHeaders.
void InitiateMultipartUploadUnparker::ParseResponseHeaders(const Http::
        HeaderValueCollection
        &
        headerValueCollection)
{
    const HeaderValueCollection & headers = headerValueCollection;
    HeaderValueCollection::const_iterator XQSEncryptionCustomerAlgorithmIter =
        headers.find("x-qs-encryption-customer-algorithm");
    if (XQSEncryptionCustomerAlgorithmIter != headers.end())
    {
        m_output->
        SetXQSEncryptionCustomerAlgorithm
        (XQSEncryptionCustomerAlgorithmIter->second);
    }
}

void InitiateMultipartUploadUnparker::ParseResponseBody(std::iostream *
        responseBody)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(*responseBody, jsonContent);
    if (jsonContent.isMember("bucket"))
    {
        m_output->SetBucket(jsonContent["bucket"].asString());
    }
    if (jsonContent.isMember("key"))
    {
        m_output->SetKey(jsonContent["key"].asString());
    }
    if (jsonContent.isMember("upload_id"))
    {
        m_output->SetUploadID(jsonContent["upload_id"].asString());
    }
    m_bNeedReleaseBody = true;
}

class ListMultipartBuilder:public QsDefaultRequestBuilder < ListMultipartInput >
{
public:
    ListMultipartBuilder(ListMultipartInput * input):QsDefaultRequestBuilder <
        ListMultipartInput > (input)
    {
    };

    virtual ~ ListMultipartBuilder()
    {
    };

    virtual bool CkeckIfInputIsVaild()
    {
        return m_input->CheckIfInputIsVaild();
    };
    virtual Http::QueryParamCollection GetQueryParamCollection();
};

// ListMultipartRequest AddQueryStringParameters.
Http::QueryParamCollection ListMultipartBuilder::GetQueryParamCollection()
{
    Http::QueryParamCollection queryParameters;
    std::stringstream ss;
    std::vector < std::string >::iterator it;
    if (m_input->IsPropHasBeenSet(SETTING_INPUT_LIST_MULTIPART_LIMIT_FLAG))
    {
        ss << m_input->GetLimit();
        queryParameters.insert(Http::HeaderValuePair("limit", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_LIST_MULTIPART_PART_NUMBER_MARKER_FLAG))
    {
        ss << m_input->GetPartNumberMarker();
        queryParameters.
        insert(Http::HeaderValuePair("part_number_marker", ss.str()));
        ss.str("");
    }
    if (m_input->IsPropHasBeenSet(SETTING_INPUT_LIST_MULTIPART_UPLOAD_ID_FLAG))
    {
        ss << m_input->GetUploadID();
        queryParameters.insert(Http::HeaderValuePair("upload_id", ss.str()));
        ss.str("");
    }
    return queryParameters;
}

class ListMultipartUnparker:public QsDefaultResponseUnparker <
    ListMultipartOutput >
{
public:
    ListMultipartUnparker(ListMultipartOutput *
                          output):QsDefaultResponseUnparker <
        ListMultipartOutput > (output)
    {
    };

    virtual ~ ListMultipartUnparker()
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

void ListMultipartUnparker::ParseResponseBody(std::iostream * responseBody)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(*responseBody, jsonContent);
    if (jsonContent.isMember("count"))
    {
        m_output->SetCount(jsonContent["count"].asInt());
    }
    if (jsonContent.isMember("object_parts"))
    {
        std::vector < ObjectPartType > vecObjectParts;
        for (unsigned i = 0; i < jsonContent["object_parts"].size(); ++i)
        {
            vecObjectParts.push_back(jsonContent["object_parts"][i].
                                     toStyledString());
        }
        m_output->SetObjectParts(vecObjectParts);
    }
    m_bNeedReleaseBody = true;
}

class OptionsObjectBuilder:public QsDefaultRequestBuilder < OptionsObjectInput >
{
public:
    OptionsObjectBuilder(OptionsObjectInput * input):QsDefaultRequestBuilder <
        OptionsObjectInput > (input)
    {
    };

    virtual ~ OptionsObjectBuilder()
    {
    };

    virtual bool CkeckIfInputIsVaild()
    {
        return m_input->CheckIfInputIsVaild();
    };
    virtual Http::HeaderValueCollection GetHeaderValueCollection();
};

// OptionsObjectRequest GetRequestSpecificHeaders.
Http::HeaderValueCollection OptionsObjectBuilder::GetHeaderValueCollection()
{
    //TO DO;
    Http::HeaderValueCollection headers;
    std::stringstream ss;
    std::vector < std::string >::iterator it;
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_OPTIONS_OBJECT_ACCESS_CONTROL_REQUEST_HEADERS_FLAG))
    {
        ss << m_input->GetAccessControlRequestHeaders();
        headers.
        insert(Http::
               HeaderValuePair("Access-Control-Request-Headers", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_OPTIONS_OBJECT_ACCESS_CONTROL_REQUEST_METHOD_FLAG))
    {
        ss << m_input->GetAccessControlRequestMethod();
        headers.
        insert(Http::
               HeaderValuePair("Access-Control-Request-Method", ss.str()));
        ss.str("");
    }
    if (m_input->IsPropHasBeenSet(SETTING_INPUT_OPTIONS_OBJECT_ORIGIN_FLAG))
    {
        ss << m_input->GetOrigin();
        headers.insert(Http::HeaderValuePair("Origin", ss.str()));
        ss.str("");
    }
    return headers;
}

class OptionsObjectUnparker:public QsDefaultResponseUnparker <
    OptionsObjectOutput >
{
public:
    OptionsObjectUnparker(OptionsObjectOutput *
                          output):QsDefaultResponseUnparker <
        OptionsObjectOutput > (output)
    {
    };

    virtual ~ OptionsObjectUnparker()
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
    virtual void ParseResponseHeaders(const Http::
                                      HeaderValueCollection &
                                      headerValueCollection);
};

// OptionsObjectRequest ParseResponseHeaders.
void OptionsObjectUnparker::ParseResponseHeaders(const Http::
        HeaderValueCollection &
        headerValueCollection)
{
    const HeaderValueCollection & headers = headerValueCollection;
    HeaderValueCollection::const_iterator AccessControlAllowHeadersIter =
        headers.find("access-control-allow-headers");
    if (AccessControlAllowHeadersIter != headers.end())
    {
        m_output->SetAccessControlAllowHeaders(AccessControlAllowHeadersIter->
                                               second);
    }
    HeaderValueCollection::const_iterator AccessControlAllowMethodsIter =
        headers.find("access-control-allow-methods");
    if (AccessControlAllowMethodsIter != headers.end())
    {
        m_output->SetAccessControlAllowMethods(AccessControlAllowMethodsIter->
                                               second);
    }
    HeaderValueCollection::const_iterator AccessControlAllowOriginIter =
        headers.find("access-control-allow-origin");
    if (AccessControlAllowOriginIter != headers.end())
    {
        m_output->SetAccessControlAllowOrigin(AccessControlAllowOriginIter->
                                              second);
    }
    HeaderValueCollection::const_iterator AccessControlExposeHeadersIter =
        headers.find("access-control-expose-headers");
    if (AccessControlExposeHeadersIter != headers.end())
    {
        m_output->SetAccessControlExposeHeaders(AccessControlExposeHeadersIter->
                                                second);
    }
    HeaderValueCollection::const_iterator AccessControlMaxAgeIter =
        headers.find("access-control-max-age");
    if (AccessControlMaxAgeIter != headers.end())
    {
        m_output->SetAccessControlMaxAge(AccessControlMaxAgeIter->second);
    }
}

class PutObjectBuilder:public QsDefaultRequestBuilder < PutObjectInput >
{
public:
    PutObjectBuilder(PutObjectInput * input):QsDefaultRequestBuilder <
        PutObjectInput > (input)
    {
    };

    virtual ~ PutObjectBuilder()
    {
    };

    virtual bool CkeckIfInputIsVaild()
    {
        return m_input->CheckIfInputIsVaild();
    };
    virtual Http::HeaderValueCollection GetHeaderValueCollection();
    virtual std::iostream * GetRequestBody();
};

// PutObjectRequest GetRequestSpecificHeaders.
Http::HeaderValueCollection PutObjectBuilder::GetHeaderValueCollection()
{
    //TO DO;
    Http::HeaderValueCollection headers;
    std::stringstream ss;
    std::vector < std::string >::iterator it;
    if (m_input->IsPropHasBeenSet(SETTING_INPUT_PUT_OBJECT_CONTENT_LENGTH_FLAG))
    {
        ss << m_input->GetContentLength();
        headers.insert(Http::HeaderValuePair("Content-Length", ss.str()));
        ss.str("");
    }
    if (m_input->IsPropHasBeenSet(SETTING_INPUT_PUT_OBJECT_CONTENT_MD5_FLAG))
    {
        ss << m_input->GetContentMD5();
        headers.insert(Http::HeaderValuePair("Content-MD5", ss.str()));
        ss.str("");
    }
    if (m_input->IsPropHasBeenSet(SETTING_INPUT_PUT_OBJECT_CONTENT_TYPE_FLAG))
    {
        ss << m_input->GetContentType();
        headers.insert(Http::HeaderValuePair("Content-Type", ss.str()));
        ss.str("");
    }
    if (m_input->IsPropHasBeenSet(SETTING_INPUT_PUT_OBJECT_EXPECT_FLAG))
    {
        ss << m_input->GetExpect();
        headers.insert(Http::HeaderValuePair("Expect", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_PUT_OBJECT_X_QS_COPY_SOURCE_FLAG))
    {
        ss << m_input->GetXQSCopySource();
        headers.insert(Http::HeaderValuePair("X-QS-Copy-Source", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_PUT_OBJECT_X_QS_COPY_SOURCE_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG))
    {
        ss << m_input->GetXQSCopySourceEncryptionCustomerAlgorithm();
        headers.
        insert(Http::
               HeaderValuePair
               ("X-QS-Copy-Source-Encryption-Customer-Algorithm",
                ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_PUT_OBJECT_X_QS_COPY_SOURCE_ENCRYPTION_CUSTOMER_KEY_FLAG))
    {
        ss << m_input->GetXQSCopySourceEncryptionCustomerKey();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Copy-Source-Encryption-Customer-Key",
                               ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_PUT_OBJECT_X_QS_COPY_SOURCE_ENCRYPTION_CUSTOMER_KEY_MD5_FLAG))
    {
        ss << m_input->GetXQSCopySourceEncryptionCustomerKeyMD5();
        headers.
        insert(Http::
               HeaderValuePair
               ("X-QS-Copy-Source-Encryption-Customer-Key-MD5", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_PUT_OBJECT_X_QS_COPY_SOURCE_IF_MATCH_FLAG))
    {
        ss << m_input->GetXQSCopySourceIfMatch();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Copy-Source-If-Match", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_PUT_OBJECT_X_QS_COPY_SOURCE_IF_MODIFIED_SINCE_FLAG))
    {
        ss << m_input->GetXQSCopySourceIfModifiedSince();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Copy-Source-If-Modified-Since",
                               ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_PUT_OBJECT_X_QS_COPY_SOURCE_IF_NONE_MATCH_FLAG))
    {
        ss << m_input->GetXQSCopySourceIfNoneMatch();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Copy-Source-If-None-Match", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_PUT_OBJECT_X_QS_COPY_SOURCE_IF_UNMODIFIED_SINCE_FLAG))
    {
        ss << m_input->GetXQSCopySourceIfUnmodifiedSince();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Copy-Source-If-Unmodified-Since",
                               ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_PUT_OBJECT_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG))
    {
        ss << m_input->GetXQSEncryptionCustomerAlgorithm();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Encryption-Customer-Algorithm",
                               ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_PUT_OBJECT_X_QS_ENCRYPTION_CUSTOMER_KEY_FLAG))
    {
        ss << m_input->GetXQSEncryptionCustomerKey();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Encryption-Customer-Key", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_PUT_OBJECT_X_QS_ENCRYPTION_CUSTOMER_KEY_MD5_FLAG))
    {
        ss << m_input->GetXQSEncryptionCustomerKeyMD5();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Encryption-Customer-Key-MD5",
                               ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_PUT_OBJECT_X_QS_FETCH_IF_UNMODIFIED_SINCE_FLAG))
    {
        ss << m_input->GetXQSFetchIfUnmodifiedSince();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Fetch-If-Unmodified-Since", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_PUT_OBJECT_X_QS_FETCH_SOURCE_FLAG))
    {
        ss << m_input->GetXQSFetchSource();
        headers.insert(Http::HeaderValuePair("X-QS-Fetch-Source", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_PUT_OBJECT_X_QS_MOVE_SOURCE_FLAG))
    {
        ss << m_input->GetXQSMoveSource();
        headers.insert(Http::HeaderValuePair("X-QS-Move-Source", ss.str()));
        ss.str("");
    }
    return headers;
}

// PutObjectRequest GetRequestBody.
std::iostream * PutObjectBuilder::GetRequestBody()
{
    return m_input->GetBody();
}

class PutObjectUnparker:public QsDefaultResponseUnparker < PutObjectOutput >
{
public:
    PutObjectUnparker(PutObjectOutput * output):QsDefaultResponseUnparker <
        PutObjectOutput > (output)
    {
    };

    virtual ~ PutObjectUnparker()
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
        int expectedRespCode[1] = { 201, };
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
    virtual void ParseResponseHeaders(const Http::
                                      HeaderValueCollection &
                                      headerValueCollection);
};

// PutObjectRequest ParseResponseHeaders.
void PutObjectUnparker::ParseResponseHeaders(const Http::
        HeaderValueCollection &
        headerValueCollection)
{
    const HeaderValueCollection & headers = headerValueCollection;
    HeaderValueCollection::const_iterator ETagIter = headers.find("etag");
    if (ETagIter != headers.end())
    {
        m_output->SetETag(ETagIter->second);
    }
    HeaderValueCollection::const_iterator XQSEncryptionCustomerAlgorithmIter =
        headers.find("x-qs-encryption-customer-algorithm");
    if (XQSEncryptionCustomerAlgorithmIter != headers.end())
    {
        m_output->
        SetXQSEncryptionCustomerAlgorithm
        (XQSEncryptionCustomerAlgorithmIter->second);
    }
}

class UploadMultipartBuilder:public QsDefaultRequestBuilder <
    UploadMultipartInput >
{
public:
    UploadMultipartBuilder(UploadMultipartInput *
                           input):QsDefaultRequestBuilder <
        UploadMultipartInput > (input)
    {
    };

    virtual ~ UploadMultipartBuilder()
    {
    };

    virtual bool CkeckIfInputIsVaild()
    {
        return m_input->CheckIfInputIsVaild();
    };
    virtual Http::HeaderValueCollection GetHeaderValueCollection();
    virtual Http::QueryParamCollection GetQueryParamCollection();
    virtual std::iostream * GetRequestBody();
};

// UploadMultipartRequest GetRequestSpecificHeaders.
Http::HeaderValueCollection UploadMultipartBuilder::GetHeaderValueCollection()
{
    //TO DO;
    Http::HeaderValueCollection headers;
    std::stringstream ss;
    std::vector < std::string >::iterator it;
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_UPLOAD_MULTIPART_CONTENT_LENGTH_FLAG))
    {
        ss << m_input->GetContentLength();
        headers.insert(Http::HeaderValuePair("Content-Length", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_UPLOAD_MULTIPART_CONTENT_MD5_FLAG))
    {
        ss << m_input->GetContentMD5();
        headers.insert(Http::HeaderValuePair("Content-MD5", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_RANGE_FLAG))
    {
        ss << m_input->GetXQSCopyRange();
        headers.insert(Http::HeaderValuePair("X-QS-Copy-Range", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_SOURCE_FLAG))
    {
        ss << m_input->GetXQSCopySource();
        headers.insert(Http::HeaderValuePair("X-QS-Copy-Source", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_SOURCE_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG))
    {
        ss << m_input->GetXQSCopySourceEncryptionCustomerAlgorithm();
        headers.
        insert(Http::
               HeaderValuePair
               ("X-QS-Copy-Source-Encryption-Customer-Algorithm",
                ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_SOURCE_ENCRYPTION_CUSTOMER_KEY_FLAG))
    {
        ss << m_input->GetXQSCopySourceEncryptionCustomerKey();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Copy-Source-Encryption-Customer-Key",
                               ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_SOURCE_ENCRYPTION_CUSTOMER_KEY_MD5_FLAG))
    {
        ss << m_input->GetXQSCopySourceEncryptionCustomerKeyMD5();
        headers.
        insert(Http::
               HeaderValuePair
               ("X-QS-Copy-Source-Encryption-Customer-Key-MD5", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_SOURCE_IF_MATCH_FLAG))
    {
        ss << m_input->GetXQSCopySourceIfMatch();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Copy-Source-If-Match", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_SOURCE_IF_MODIFIED_SINCE_FLAG))
    {
        ss << m_input->GetXQSCopySourceIfModifiedSince();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Copy-Source-If-Modified-Since",
                               ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_SOURCE_IF_NONE_MATCH_FLAG))
    {
        ss << m_input->GetXQSCopySourceIfNoneMatch();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Copy-Source-If-None-Match", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_SOURCE_IF_UNMODIFIED_SINCE_FLAG))
    {
        ss << m_input->GetXQSCopySourceIfUnmodifiedSince();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Copy-Source-If-Unmodified-Since",
                               ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_UPLOAD_MULTIPART_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG))
    {
        ss << m_input->GetXQSEncryptionCustomerAlgorithm();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Encryption-Customer-Algorithm",
                               ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_UPLOAD_MULTIPART_X_QS_ENCRYPTION_CUSTOMER_KEY_FLAG))
    {
        ss << m_input->GetXQSEncryptionCustomerKey();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Encryption-Customer-Key", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet
            (SETTING_INPUT_UPLOAD_MULTIPART_X_QS_ENCRYPTION_CUSTOMER_KEY_MD5_FLAG))
    {
        ss << m_input->GetXQSEncryptionCustomerKeyMD5();
        headers.
        insert(Http::
               HeaderValuePair("X-QS-Encryption-Customer-Key-MD5",
                               ss.str()));
        ss.str("");
    }
    return headers;
}

// UploadMultipartRequest AddQueryStringParameters.
Http::QueryParamCollection UploadMultipartBuilder::GetQueryParamCollection()
{
    Http::QueryParamCollection queryParameters;
    std::stringstream ss;
    std::vector < std::string >::iterator it;
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_UPLOAD_MULTIPART_PART_NUMBER_FLAG))
    {
        ss << m_input->GetPartNumber();
        queryParameters.insert(Http::HeaderValuePair("part_number", ss.str()));
        ss.str("");
    }
    if (m_input->
            IsPropHasBeenSet(SETTING_INPUT_UPLOAD_MULTIPART_UPLOAD_ID_FLAG))
    {
        ss << m_input->GetUploadID();
        queryParameters.insert(Http::HeaderValuePair("upload_id", ss.str()));
        ss.str("");
    }
    return queryParameters;
}

// UploadMultipartRequest GetRequestBody.
std::iostream * UploadMultipartBuilder::GetRequestBody()
{
    return m_input->GetBody();
}

class UploadMultipartUnparker:public QsDefaultResponseUnparker <
    UploadMultipartOutput >
{
public:
    UploadMultipartUnparker(UploadMultipartOutput *
                            output):QsDefaultResponseUnparker <
        UploadMultipartOutput > (output)
    {
    };

    virtual ~ UploadMultipartUnparker()
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
        int expectedRespCode[1] = { 201, };
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
    virtual void ParseResponseHeaders(const Http::
                                      HeaderValueCollection &
                                      headerValueCollection);
};

// UploadMultipartRequest ParseResponseHeaders.
void UploadMultipartUnparker::ParseResponseHeaders(const Http::
        HeaderValueCollection &
        headerValueCollection)
{
    const HeaderValueCollection & headers = headerValueCollection;
    HeaderValueCollection::const_iterator ETagIter = headers.find("etag");
    if (ETagIter != headers.end())
    {
        m_output->SetETag(ETagIter->second);
    }
    HeaderValueCollection::const_iterator XQSContentCopyRangeIter =
        headers.find("x-qs-content-copy-range");
    if (XQSContentCopyRangeIter != headers.end())
    {
        m_output->SetXQSContentCopyRange(XQSContentCopyRangeIter->second);
    }
    HeaderValueCollection::const_iterator XQSEncryptionCustomerAlgorithmIter =
        headers.find("x-qs-encryption-customer-algorithm");
    if (XQSEncryptionCustomerAlgorithmIter != headers.end())
    {
        m_output->
        SetXQSEncryptionCustomerAlgorithm
        (XQSEncryptionCustomerAlgorithmIter->second);
    }
}

// +--------------------------------------------------------------------
// |           SDK API Operation Source
// +--------------------------------------------------------------------

QsError Bucket::DeleteBucket(DeleteBucketInput & input,
                             DeleteBucketOutput & output)
{
    Properties properties(m_properties);
    Operation operation(&m_qsConfig, properties,
                        "DELETE Bucket", HTTP_DELETE, "/<bucket-name>");
    DeleteBucketBuilder bulider(&input);
    DeleteBucketUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::DeleteBucketCORS(DeleteBucketCORSInput & input,
                                 DeleteBucketCORSOutput & output)
{
    Properties properties(m_properties);
    Operation operation(&m_qsConfig, properties,
                        "DELETE Bucket CORS",
                        HTTP_DELETE, "/<bucket-name>?cors");
    DeleteBucketCORSBuilder bulider(&input);
    DeleteBucketCORSUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::
DeleteBucketExternalMirror(DeleteBucketExternalMirrorInput & input,
                           DeleteBucketExternalMirrorOutput & output)
{
    Properties properties(m_properties);
    Operation operation(&m_qsConfig, properties,
                        "DELETE Bucket External Mirror",
                        HTTP_DELETE, "/<bucket-name>?mirror");
    DeleteBucketExternalMirrorBuilder bulider(&input);
    DeleteBucketExternalMirrorUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::DeleteBucketPolicy(DeleteBucketPolicyInput & input,
                                   DeleteBucketPolicyOutput & output)
{
    Properties properties(m_properties);
    Operation operation(&m_qsConfig, properties,
                        "DELETE Bucket Policy",
                        HTTP_DELETE, "/<bucket-name>?policy");
    DeleteBucketPolicyBuilder bulider(&input);
    DeleteBucketPolicyUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::DeleteMultipleObjects(DeleteMultipleObjectsInput & input,
                                      DeleteMultipleObjectsOutput & output)
{
    Properties properties(m_properties);
    Operation operation(&m_qsConfig, properties,
                        "Delete Multiple Objects",
                        HTTP_POST, "/<bucket-name>?delete");
    DeleteMultipleObjectsBuilder bulider(&input);
    DeleteMultipleObjectsUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::GetBucketACL(GetBucketACLInput & input,
                             GetBucketACLOutput & output)
{
    Properties properties(m_properties);
    Operation operation(&m_qsConfig, properties,
                        "GET Bucket ACL", HTTP_GET, "/<bucket-name>?acl");
    GetBucketACLBuilder bulider(&input);
    GetBucketACLUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::GetBucketCORS(GetBucketCORSInput & input,
                              GetBucketCORSOutput & output)
{
    Properties properties(m_properties);
    Operation operation(&m_qsConfig, properties,
                        "GET Bucket CORS", HTTP_GET, "/<bucket-name>?cors");
    GetBucketCORSBuilder bulider(&input);
    GetBucketCORSUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::GetBucketExternalMirror(GetBucketExternalMirrorInput & input,
                                        GetBucketExternalMirrorOutput & output)
{
    Properties properties(m_properties);
    Operation operation(&m_qsConfig, properties,
                        "GET Bucket External Mirror",
                        HTTP_GET, "/<bucket-name>?mirror");
    GetBucketExternalMirrorBuilder bulider(&input);
    GetBucketExternalMirrorUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::GetBucketPolicy(GetBucketPolicyInput & input,
                                GetBucketPolicyOutput & output)
{
    Properties properties(m_properties);
    Operation operation(&m_qsConfig, properties,
                        "GET Bucket Policy", HTTP_GET, "/<bucket-name>?policy");
    GetBucketPolicyBuilder bulider(&input);
    GetBucketPolicyUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::GetBucketStatistics(GetBucketStatisticsInput & input,
                                    GetBucketStatisticsOutput & output)
{
    Properties properties(m_properties);
    Operation operation(&m_qsConfig, properties,
                        "GET Bucket Statistics",
                        HTTP_GET, "/<bucket-name>?stats");
    GetBucketStatisticsBuilder bulider(&input);
    GetBucketStatisticsUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::HeadBucket(HeadBucketInput & input, HeadBucketOutput & output)
{
    Properties properties(m_properties);
    Operation operation(&m_qsConfig, properties,
                        "HEAD Bucket", HTTP_HEAD, "/<bucket-name>");
    HeadBucketBuilder bulider(&input);
    HeadBucketUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::ListMultipartUploads(ListMultipartUploadsInput & input,
                                     ListMultipartUploadsOutput & output)
{
    Properties properties(m_properties);
    Operation operation(&m_qsConfig, properties,
                        "List Multipart Uploads",
                        HTTP_GET, "/<bucket-name>?uploads");
    ListMultipartUploadsBuilder bulider(&input);
    ListMultipartUploadsUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::ListObjects(ListObjectsInput & input,
                            ListObjectsOutput & output)
{
    Properties properties(m_properties);
    Operation operation(&m_qsConfig, properties,
                        "GET Bucket (List Objects)",
                        HTTP_GET, "/<bucket-name>");
    ListObjectsBuilder bulider(&input);
    ListObjectsUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::PutBucket(PutBucketInput & input, PutBucketOutput & output)
{
    Properties properties(m_properties);
    Operation operation(&m_qsConfig, properties,
                        "PUT Bucket", HTTP_PUT, "/<bucket-name>");
    PutBucketBuilder bulider(&input);
    PutBucketUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::PutBucketACL(PutBucketACLInput & input,
                             PutBucketACLOutput & output)
{
    Properties properties(m_properties);
    Operation operation(&m_qsConfig, properties,
                        "PUT Bucket ACL", HTTP_PUT, "/<bucket-name>?acl");
    PutBucketACLBuilder bulider(&input);
    PutBucketACLUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::PutBucketCORS(PutBucketCORSInput & input,
                              PutBucketCORSOutput & output)
{
    Properties properties(m_properties);
    Operation operation(&m_qsConfig, properties,
                        "PUT Bucket CORS", HTTP_PUT, "/<bucket-name>?cors");
    PutBucketCORSBuilder bulider(&input);
    PutBucketCORSUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::PutBucketExternalMirror(PutBucketExternalMirrorInput & input,
                                        PutBucketExternalMirrorOutput & output)
{
    Properties properties(m_properties);
    Operation operation(&m_qsConfig, properties,
                        "PUT Bucket External Mirror",
                        HTTP_PUT, "/<bucket-name>?mirror");
    PutBucketExternalMirrorBuilder bulider(&input);
    PutBucketExternalMirrorUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::PutBucketPolicy(PutBucketPolicyInput & input,
                                PutBucketPolicyOutput & output)
{
    Properties properties(m_properties);
    Operation operation(&m_qsConfig, properties,
                        "PUT Bucket Policy", HTTP_PUT, "/<bucket-name>?policy");
    PutBucketPolicyBuilder bulider(&input);
    PutBucketPolicyUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

// +--------------------------------------------------------------------
// |           SDK API Operation Source
// +--------------------------------------------------------------------

QsError Bucket::AbortMultipartUpload(std::string objectKey,
                                     AbortMultipartUploadInput & input,
                                     AbortMultipartUploadOutput & output)
{
    Properties properties(m_properties);
    properties.ObjectKey = objectKey;
    Operation operation(&m_qsConfig, properties,
                        "Abort Multipart Upload",
                        HTTP_DELETE, "/<bucket-name>/<object-key>");
    AbortMultipartUploadBuilder bulider(&input);
    AbortMultipartUploadUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::CompleteMultipartUpload(std::string objectKey,
                                        CompleteMultipartUploadInput & input,
                                        CompleteMultipartUploadOutput & output)
{
    Properties properties(m_properties);
    properties.ObjectKey = objectKey;
    Operation operation(&m_qsConfig, properties,
                        "Complete multipart upload",
                        HTTP_POST, "/<bucket-name>/<object-key>");
    CompleteMultipartUploadBuilder bulider(&input);
    CompleteMultipartUploadUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::DeleteObject(std::string objectKey, DeleteObjectInput & input,
                             DeleteObjectOutput & output)
{
    Properties properties(m_properties);
    properties.ObjectKey = objectKey;
    Operation operation(&m_qsConfig, properties,
                        "DELETE Object",
                        HTTP_DELETE, "/<bucket-name>/<object-key>");
    DeleteObjectBuilder bulider(&input);
    DeleteObjectUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::GetObject(std::string objectKey, GetObjectInput & input,
                          GetObjectOutput & output)
{
    Properties properties(m_properties);
    properties.ObjectKey = objectKey;
    Operation operation(&m_qsConfig, properties,
                        "GET Object", HTTP_GET, "/<bucket-name>/<object-key>");
    GetObjectBuilder bulider(&input);
    GetObjectUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::HeadObject(std::string objectKey, HeadObjectInput & input,
                           HeadObjectOutput & output)
{
    Properties properties(m_properties);
    properties.ObjectKey = objectKey;
    Operation operation(&m_qsConfig, properties,
                        "HEAD Object",
                        HTTP_HEAD, "/<bucket-name>/<object-key>");
    HeadObjectBuilder bulider(&input);
    HeadObjectUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::ImageProcess(std::string objectKey, ImageProcessInput & input,
                             ImageProcessOutput & output)
{
    Properties properties(m_properties);
    properties.ObjectKey = objectKey;
    Operation operation(&m_qsConfig, properties,
                        "Image Process",
                        HTTP_GET, "/<bucket-name>/<object-key>?image");
    ImageProcessBuilder bulider(&input);
    ImageProcessUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::InitiateMultipartUpload(std::string objectKey,
                                        InitiateMultipartUploadInput & input,
                                        InitiateMultipartUploadOutput & output)
{
    Properties properties(m_properties);
    properties.ObjectKey = objectKey;
    Operation operation(&m_qsConfig, properties,
                        "Initiate Multipart Upload",
                        HTTP_POST, "/<bucket-name>/<object-key>?uploads");
    InitiateMultipartUploadBuilder bulider(&input);
    InitiateMultipartUploadUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::ListMultipart(std::string objectKey, ListMultipartInput & input,
                              ListMultipartOutput & output)
{
    Properties properties(m_properties);
    properties.ObjectKey = objectKey;
    Operation operation(&m_qsConfig, properties,
                        "List Multipart",
                        HTTP_GET, "/<bucket-name>/<object-key>");
    ListMultipartBuilder bulider(&input);
    ListMultipartUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::OptionsObject(std::string objectKey, OptionsObjectInput & input,
                              OptionsObjectOutput & output)
{
    Properties properties(m_properties);
    properties.ObjectKey = objectKey;
    Operation operation(&m_qsConfig, properties,
                        "OPTIONS Object",
                        HTTP_OPTIONS, "/<bucket-name>/<object-key>");
    OptionsObjectBuilder bulider(&input);
    OptionsObjectUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::PutObject(std::string objectKey, PutObjectInput & input,
                          PutObjectOutput & output)
{
    Properties properties(m_properties);
    properties.ObjectKey = objectKey;
    Operation operation(&m_qsConfig, properties,
                        "PUT Object", HTTP_PUT, "/<bucket-name>/<object-key>");
    PutObjectBuilder bulider(&input);
    PutObjectUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}

QsError Bucket::UploadMultipart(std::string objectKey,
                                UploadMultipartInput & input,
                                UploadMultipartOutput & output)
{
    Properties properties(m_properties);
    properties.ObjectKey = objectKey;
    Operation operation(&m_qsConfig, properties,
                        "Upload Multipart",
                        HTTP_PUT, "/<bucket-name>/<object-key>");
    UploadMultipartBuilder bulider(&input);
    UploadMultipartUnparker unparker(&output);
    QsRequest request(operation, &bulider, &unparker);
    return request.GetResponse();
}
