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
#include "KeyType.h"

#ifdef BUILD_C_STYLE_INTERFACE
#include "../service_with_c_style/types/KeyDeleteErrorType.h"
#endif							// BUILD_C_STYLE_INTERFACE

// Object key'flag
#define SETTING_KEY_DELETE_ERROR_KEY_FLAG 0x1

// Error message'flag
#define SETTING_KEY_DELETE_ERROR_MESSAGE_FLAG 0x2

// Error code'flag
#define SETTING_KEY_DELETE_ERROR_CODE_FLAG 0x4

//KeyDeleteErrorType presents costom type：KeyDeleteError.
class QS_SDK_API KeyDeleteErrorType:QsBaseType
{

public:
    KeyDeleteErrorType()
    {
    };
    KeyDeleteErrorType(std::string serializedStr);

#ifdef BUILD_C_STYLE_INTERFACE
    KeyDeleteErrorType(qs_key_delete_error_t key_delete_error);
    qs_key_delete_error_t *toCStyleObj();
#endif							// BUILD_C_STYLE_INTERFACE// Error code

    inline void SetCode(std::string Code)
    {
        m_settingFlag |= SETTING_KEY_DELETE_ERROR_CODE_FLAG;
        m_Code = Code;
    };

    inline std::string GetCode()
    {
        return m_Code;
    };

    // Object key

    inline void SetKey(std::string Key)
    {
        m_settingFlag |= SETTING_KEY_DELETE_ERROR_KEY_FLAG;
        m_Key = Key;
    };

    inline std::string GetKey()
    {
        return m_Key;
    };

    // Error message

    inline void SetMessage(std::string Message)
    {
        m_settingFlag |= SETTING_KEY_DELETE_ERROR_MESSAGE_FLAG;
        m_Message = Message;
    };

    inline std::string GetMessage()
    {
        return m_Message;
    };

    std::string Serialize();

private:

    // Error code
    std::string m_Code;

    // Object key
    std::string m_Key;

    // Error message
    std::string m_Message;

    int setting_flag;
};
