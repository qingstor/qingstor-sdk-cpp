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

#include "HttpCommon.h"

namespace QingStor
{
namespace Http
{
namespace HttpMethodMapper
{
const char *GetNameForHttpMethod(HttpMethod httpMethod)
{
    switch (httpMethod)
    {
    case HTTP_GET:
        return "GET";
    case HTTP_POST:
        return "POST";
    case HTTP_DELETE:
        return "DELETE";
    case HTTP_PUT:
        return "PUT";
    case HTTP_HEAD:
        return "HEAD";
    case HTTP_PATCH:
        return "PATCH";
    default:
        return "GET";
    }
}
}

namespace SchemeMapper
{

/**
* Converts a Scheme instance to a String.
*/
QS_SDK_API const char *ToString(Scheme scheme)
{
    switch (scheme)
    {
    case HTTP:
        return "http";
    case HTTPS:
        return "https";
    default:
        return "http";
    }
}

/**
* Converts a string instance to a Scheme. Defaults to https.
*/
QS_SDK_API Scheme FromString(const char *name)
{
    std::string trimmedString = QingStor::Utils::StringUtils::Trim(name);
    std::string loweredTrimmedString = QingStor::Utils::StringUtils::ToLower(trimmedString.c_str());
    if (loweredTrimmedString == "http")
    {
        return HTTP;
    }
    //this branch is technically unneeded, but it is here so we don't have a subtle bug
    //creep in as we extend this enum.
    else if (loweredTrimmedString == "https")
    {
        return HTTPS;
    }
    return HTTPS;
}
} // namespace SchemeMapper

const char *DATE_HEADER = "Date";
const char *CONTENT_LENGTH_HEADER = "Content-Length";
const char *CONTENT_TYPE_HEADER = "Content-Type";
const char *CONTENT_MD5_HEADER = "Content-MD5";
const char *AUTHORIZATION_HEADER = "Authorization";

} // namespace Http
} // namespace QingStor
