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
#include "../service_with_c_style/types/StringNotLikeType.h"
#endif							// BUILD_C_STYLE_INTERFACE

// Refer url'flag
#define SETTING_STRING_NOT_LIKE_REFERER_FLAG 0x1

//StringNotLikeType presents costom type：StringNotLike.
class QS_SDK_API StringNotLikeType:QsBaseType
{

public:
    StringNotLikeType()
    {
    };
    StringNotLikeType(std::string serializedStr);

#ifdef BUILD_C_STYLE_INTERFACE
    StringNotLikeType(qs_string_not_like_t string_not_like);
    qs_string_not_like_t *toCStyleObj();
#endif							// BUILD_C_STYLE_INTERFACE// Refer url
#ifdef BUILD_C_STYLE_INTERFACE
    inline void SetReferer(qs_list_t * referer)
    {
        m_settingFlag |= SETTING_STRING_NOT_LIKE_REFERER_FLAG;
        qs_string_item_t *item;
        qs_list_for_each_entry(qs_string_item_t, item, referer)
        {
            m_Referer.push_back(item->content);
        }
    };
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetReferer(std::vector < std::string > Referer)
    {
        m_settingFlag |= SETTING_STRING_NOT_LIKE_REFERER_FLAG;
        m_Referer = Referer;
    };

    inline std::vector < std::string > GetReferer()
    {
        return m_Referer;
    };

    std::string Serialize();

private:

    // Refer url

    std::vector < std::string > m_Referer;

    int setting_flag;
};
