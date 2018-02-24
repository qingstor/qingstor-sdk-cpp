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
#include "ConditionType.h"

#ifdef BUILD_C_STYLE_INTERFACE
#include "../service_with_c_style/types/StatementType.h"
#endif							// BUILD_C_STYLE_INTERFACE

// Bucket policy id, must be unique'flag
#define SETTING_STATEMENT_ID_FLAG 0x1

// The resources to apply bucket policy'flag
#define SETTING_STATEMENT_RESOURCE_FLAG 0x2

// The user to apply bucket policy'flag
#define SETTING_STATEMENT_USER_FLAG 0x4

// QingStor API methods'flag
#define SETTING_STATEMENT_ACTION_FLAG 0x8

#define SETTING_STATEMENT_CONDITION_FLAG 0x10

// Statement effect'flag
// Effect's available values: allow, deny
#define SETTING_STATEMENT_EFFECT_FLAG 0x20

//StatementType presents costom type：Statement.
class QS_SDK_API StatementType:QsBaseType
{

public:
    StatementType()
    {
    };
    StatementType(std::string serializedStr);

#ifdef BUILD_C_STYLE_INTERFACE
    StatementType(qs_statement_t statement);
    qs_statement_t *toCStyleObj();
#endif							// BUILD_C_STYLE_INTERFACE// QingStor API methods
#ifdef BUILD_C_STYLE_INTERFACE
    inline void SetAction(qs_list_t * action)
    {
        m_settingFlag |= SETTING_STATEMENT_ACTION_FLAG;
        qs_string_item_t *item;
        qs_list_for_each_entry(qs_string_item_t, item, action)
        {
            m_Action.push_back(item->content);
        }
    };
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetAction(std::vector < std::string > Action)
    {
        m_settingFlag |= SETTING_STATEMENT_ACTION_FLAG;
        m_Action = Action;
    };

    inline std::vector < std::string > GetAction()
    {
        return m_Action;
    };

    inline void SetCondition(ConditionType Condition)
    {
        m_settingFlag |= SETTING_STATEMENT_CONDITION_FLAG;
        m_Condition = Condition;
    };

    inline ConditionType GetCondition()
    {
        return m_Condition;
    };

    // Statement effect
    // Effect's available values: allow, deny

    inline void SetEffect(std::string Effect)
    {
        m_settingFlag |= SETTING_STATEMENT_EFFECT_FLAG;
        m_Effect = Effect;
    };

    inline std::string GetEffect()
    {
        return m_Effect;
    };

    // Bucket policy id, must be unique

    inline void SetID(std::string ID)
    {
        m_settingFlag |= SETTING_STATEMENT_ID_FLAG;
        m_ID = ID;
    };

    inline std::string GetID()
    {
        return m_ID;
    };

    // The resources to apply bucket policy
#ifdef BUILD_C_STYLE_INTERFACE
    inline void SetResource(qs_list_t * resource)
    {
        m_settingFlag |= SETTING_STATEMENT_RESOURCE_FLAG;
        qs_string_item_t *item;
        qs_list_for_each_entry(qs_string_item_t, item, resource)
        {
            m_Resource.push_back(item->content);
        }
    };
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetResource(std::vector < std::string > Resource)
    {
        m_settingFlag |= SETTING_STATEMENT_RESOURCE_FLAG;
        m_Resource = Resource;
    };

    inline std::vector < std::string > GetResource()
    {
        return m_Resource;
    };

    // The user to apply bucket policy
#ifdef BUILD_C_STYLE_INTERFACE
    inline void SetUser(qs_list_t * user)
    {
        m_settingFlag |= SETTING_STATEMENT_USER_FLAG;
        qs_string_item_t *item;
        qs_list_for_each_entry(qs_string_item_t, item, user)
        {
            m_User.push_back(item->content);
        }
    };
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetUser(std::vector < std::string > User)
    {
        m_settingFlag |= SETTING_STATEMENT_USER_FLAG;
        m_User = User;
    };

    inline std::vector < std::string > GetUser()
    {
        return m_User;
    };

    std::string Serialize();

private:

    // QingStor API methods

    std::vector < std::string > m_Action;	// Required

    ConditionType m_Condition;

    // Statement effect
    // Effect's available values: allow, deny
    std::string m_Effect;		// Required

    // Bucket policy id, must be unique
    std::string m_ID;			// Required

    // The resources to apply bucket policy

    std::vector < std::string > m_Resource;

    // The user to apply bucket policy

    std::vector < std::string > m_User;	// Required

    int setting_flag;
};
