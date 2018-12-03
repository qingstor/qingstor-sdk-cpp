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
#include "../service_with_c_style/types/ExpirationType.h"
#endif							// BUILD_C_STYLE_INTERFACE

// days'flag
#define SETTING_EXPIRATION_DAYS_FLAG 0x1

//ExpirationType presents costom type：Expiration.
class QS_SDK_API ExpirationType:QsBaseType
{

public:
    ExpirationType()
    {
    };
    ExpirationType(std::string serializedStr);

#ifdef BUILD_C_STYLE_INTERFACE
    ExpirationType(qs_expiration_t expiration);
    qs_expiration_t *toCStyleObj();
#endif							// BUILD_C_STYLE_INTERFACE// days

    inline void SetDays(int Days)
    {
        m_settingFlag |= SETTING_EXPIRATION_DAYS_FLAG;
        m_Days = Days;
    };

    inline int GetDays()
    {
        return m_Days;
    };

    std::string Serialize();

private:

    // days
    int m_Days;

    int setting_flag;
};
