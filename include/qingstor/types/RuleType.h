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
#include "AbortIncompleteMultipartUploadType.h"
#include "ExpirationType.h"
#include "FilterType.h"
#include "TransitionType.h"

#ifdef BUILD_C_STYLE_INTERFACE
#include "../service_with_c_style/types/RuleType.h"
#endif							// BUILD_C_STYLE_INTERFACE

#define SETTING_RULE_ABORT_INCOMPLETE_MULTIPART_UPLOAD_FLAG 0x1

#define SETTING_RULE_EXPIRATION_FLAG 0x2

#define SETTING_RULE_FILTER_FLAG 0x4

// rule id'flag
#define SETTING_RULE_ID_FLAG 0x8

// rule status'flag
// Status's available values: enabled, disabled
#define SETTING_RULE_STATUS_FLAG 0x10

#define SETTING_RULE_TRANSITION_FLAG 0x20

//RuleType presents costom type：Rule.
class QS_SDK_API RuleType:QsBaseType
{

public:
    RuleType()
    {
    };
    RuleType(std::string serializedStr);

#ifdef BUILD_C_STYLE_INTERFACE
    RuleType(qs_rule_t rule);
    qs_rule_t *toCStyleObj();
#endif							// BUILD_C_STYLE_INTERFACE

    inline void
    SetAbortIncompleteMultipartUpload(AbortIncompleteMultipartUploadType
                                      AbortIncompleteMultipartUpload)
    {
        m_settingFlag |= SETTING_RULE_ABORT_INCOMPLETE_MULTIPART_UPLOAD_FLAG;
        m_AbortIncompleteMultipartUpload = AbortIncompleteMultipartUpload;
    };

    inline
    AbortIncompleteMultipartUploadType GetAbortIncompleteMultipartUpload()
    {
        return m_AbortIncompleteMultipartUpload;
    };

    inline void SetExpiration(ExpirationType Expiration)
    {
        m_settingFlag |= SETTING_RULE_EXPIRATION_FLAG;
        m_Expiration = Expiration;
    };

    inline ExpirationType GetExpiration()
    {
        return m_Expiration;
    };

    inline void SetFilter(FilterType Filter)
    {
        m_settingFlag |= SETTING_RULE_FILTER_FLAG;
        m_Filter = Filter;
    };

    inline FilterType GetFilter()
    {
        return m_Filter;
    };

    // rule id

    inline void SetID(std::string ID)
    {
        m_settingFlag |= SETTING_RULE_ID_FLAG;
        m_ID = ID;
    };

    inline std::string GetID()
    {
        return m_ID;
    };

    // rule status
    // Status's available values: enabled, disabled

    inline void SetStatus(std::string Status)
    {
        m_settingFlag |= SETTING_RULE_STATUS_FLAG;
        m_Status = Status;
    };

    inline std::string GetStatus()
    {
        return m_Status;
    };

    inline void SetTransition(TransitionType Transition)
    {
        m_settingFlag |= SETTING_RULE_TRANSITION_FLAG;
        m_Transition = Transition;
    };

    inline TransitionType GetTransition()
    {
        return m_Transition;
    };

    std::string Serialize();

private:

    AbortIncompleteMultipartUploadType m_AbortIncompleteMultipartUpload;

    ExpirationType m_Expiration;

    FilterType m_Filter;		// Required

    // rule id
    std::string m_ID;			// Required

    // rule status
    // Status's available values: enabled, disabled
    std::string m_Status;		// Required

    TransitionType m_Transition;

    int setting_flag;
};
