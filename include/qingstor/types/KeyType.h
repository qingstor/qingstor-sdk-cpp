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
#include "../service_with_c_style/types/KeyType.h"
#endif							// BUILD_C_STYLE_INTERFACE

// Object key'flag
#define SETTING_KEY_KEY_FLAG 0x1

// MIME type of the object'flag
#define SETTING_KEY_MIME_TYPE_FLAG 0x2

// Last modified time in unix time format'flag
#define SETTING_KEY_MODIFIED_FLAG 0x4

// Object content size'flag
#define SETTING_KEY_SIZE_FLAG 0x8

// Object created time'flag
#define SETTING_KEY_CREATED_FLAG 0x10

// Whether this key is encrypted'flag
#define SETTING_KEY_ENCRYPTED_FLAG 0x20

// MD5sum of the object'flag
#define SETTING_KEY_ETAG_FLAG 0x40

//KeyType presents costom type：Key.
class QS_SDK_API KeyType:QsBaseType
{

public:
    KeyType()
    {
    };
    KeyType(std::string serializedStr);

#ifdef BUILD_C_STYLE_INTERFACE
    KeyType(qs_key_t key);
    qs_key_t *toCStyleObj();
#endif							// BUILD_C_STYLE_INTERFACE// Object created time

    inline void SetCreated(std::string Created)
    {
        m_settingFlag |= SETTING_KEY_CREATED_FLAG;
        m_Created = Created;
    };

    inline std::string GetCreated()
    {
        return m_Created;
    };

    // Whether this key is encrypted

    inline void SetEncrypted(bool Encrypted)
    {
        m_settingFlag |= SETTING_KEY_ENCRYPTED_FLAG;
        m_Encrypted = Encrypted;
    };

    inline bool GetEncrypted()
    {
        return m_Encrypted;
    };

    // MD5sum of the object

    inline void SetEtag(std::string Etag)
    {
        m_settingFlag |= SETTING_KEY_ETAG_FLAG;
        m_Etag = Etag;
    };

    inline std::string GetEtag()
    {
        return m_Etag;
    };

    // Object key

    inline void SetKey(std::string Key)
    {
        m_settingFlag |= SETTING_KEY_KEY_FLAG;
        m_Key = Key;
    };

    inline std::string GetKey()
    {
        return m_Key;
    };

    // MIME type of the object

    inline void SetMimeType(std::string MimeType)
    {
        m_settingFlag |= SETTING_KEY_MIME_TYPE_FLAG;
        m_MimeType = MimeType;
    };

    inline std::string GetMimeType()
    {
        return m_MimeType;
    };

    // Last modified time in unix time format

    inline void SetModified(int Modified)
    {
        m_settingFlag |= SETTING_KEY_MODIFIED_FLAG;
        m_Modified = Modified;
    };

    inline int GetModified()
    {
        return m_Modified;
    };

    // Object content size

    inline void SetSize(int64_t Size)
    {
        m_settingFlag |= SETTING_KEY_SIZE_FLAG;
        m_Size = Size;
    };

    inline int64_t GetSize()
    {
        return m_Size;
    };

    std::string Serialize();

private:

    // Object created time
    std::string m_Created;

    // Whether this key is encrypted
    bool m_Encrypted;

    // MD5sum of the object
    std::string m_Etag;

    // Object key
    std::string m_Key;

    // MIME type of the object
    std::string m_MimeType;

    // Last modified time in unix time format
    int m_Modified;

    // Object content size
    int64_t m_Size;

    int setting_flag;
};
