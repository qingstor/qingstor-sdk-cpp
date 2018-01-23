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
#include "GranteeType.h"

#ifdef BUILD_C_STYLE_INTERFACE
#include "../service_with_c_style/types/ACLType.h"
#endif							// BUILD_C_STYLE_INTERFACE

#define SETTING_ACL_GRANTEE_FLAG 0x1

// Permission for this grantee'flag
// Permission's available values: READ, WRITE, FULL_CONTROL
#define SETTING_ACL_PERMISSION_FLAG 0x2

//ACLType presents costom type：ACL.
class QS_SDK_API ACLType:QsBaseType
{

public:
    ACLType()
    {
    };
    ACLType(std::string serializedStr);

#ifdef BUILD_C_STYLE_INTERFACE
    ACLType(qs_acl_t acl);
    qs_acl_t *toCStyleObj();
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetGrantee(GranteeType Grantee)
    {
        m_settingFlag |= SETTING_ACL_GRANTEE_FLAG;
        m_Grantee = Grantee;
    };

    inline GranteeType GetGrantee()
    {
        return m_Grantee;
    };

    // Permission for this grantee
    // Permission's available values: READ, WRITE, FULL_CONTROL

    inline void SetPermission(std::string Permission)
    {
        m_settingFlag |= SETTING_ACL_PERMISSION_FLAG;
        m_Permission = Permission;
    };

    inline std::string GetPermission()
    {
        return m_Permission;
    };

    std::string Serialize();

private:

    GranteeType m_Grantee;		// Required

    // Permission for this grantee
    // Permission's available values: READ, WRITE, FULL_CONTROL
    std::string m_Permission;	// Required

    int setting_flag;
};
