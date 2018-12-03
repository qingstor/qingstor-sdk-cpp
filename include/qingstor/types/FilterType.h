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
#include "../service_with_c_style/types/FilterType.h"
#endif							// BUILD_C_STYLE_INTERFACE

// Prefix matching'flag
#define SETTING_FILTER_PREFIX_FLAG 0x1

//FilterType presents costom type：Filter.
class QS_SDK_API FilterType:QsBaseType
{

public:
    FilterType()
    {
    };
    FilterType(std::string serializedStr);

#ifdef BUILD_C_STYLE_INTERFACE
    FilterType(qs_filter_t filter);
    qs_filter_t *toCStyleObj();
#endif							// BUILD_C_STYLE_INTERFACE// Prefix matching

    inline void SetPrefix(std::string Prefix)
    {
        m_settingFlag |= SETTING_FILTER_PREFIX_FLAG;
        m_Prefix = Prefix;
    };

    inline std::string GetPrefix()
    {
        return m_Prefix;
    };

    std::string Serialize();

private:

    // Prefix matching
    std::string m_Prefix;		// Required

    int setting_flag;
};
