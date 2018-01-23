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
#include "../service_with_c_style/types/GranteeType.h"
#endif							// BUILD_C_STYLE_INTERFACE

// Grantee user ID'flag
#define SETTING_GRANTEE_ID_FLAG 0x1

// Grantee group name'flag
#define SETTING_GRANTEE_NAME_FLAG 0x2

// Grantee type'flag
// Type's available values: user, group
#define SETTING_GRANTEE_TYPE_FLAG 0x4

//GranteeType presents costom type：Grantee.
class QS_SDK_API GranteeType:QsBaseType
{

public:
    GranteeType()
    {
    };
    GranteeType(std::string serializedStr);

#ifdef BUILD_C_STYLE_INTERFACE
    GranteeType(qs_grantee_t grantee);
    qs_grantee_t *toCStyleObj();
#endif							// BUILD_C_STYLE_INTERFACE// Grantee user ID

    inline void SetID(std::string ID)
    {
        m_settingFlag |= SETTING_GRANTEE_ID_FLAG;
        m_ID = ID;
    };

    inline std::string GetID()
    {
        return m_ID;
    };

    // Grantee group name

    inline void SetName(std::string Name)
    {
        m_settingFlag |= SETTING_GRANTEE_NAME_FLAG;
        m_Name = Name;
    };

    inline std::string GetName()
    {
        return m_Name;
    };

    // Grantee type
    // Type's available values: user, group

    inline void SetType(std::string Type)
    {
        m_settingFlag |= SETTING_GRANTEE_TYPE_FLAG;
        m_Type = Type;
    };

    inline std::string GetType()
    {
        return m_Type;
    };

    std::string Serialize();

private:

    // Grantee user ID
    std::string m_ID;

    // Grantee group name
    std::string m_Name;

    // Grantee type
    // Type's available values: user, group
    std::string m_Type;			// Required

    int setting_flag;
};
