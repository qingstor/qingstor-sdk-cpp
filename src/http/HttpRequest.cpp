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

#include "http/HttpRequest.h"
#include "StringUtils.h"
#include <algorithm>

using namespace QingStor::Utils;
using namespace QingStor::Http;

HttpRequest::HttpRequest(HttpMethod method, URI uri)
    : bodyStream(NULL), m_uri(uri), m_method(method), headerMap()
{
    std::string queryString = uri.GetQueryString();
    if("" != queryString)
    {
        SetQueryStringParameter(queryString.substr(1, queryString.length()), "");
    }
}

const std::string  HttpRequest::GetHeaderValue(const char* headerName) const
{
    if (headerMap.find(StringUtils::ToLower(headerName)) != headerMap.end())
    {
        return headerMap.find(StringUtils::ToLower(headerName))->second;
    }
    else
    {
        return "";
    }
}

void HttpRequest::SetHeaderValue(const char* headerName, const std::string& headerValue)
{
    headerMap[StringUtils::ToLower(headerName)] = StringUtils::Trim(headerValue.c_str());
}

void HttpRequest::SetHeaderValue(const std::string& headerName, const std::string& headerValue)
{
    headerMap[StringUtils::ToLower(headerName.c_str())] = StringUtils::Trim(headerValue.c_str());
}

void HttpRequest::SetQueryStringParameter(const char* name, const std::string& value)
{
    queryMap[StringUtils::ToLower(name)] = StringUtils::Trim(value.c_str());
    m_uri.AddQueryStringParameter(name, value);
}

void HttpRequest::SetQueryStringParameter(const std::string& name, const std::string& value)
{
    queryMap[StringUtils::ToLower(name.c_str())] = StringUtils::Trim(value.c_str());
    m_uri.AddQueryStringParameter(name.c_str(), value);
}

void HttpRequest::DeleteHeader(const char* headerName)
{
    headerMap.erase(StringUtils::ToLower(headerName));
}

bool HttpRequest::HasHeader(const char* headerName) const
{
    return headerMap.find(StringUtils::ToLower(headerName)) != headerMap.end();
}
