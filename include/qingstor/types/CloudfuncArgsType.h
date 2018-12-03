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
#include "../service_with_c_style/types/CloudfuncArgsType.h"
#endif							// BUILD_C_STYLE_INTERFACE

#define SETTING_CLOUDFUNC_ARGS_ACTION_FLAG 0x1

#define SETTING_CLOUDFUNC_ARGS_KEY_PREFIX_FLAG 0x2

#define SETTING_CLOUDFUNC_ARGS_KEY_SEPRATE_FLAG 0x4

#define SETTING_CLOUDFUNC_ARGS_SAVE_BUCKET_FLAG 0x8

//CloudfuncArgsType presents costom type：CloudfuncArgs.
class QS_SDK_API CloudfuncArgsType:QsBaseType
{

public:
    CloudfuncArgsType()
    {
    };
    CloudfuncArgsType(std::string serializedStr);

#ifdef BUILD_C_STYLE_INTERFACE
    CloudfuncArgsType(qs_cloudfunc_args_t cloudfunc_args);
    qs_cloudfunc_args_t *toCStyleObj();
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetAction(std::string Action)
    {
        m_settingFlag |= SETTING_CLOUDFUNC_ARGS_ACTION_FLAG;
        m_Action = Action;
    };

    inline std::string GetAction()
    {
        return m_Action;
    };

    inline void SetKeyPrefix(std::string KeyPrefix)
    {
        m_settingFlag |= SETTING_CLOUDFUNC_ARGS_KEY_PREFIX_FLAG;
        m_KeyPrefix = KeyPrefix;
    };

    inline std::string GetKeyPrefix()
    {
        return m_KeyPrefix;
    };

    inline void SetKeySeprate(std::string KeySeprate)
    {
        m_settingFlag |= SETTING_CLOUDFUNC_ARGS_KEY_SEPRATE_FLAG;
        m_KeySeprate = KeySeprate;
    };

    inline std::string GetKeySeprate()
    {
        return m_KeySeprate;
    };

    inline void SetSaveBucket(std::string SaveBucket)
    {
        m_settingFlag |= SETTING_CLOUDFUNC_ARGS_SAVE_BUCKET_FLAG;
        m_SaveBucket = SaveBucket;
    };

    inline std::string GetSaveBucket()
    {
        return m_SaveBucket;
    };

    std::string Serialize();

private:

    std::string m_Action;		// Required

    std::string m_KeyPrefix;

    std::string m_KeySeprate;

    std::string m_SaveBucket;

    int setting_flag;
};
