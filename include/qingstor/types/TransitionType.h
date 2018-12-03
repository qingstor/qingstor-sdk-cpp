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
#include "../service_with_c_style/types/TransitionType.h"
#endif							// BUILD_C_STYLE_INTERFACE

// days'flag
#define SETTING_TRANSITION_DAYS_FLAG 0x1

// storage class'flag
#define SETTING_TRANSITION_STORAGE_CLASS_FLAG 0x2

//TransitionType presents costom type：Transition.
class QS_SDK_API TransitionType:QsBaseType
{

public:
    TransitionType()
    {
    };
    TransitionType(std::string serializedStr);

#ifdef BUILD_C_STYLE_INTERFACE
    TransitionType(qs_transition_t transition);
    qs_transition_t *toCStyleObj();
#endif							// BUILD_C_STYLE_INTERFACE// days

    inline void SetDays(int Days)
    {
        m_settingFlag |= SETTING_TRANSITION_DAYS_FLAG;
        m_Days = Days;
    };

    inline int GetDays()
    {
        return m_Days;
    };

    // storage class

    inline void SetStorageClass(int StorageClass)
    {
        m_settingFlag |= SETTING_TRANSITION_STORAGE_CLASS_FLAG;
        m_StorageClass = StorageClass;
    };

    inline int GetStorageClass()
    {
        return m_StorageClass;
    };

    std::string Serialize();

private:

    // days
    int m_Days;

    // storage class
    int m_StorageClass;			// Required

    int setting_flag;
};
