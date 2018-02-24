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
#include "../service_with_c_style/types/NotIPAddressType.h"
#endif							// BUILD_C_STYLE_INTERFACE

// Source IP'flag
#define SETTING_NOT_IP_ADDRESS_SOURCE_IP_FLAG 0x1

//NotIPAddressType presents costom type：NotIPAddress.
class QS_SDK_API NotIPAddressType:QsBaseType
{

public:
    NotIPAddressType()
    {
    };
    NotIPAddressType(std::string serializedStr);

#ifdef BUILD_C_STYLE_INTERFACE
    NotIPAddressType(qs_not_ip_address_t not_ip_address);
    qs_not_ip_address_t *toCStyleObj();
#endif							// BUILD_C_STYLE_INTERFACE// Source IP
#ifdef BUILD_C_STYLE_INTERFACE
    inline void SetSourceIP(qs_list_t * source_ip)
    {
        m_settingFlag |= SETTING_NOT_IP_ADDRESS_SOURCE_IP_FLAG;
        qs_string_item_t *item;
        qs_list_for_each_entry(qs_string_item_t, item, source_ip)
        {
            m_SourceIP.push_back(item->content);
        }
    };
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetSourceIP(std::vector < std::string > SourceIP)
    {
        m_settingFlag |= SETTING_NOT_IP_ADDRESS_SOURCE_IP_FLAG;
        m_SourceIP = SourceIP;
    };

    inline std::vector < std::string > GetSourceIP()
    {
        return m_SourceIP;
    };

    std::string Serialize();

private:

    // Source IP

    std::vector < std::string > m_SourceIP;

    int setting_flag;
};
