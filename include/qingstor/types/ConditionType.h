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
#include "IPAddressType.h"
#include "IsNullType.h"
#include "NotIPAddressType.h"
#include "StringLikeType.h"
#include "StringNotLikeType.h"

#ifdef BUILD_C_STYLE_INTERFACE
#include "../service_with_c_style/types/ConditionType.h"
#endif							// BUILD_C_STYLE_INTERFACE

#define SETTING_CONDITION_IP_ADDRESS_FLAG 0x1

#define SETTING_CONDITION_IS_NULL_FLAG 0x2

#define SETTING_CONDITION_NOT_IP_ADDRESS_FLAG 0x4

#define SETTING_CONDITION_STRING_LIKE_FLAG 0x8

#define SETTING_CONDITION_STRING_NOT_LIKE_FLAG 0x10

//ConditionType presents costom type：Condition.
class QS_SDK_API ConditionType:QsBaseType
{

public:
    ConditionType()
    {
    };
    ConditionType(std::string serializedStr);

#ifdef BUILD_C_STYLE_INTERFACE
    ConditionType(qs_condition_t condition);
    qs_condition_t *toCStyleObj();
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetIPAddress(IPAddressType IPAddress)
    {
        m_settingFlag |= SETTING_CONDITION_IP_ADDRESS_FLAG;
        m_IPAddress = IPAddress;
    };

    inline IPAddressType GetIPAddress()
    {
        return m_IPAddress;
    };

    inline void SetIsNull(IsNullType IsNull)
    {
        m_settingFlag |= SETTING_CONDITION_IS_NULL_FLAG;
        m_IsNull = IsNull;
    };

    inline IsNullType GetIsNull()
    {
        return m_IsNull;
    };

    inline void SetNotIPAddress(NotIPAddressType NotIPAddress)
    {
        m_settingFlag |= SETTING_CONDITION_NOT_IP_ADDRESS_FLAG;
        m_NotIPAddress = NotIPAddress;
    };

    inline NotIPAddressType GetNotIPAddress()
    {
        return m_NotIPAddress;
    };

    inline void SetStringLike(StringLikeType StringLike)
    {
        m_settingFlag |= SETTING_CONDITION_STRING_LIKE_FLAG;
        m_StringLike = StringLike;
    };

    inline StringLikeType GetStringLike()
    {
        return m_StringLike;
    };

    inline void SetStringNotLike(StringNotLikeType StringNotLike)
    {
        m_settingFlag |= SETTING_CONDITION_STRING_NOT_LIKE_FLAG;
        m_StringNotLike = StringNotLike;
    };

    inline StringNotLikeType GetStringNotLike()
    {
        return m_StringNotLike;
    };

    std::string Serialize();

private:

    IPAddressType m_IPAddress;

    IsNullType m_IsNull;

    NotIPAddressType m_NotIPAddress;

    StringLikeType m_StringLike;

    StringNotLikeType m_StringNotLike;

    int setting_flag;
};
