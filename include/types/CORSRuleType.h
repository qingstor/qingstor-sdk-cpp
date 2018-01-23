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

#include "../QsBaseType.h"
#include <string>

// Headers of CustomizedType.

#ifdef BUILD_C_STYLE_INTERFACE
#include "../service_with_c_style/types/CORSRuleType.h"
#endif							// BUILD_C_STYLE_INTERFACE

// Allowed origin'flag
#define SETTING_CORS_RULE_ALLOWED_ORIGIN_FLAG 0x1

// Expose headers'flag
#define SETTING_CORS_RULE_EXPOSE_HEADERS_FLAG 0x2

// Max age seconds'flag
#define SETTING_CORS_RULE_MAX_AGE_SECONDS_FLAG 0x4

// Allowed headers'flag
#define SETTING_CORS_RULE_ALLOWED_HEADERS_FLAG 0x8

// Allowed methods'flag
#define SETTING_CORS_RULE_ALLOWED_METHODS_FLAG 0x10

//CORSRuleType presents costom type：CORSRule.
class QS_SDK_API CORSRuleType:QsBaseType
{

public:
    CORSRuleType()
    {
    };
    CORSRuleType(std::string serializedStr);

#ifdef BUILD_C_STYLE_INTERFACE
    CORSRuleType(qs_cors_rule_t cors_rule);
    qs_cors_rule_t *toCStyleObj();
#endif							// BUILD_C_STYLE_INTERFACE// Allowed headers
#ifdef BUILD_C_STYLE_INTERFACE
    inline void SetAllowedHeaders(qs_list_t * allowed_headers)
    {
        m_settingFlag |= SETTING_CORS_RULE_ALLOWED_HEADERS_FLAG;
        qs_string_item_t *item;
        qs_list_for_each_entry(qs_string_item_t, item, allowed_headers)
        {
            m_AllowedHeaders.push_back(item->content);
        }
    };
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetAllowedHeaders(std::vector < std::string > AllowedHeaders)
    {
        m_settingFlag |= SETTING_CORS_RULE_ALLOWED_HEADERS_FLAG;
        m_AllowedHeaders = AllowedHeaders;
    };

    inline std::vector < std::string > GetAllowedHeaders()
    {
        return m_AllowedHeaders;
    };

    // Allowed methods
#ifdef BUILD_C_STYLE_INTERFACE
    inline void SetAllowedMethods(qs_list_t * allowed_methods)
    {
        m_settingFlag |= SETTING_CORS_RULE_ALLOWED_METHODS_FLAG;
        qs_string_item_t *item;
        qs_list_for_each_entry(qs_string_item_t, item, allowed_methods)
        {
            m_AllowedMethods.push_back(item->content);
        }
    };
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetAllowedMethods(std::vector < std::string > AllowedMethods)
    {
        m_settingFlag |= SETTING_CORS_RULE_ALLOWED_METHODS_FLAG;
        m_AllowedMethods = AllowedMethods;
    };

    inline std::vector < std::string > GetAllowedMethods()
    {
        return m_AllowedMethods;
    };

    // Allowed origin

    inline void SetAllowedOrigin(std::string AllowedOrigin)
    {
        m_settingFlag |= SETTING_CORS_RULE_ALLOWED_ORIGIN_FLAG;
        m_AllowedOrigin = AllowedOrigin;
    };

    inline std::string GetAllowedOrigin()
    {
        return m_AllowedOrigin;
    };

    // Expose headers
#ifdef BUILD_C_STYLE_INTERFACE
    inline void SetExposeHeaders(qs_list_t * expose_headers)
    {
        m_settingFlag |= SETTING_CORS_RULE_EXPOSE_HEADERS_FLAG;
        qs_string_item_t *item;
        qs_list_for_each_entry(qs_string_item_t, item, expose_headers)
        {
            m_ExposeHeaders.push_back(item->content);
        }
    };
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetExposeHeaders(std::vector < std::string > ExposeHeaders)
    {
        m_settingFlag |= SETTING_CORS_RULE_EXPOSE_HEADERS_FLAG;
        m_ExposeHeaders = ExposeHeaders;
    };

    inline std::vector < std::string > GetExposeHeaders()
    {
        return m_ExposeHeaders;
    };

    // Max age seconds

    inline void SetMaxAgeSeconds(int MaxAgeSeconds)
    {
        m_settingFlag |= SETTING_CORS_RULE_MAX_AGE_SECONDS_FLAG;
        m_MaxAgeSeconds = MaxAgeSeconds;
    };

    inline int GetMaxAgeSeconds()
    {
        return m_MaxAgeSeconds;
    };

    std::string Serialize();

private:

    // Allowed headers

    std::vector < std::string > m_AllowedHeaders;

    // Allowed methods

    std::vector < std::string > m_AllowedMethods;	// Required

    // Allowed origin
    std::string m_AllowedOrigin;	// Required

    // Expose headers

    std::vector < std::string > m_ExposeHeaders;

    // Max age seconds
    int m_MaxAgeSeconds;

    int setting_flag;
};
