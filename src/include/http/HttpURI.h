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
#include "HttpCommon.h"
#include <stdint.h>
#include <string>
#include <map>
#include <list>

namespace QingStor
{
namespace Http
{
extern QS_SDK_API const char *SEPARATOR;

class QS_SDK_API URI
{
public:

    URI(const std::string &endpoint, const std::string &path, const std::string &queryString = "") ;

    /**
    * Gets the raw query string including "?"
    */
    inline const std::string &GetQueryString() const
    {
        return m_queryString;
    }

    /**
    * Gets the uri with every path portion encoded
    */
    inline std::string GetURLEncodedPath() const
    {
        return URLEncodePath(m_path);
    }

    /**
    * Cannonicalizes the query string with filter.
    */
    std::string GetFormParameters() const;

    /**
    * Adds query string parameter to underlying query string.
    */
    void AddQueryStringParameter(const char *key, const std::string &value);

    /**
    * Get Encoded URL
    */
    std::string GetURIString() const;

    /**
     * URLEncodes encode portions of path (doesn't encode "/")
     */
    static std::string URLEncodePath(const std::string &path);

private:
    std::string m_endpoint;
    std::string m_path;
    std::string m_queryString;
};

} // namespace Http
} // namespace QingStor
