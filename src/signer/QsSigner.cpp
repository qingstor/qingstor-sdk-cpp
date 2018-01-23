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
#include "signer/QsSigner.h"
#include "StringUtils.h"
#include "HttpCommon.h"
#include "utils/QsEncoder.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <time.h>

#include <openssl/hmac.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <openssl/sha.h>

using namespace QingStor;
using namespace QingStor::Utils;
using namespace QingStor::Http;

static const char* LINE_BREAK = "\n";
static const char* CANONICALHEADERS_PREFIX = "x-qs-";

static const int  counToSign = 15;
static std::string pramaterToSign[counToSign] =
{
    "acl",
    "cors",
    "delete",
    "mirror",
    "part_number",
    "policy",
    "stats",
    "upload_id",
    "uploads",
    "response-expires",
    "response-cache-control",
    "response-content-type",
    "response-content-language",
    "response-content-encoding",
    "response-content-disposition",
};

std::string QsSigner::GetTimestamp() const
{
    time_t timestamp;
    struct tm *tm_info;
    char timebuf[65];
    timestamp = time(NULL);
    tm_info = gmtime(&timestamp);
    strftime(timebuf, 64, "%a, %d %b %Y %H:%M:%S GMT", tm_info);
    return std::string(timebuf);
}

QsError QsSigner::SignRequest(Http::HttpRequest* request) const
{
    /* SHA_DIGEST_LENGTH is 32 */
    char tmpbuf[33];
    std::string timestamp = GetTimestamp();
    request->SetHeaderValue(DATE_HEADER, timestamp);
    std::string stringToSign = BuildStringToSign(request);
    Encoder::sha256hmac(stringToSign.c_str(), tmpbuf, m_strSecretAccessKey.c_str());
    std::string signature = Encoder::Base64Encode(tmpbuf, 32);  // SHA256_DIGEST_LENGHT is 32
    std::string authorization = "QS " + m_AccessKeyID + ":" + signature;
    request->SetHeaderValue(AUTHORIZATION_HEADER, authorization);
    return QS_ERR_NO_ERROR;
}


std::string QsSigner::BuildStringToSign(Http::HttpRequest* request)  const
{
    std::string stringToSign;
    std::string canonicalizedHeaders;
    std::string canonicalizedResource;
    stringToSign += HttpMethodMapper::GetNameForHttpMethod(request->GetMethod());
    stringToSign += LINE_BREAK;
    stringToSign += request->GetHeaderValue(CONTENT_MD5_HEADER);
    stringToSign += LINE_BREAK;
    stringToSign += request->GetHeaderValue(CONTENT_TYPE_HEADER);
    stringToSign += LINE_BREAK;
    stringToSign += request->GetHeaderValue(DATE_HEADER);
    stringToSign += LINE_BREAK;
    canonicalizedHeaders = BuildCanonicalizedHeaders(request->GetHeaders());
    stringToSign += canonicalizedHeaders;
    canonicalizedResource = BuildCanonicalizedResource(request->GetQueries(), request->GetURLEncodedPath());
    stringToSign += canonicalizedResource;
    LOG_DEBUG << "QingStor string to sign:" << stringToSign;
    return stringToSign;
}

std::string QsSigner::BuildCanonicalizedHeaders(Http::HeaderValueCollection headers)  const
{
    std::stringstream ssCanonicalHeaders;
    std::vector<std::string> arrayCanonicalHeaders;
    for(HeaderValueCollection::iterator it = headers.begin(); it != headers.end(); it++)
    {
        // skip header wiht "" value
        if ("" != it->second)
        {
            std::string strHeaderKey = StringUtils::ToLower(it->first.c_str());
            if (StringUtils::HasPrefix(strHeaderKey, CANONICALHEADERS_PREFIX))
            {
                arrayCanonicalHeaders.push_back(strHeaderKey);
            }
        }
    }
    // sort with from small to big, Alphabetic order  
    std::sort(arrayCanonicalHeaders.begin(), arrayCanonicalHeaders.end(), std::less<std::string>());
    for(std::vector<std::string>::iterator it = arrayCanonicalHeaders.begin(); it != arrayCanonicalHeaders.end(); it++)
    {
        ssCanonicalHeaders << *it << ":" << headers[*it] << LINE_BREAK;
    }
    return ssCanonicalHeaders.str();
}

std::string QsSigner::BuildCanonicalizedResource(QueryParamCollection queryMap, std::string urlEncodedPath)  const
{
    // filter
    std::vector<std::string> arrayQueryParams;
    for (QueryParamCollection::iterator iter = queryMap.begin();
            iter != queryMap.end(); ++iter)
    {
        bool isParameterToSigner = false;
        for (int i = 0; i < counToSign; i++)
        {
            if (iter->first == pramaterToSign[i])
            {
                // chose to sign
                isParameterToSigner = true;
                break;
            }
        }
        if (!isParameterToSigner)
        {
            continue;
        }
        arrayQueryParams.push_back(iter->first);
    }
    std::stringstream signingStringStream;
    signingStringStream << urlEncodedPath;
    bool first = true;
    // sort with from small to big, Alphabetic order
    std::sort(arrayQueryParams.begin(), arrayQueryParams.end(), std::less<std::string>());
    for(std::vector<std::string>::iterator it = arrayQueryParams.begin(); it != arrayQueryParams.end(); it++)
    {
        if (!first)
        {
            signingStringStream << "&";
        }
        else
        {
            signingStringStream << "?";
        }
        first = false;
        std::string queryName = *it;
        std::string queryValue = queryMap[queryName];
        signingStringStream << queryName;
        if ("" != queryValue)
        {
            signingStringStream << "=";
            signingStringStream << queryValue;
        }
    }
    return signingStringStream.str();
}