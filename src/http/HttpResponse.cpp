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

#include <http/HttpResponse.h>
#include "HttpCommon.h"
#include "StringUtils.h"
#include <map>

using namespace QingStor::Http;
using namespace QingStor::Utils;

HeaderValueCollection HttpResponse::GetHeaders()
{
    return headerMap;
}

bool HttpResponse::HasHeader(const char *headerName) const
{
    return headerMap.find(StringUtils::ToLower(headerName)) != headerMap.end();
}

std::string HttpResponse::GetHeader(const std::string &headerName) const
{
    std::map<std::string, std::string>::const_iterator foundValue = headerMap.find(StringUtils::ToLower(headerName.c_str()));
    if (foundValue == headerMap.end())
    {
        return "";
    }
    else
    {
        return foundValue->second;
    }
}

void HttpResponse::AddHeader(const std::string &headerName, const std::string &headerValue)
{
    headerMap[StringUtils::ToLower(headerName.c_str())] = headerValue;
}
