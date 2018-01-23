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

#include <http/HttpURI.h>
#include "HttpCommon.h"
#include "StringUtils.h"
#include <sstream>
#include <stdlib.h>
#include <cctype>
#include <cassert>
#include <algorithm>

using namespace QingStor::Http;
using namespace QingStor::Utils;

namespace QingStor
{
namespace Http
{
const char *SEPARATOR = "://";
}
} // namespace QingStor

URI::URI(const std::string &endpoint, const std::string &path, const std::string &queryString) : m_endpoint(endpoint), m_path(path), m_queryString(queryString)
{
}

std::string URI::URLEncodePath(const std::string &path)
{
    std::vector<std::string> pathParts = StringUtils::Split(path, '/');
    std::stringstream ss;
    for (std::vector<std::string>::iterator iter = pathParts.begin(); iter != pathParts.end(); ++iter)
    {
        ss << '/' << StringUtils::URLEncode(iter->c_str());
    }
    //if the last character was also a slash, then add that back here.
    if ("" != path && path[path.length() - 1] == '/')
    {
        ss << '/';
    }
    return ss.str();
}

void URI::AddQueryStringParameter(const char *key, const std::string &value)
{
    if (m_queryString.size() <= 0)
    {
        m_queryString.append("?");
    }
    else
    {
        m_queryString.append("&");
    }
    m_queryString.append(StringUtils::URLEncode(key) + "=" + StringUtils::URLEncode(value.c_str()));
}

std::string URI::GetURIString() const
{
    std::stringstream ss;
    ss << m_endpoint << URLEncodePath(m_path) << m_queryString;
    return ss.str();
}

std::string URI::GetFormParameters() const
{
    if (m_queryString.length() == 0)
    {
        return "";
    }
    else
    {
        return m_queryString.substr(1);
    }
}
