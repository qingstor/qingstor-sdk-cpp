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
#include "../service_with_c_style/types/ObjectPartType.h"
#endif							// BUILD_C_STYLE_INTERFACE

// Object part size'flag
#define SETTING_OBJECT_PART_SIZE_FLAG 0x1

// Object part created time'flag
#define SETTING_OBJECT_PART_CREATED_FLAG 0x2

// MD5sum of the object part'flag
#define SETTING_OBJECT_PART_ETAG_FLAG 0x4

// Object part number'flag
#define SETTING_OBJECT_PART_PART_NUMBER_FLAG 0x8

//ObjectPartType presents costom type：ObjectPart.
class QS_SDK_API ObjectPartType:QsBaseType
{

public:
    ObjectPartType()
    {
    };
    ObjectPartType(std::string serializedStr);

#ifdef BUILD_C_STYLE_INTERFACE
    ObjectPartType(qs_object_part_t object_part);
    qs_object_part_t *toCStyleObj();
#endif							// BUILD_C_STYLE_INTERFACE// Object part created time

    inline void SetCreated(std::string Created)
    {
        m_settingFlag |= SETTING_OBJECT_PART_CREATED_FLAG;
        m_Created = Created;
    };

    inline std::string GetCreated()
    {
        return m_Created;
    };

    // MD5sum of the object part

    inline void SetEtag(std::string Etag)
    {
        m_settingFlag |= SETTING_OBJECT_PART_ETAG_FLAG;
        m_Etag = Etag;
    };

    inline std::string GetEtag()
    {
        return m_Etag;
    };

    // Object part number

    inline void SetPartNumber(int PartNumber)
    {
        m_settingFlag |= SETTING_OBJECT_PART_PART_NUMBER_FLAG;
        m_PartNumber = PartNumber;
    };

    inline int GetPartNumber()
    {
        return m_PartNumber;
    };

    // Object part size

    inline void SetSize(int64_t Size)
    {
        m_settingFlag |= SETTING_OBJECT_PART_SIZE_FLAG;
        m_Size = Size;
    };

    inline int64_t GetSize()
    {
        return m_Size;
    };

    std::string Serialize();

private:

    // Object part created time
    std::string m_Created;

    // MD5sum of the object part
    std::string m_Etag;

    // Object part number
    int m_PartNumber;			// Required

    // Object part size
    int64_t m_Size;

    int setting_flag;
};
