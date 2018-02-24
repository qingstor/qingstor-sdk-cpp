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
#include "../service_with_c_style/types/BucketType.h"
#endif							// BUILD_C_STYLE_INTERFACE

// Created time of the bucket'flag
#define SETTING_BUCKET_CREATED_FLAG 0x1

// QingCloud Zone ID'flag
#define SETTING_BUCKET_LOCATION_FLAG 0x2

// Bucket name'flag
#define SETTING_BUCKET_NAME_FLAG 0x4

// URL to access the bucket'flag
#define SETTING_BUCKET_URL_FLAG 0x8

//BucketType presents costom type：Bucket.
class QS_SDK_API BucketType:QsBaseType
{

public:
    BucketType()
    {
    };
    BucketType(std::string serializedStr);

#ifdef BUILD_C_STYLE_INTERFACE
    BucketType(qs_bucket_t bucket);
    qs_bucket_t *toCStyleObj();
#endif							// BUILD_C_STYLE_INTERFACE// Created time of the bucket

    inline void SetCreated(std::string Created)
    {
        m_settingFlag |= SETTING_BUCKET_CREATED_FLAG;
        m_Created = Created;
    };

    inline std::string GetCreated()
    {
        return m_Created;
    };

    // QingCloud Zone ID

    inline void SetLocation(std::string Location)
    {
        m_settingFlag |= SETTING_BUCKET_LOCATION_FLAG;
        m_Location = Location;
    };

    inline std::string GetLocation()
    {
        return m_Location;
    };

    // Bucket name

    inline void SetName(std::string Name)
    {
        m_settingFlag |= SETTING_BUCKET_NAME_FLAG;
        m_Name = Name;
    };

    inline std::string GetName()
    {
        return m_Name;
    };

    // URL to access the bucket

    inline void SetURL(std::string URL)
    {
        m_settingFlag |= SETTING_BUCKET_URL_FLAG;
        m_URL = URL;
    };

    inline std::string GetURL()
    {
        return m_URL;
    };

    std::string Serialize();

private:

    // Created time of the bucket
    std::string m_Created;

    // QingCloud Zone ID
    std::string m_Location;

    // Bucket name
    std::string m_Name;

    // URL to access the bucket
    std::string m_URL;

    int setting_flag;
};
