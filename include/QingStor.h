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

#include  "QsSdkOption.h"
#include  "Bucket.h"

namespace QingStor
{

// SDK wide options
struct QS_SDK_API SDKOptions
{
    SDKOptions():initAndCleanupCurl(true), logLevel(None), logPath("")
    {
    }
    // SDK wide options for curl
    // If it is being used then we automatically initialize and clean it up.
    // If this is a problem for you, set this to false. 
    bool initAndCleanupCurl;

    // Option for logging level ,defaults to Off
    LogLevel logLevel;

    // Option for logging file path, defaults to the path of the executable program.
    std::string logPath;
};

// This method should be called brfore using the SDK.
QS_SDK_API void InitializeSDK(const SDKOptions & options);

// This method should be called when you are finished using the SDK.
// Do not call any other SDK methods after calling ShutdownSDK.
QS_SDK_API void ShutdownSDK(const SDKOptions & options);

// +--------------------------------------------------------------------
// |                     InputClassHeader
// +--------------------------------------------------------------------
// ListBucketsInput presents input for ListBuckets.
class QS_SDK_API ListBucketsInput:public QsInput
{
public:
    ListBucketsInput()
    {
    };

    inline bool CheckIfInputIsVaild()
    {
        int tmpFlag = BASIC_FLAG;
        return (tmpFlag == (tmpFlag & m_settingFlag));
    };
    // Limits results to buckets that in the location

    inline void SetLocation(std::string Location)
    {
        m_settingFlag |= SETTING_INPUT_LIST_BUCKETS_LOCATION_FLAG;
        m_Location = Location;
    };

    inline std::string GetLocation()
    {
        return m_Location;
    };

private:
    // Limits results to buckets that in the location
    std::string m_Location;

};

// +--------------------------------------------------------------------
// |                     OutputClassHeader
// +--------------------------------------------------------------------

// ListBucketsOutput presents input for ListBuckets.
class QS_SDK_API ListBucketsOutput:public QsOutput
{

public:
    ListBucketsOutput(QsError err,
                      Http::HttpResponseCode responseCode):QsOutput(err,
                                  responseCode)
    {
    };
    ListBucketsOutput()
    {
    };

    // Buckets information
    inline void SetBuckets(std::vector < BucketType > Buckets)
    {
        m_settingFlag |= SETTING_OUTPUT_LIST_BUCKETS_BUCKETS_FLAG;
        m_Buckets = Buckets;
    };

    inline std::vector < BucketType > GetBuckets()
    {
        return m_Buckets;
    };

    // Bucket count
    inline void SetCount(int Count)
    {
        m_settingFlag |= SETTING_OUTPUT_LIST_BUCKETS_COUNT_FLAG;
        m_Count = Count;
    };

    inline int GetCount()
    {
        return m_Count;
    };

private:
    // Buckets information

    std::vector < BucketType > m_Buckets;

    // Bucket count
    int m_Count;

};

// +--------------------------------------------------------------------
// |                     QingStorService
// +--------------------------------------------------------------------

class QS_SDK_API QingStorService
{
public:
    QingStorService(const QsConfig & qsConfig);

    virtual ~ QingStorService()
    {
    };

    // ListBuckets does Retrieve the bucket list.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/service/get.html
    QsError ListBuckets(ListBucketsInput & input,
                        ListBucketsOutput & output);

private:
    QsConfig m_qsConfig;
    Properties m_properties;
};

}								// namespace QingStor
