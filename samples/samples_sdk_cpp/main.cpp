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

// +-------------------------------------------------------------------------
// | This Example shows how to use the API interface.
// | For more information, please refer to URL :
// |
// | You should configure the following environment variables to ensure the
// | smooth execution of the program:
// | QINGSTOR_CONFIG_PATH : QingStor config file path
// | QINGSTOR_BUCKET_NAME : QingStor bucket name
// | QINGSTOR_ZONE_NAME : QingStor zone name
// +-------------------------------------------------------------------------

#include <qingstor/QingStor.h>
#include <fstream>
#include <memory>
#include <string>

using namespace QingStor;

static std::iostream* Create5MbStream4UploadPart(const std::string partTag)
{
    size_t fiveMbSize = 5 * 1024 * 1024;
    std::stringstream patternStream;
    patternStream << "Multi-Part upload Test Part " << partTag << ":" << std::endl;
    std::string pattern = patternStream.str();
    std::string scratchString;
    scratchString.reserve(fiveMbSize);
    // 5MB is a hard minimum for multi part uploads; make sure the final string is at least that long
    size_t patternCopyCount = static_cast< size_t >( fiveMbSize / pattern.size() + 1 );
    for(size_t i = 0; i < patternCopyCount; ++i)
    {
        scratchString.append(pattern);
    }
    std::iostream* streamPtr = new std::stringstream(scratchString);
    streamPtr->seekg(0);
    streamPtr->seekp(0, std::ios_base::end);
    return streamPtr;
}


void ShowHow2Do_InitiateMultipartUpload(Bucket * qsBucket, std::string &objectkey, std::string &uploadID)
{
    if(!qsBucket)
    {
        return;
    }
    InitiateMultipartUploadInput input;
    InitiateMultipartUploadOutput output;
    QsError err = qsBucket->InitiateMultipartUpload (objectkey, input, output);
    if (QS_ERR_NO_ERROR == err)
    {
        // If Success.
        uploadID = output.GetUploadID();
    }
    else if(QS_ERR_NO_REQUIRED_PARAMETER == err)
    {
        printf("%s\n" , "The input object lacks some of the parameters that must be filled in.");
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        ResponseErrorInfo  errorInfo = output.GetResponseErrInfo();
        printf("request_id = %s , with detail message : %s\n" , errorInfo.requestID.c_str(), errorInfo.message.c_str());
    }
    return;
}


void ShowHow2Do_UploadMultipart(Bucket * qsBucket, std::string &objectkey, std::string &uploadID ,int partNumber)
{
    if(!qsBucket)
    {
        return;
    }
    UploadMultipartInput input;
    UploadMultipartOutput output;
    // objectStream can be filestream or stringstream.
    std::iostream* objectStream = Create5MbStream4UploadPart("1");
    objectStream->seekg(0, objectStream->end);
    size_t streamSize = objectStream->tellg();
    objectStream->seekg(0, objectStream->beg);
    // The content length must be set.
    input.SetContentLength(streamSize);
    input.SetBody (objectStream);
    input.SetPartNumber (partNumber);
    input.SetUploadID (uploadID);
    QsError err = qsBucket->UploadMultipart (objectkey, input, output);
    if(QS_ERR_NO_REQUIRED_PARAMETER == err)
    {
        printf("%s\n" , "The input object lacks some of the parameters that must be filled in.");
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        ResponseErrorInfo  errorInfo = output.GetResponseErrInfo();
        printf("request_id = %s , with detail message : %s\n" , errorInfo.requestID.c_str(), errorInfo.message.c_str());
    }
    printf("Part %d is finished.\n", partNumber);
    // when api finish, you should release resource.
    delete objectStream;
    return;
}


void ShowHow2Do_CompleteMultipartUpload(Bucket * qsBucket, std::string &objectkey, std::string &uploadID, std::vector<ObjectPartType> &objectParts)
{
    if(!qsBucket)
    {
        return;
    }
    CompleteMultipartUploadInput input;
    CompleteMultipartUploadOutput output;
    input.SetUploadID (uploadID);
    input.SetObjectParts(objectParts);
    QsError err = qsBucket->CompleteMultipartUpload (objectkey, input, output);
    if(QS_ERR_NO_REQUIRED_PARAMETER == err)
    {
        printf("%s\n" , "The input object lacks some of the parameters that must be filled in.");
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        ResponseErrorInfo  errorInfo = output.GetResponseErrInfo();
        printf("request_id = %s , with detail message : %s\n" , errorInfo.requestID.c_str(), errorInfo.message.c_str());
    }
    return;
}


void ShowHow2Do_ListObjects(Bucket * qsBucket)
{
    if(!qsBucket)
    {
        return;
    }
    // List Objects
    ListObjectsInput input;
    ListObjectsOutput output;
    // if you want limit the maximum number of object in response, you can set "Limit" paramter.
    // the default value is 200, maximum allowable set 1000
    input.SetLimit(100);//
    QsError err = qsBucket->ListObjects(input, output);
    if(QS_ERR_NO_REQUIRED_PARAMETER == err)
    {
        printf("%s\n" , "The input object lacks some of the parameters that must be filled in.");
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        ResponseErrorInfo  errorInfo = output.GetResponseErrInfo();
        printf("request_id = %s , with detail message : %s\n" , errorInfo.requestID.c_str(), errorInfo.message.c_str());
    }
    if (QS_ERR_NO_ERROR != err)
    {
        return;
    }
    std::vector<KeyType> keys = output.GetKeys();
    printf("Got %ld objects\n" ,keys.size());
    return;
}

void ShowHow2Do_MultipartUploadObject(Bucket * qsBucket, std::string &objectkey)
{
    if(!qsBucket)
    {
        return;
    }
    std::string uploadID = "";
    ShowHow2Do_InitiateMultipartUpload(qsBucket, objectkey, uploadID);
    ShowHow2Do_UploadMultipart(qsBucket, objectkey, uploadID ,1);
    ShowHow2Do_UploadMultipart(qsBucket, objectkey, uploadID ,2);
    std::vector<ObjectPartType> objectParts;
    ObjectPartType part1,part2;
    part1.SetPartNumber(1);
    part2.SetPartNumber(2);
    objectParts.push_back(part1);
    objectParts.push_back(part2);
    ShowHow2Do_CompleteMultipartUpload(qsBucket, objectkey, uploadID, objectParts);
    return;
}

void ShowHow2Do_GetObject(Bucket * qsBucket, std::string &objectkey)
{
    if(!qsBucket)
    {
        return;
    }
    GetObjectInput input;
    GetObjectOutput output;
    QsError err = qsBucket->GetObject(objectkey, input, output);
    if(QS_ERR_NO_REQUIRED_PARAMETER == err)
    {
        printf("%s\n" , "The input object lacks some of the parameters that must be filled in.");
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        ResponseErrorInfo  errorInfo = output.GetResponseErrInfo();
        printf("request_id = %s , with detail message : %s\n" , errorInfo.requestID.c_str(), errorInfo.message.c_str());
    }
    if (QS_ERR_NO_ERROR != err)
    {
        return;
    }
    size_t streamSize = 0;
    std::iostream* objectStream = output.GetBody();
    if(objectStream)
    {
        objectStream->seekg(0, objectStream->end);
        streamSize = objectStream->tellg();
    }
    delete objectStream;
    printf("The length of object is : %ld\n" , streamSize);
    return;
}

void ShowHow2Do_DeleteObject(Bucket * qsBucket, std::string &objectkey)
{
    if(!qsBucket)
    {
        return;
    }
    DeleteObjectInput input;
    DeleteObjectOutput output;
    QsError err = qsBucket->DeleteObject(objectkey, input, output);
    if(QS_ERR_NO_REQUIRED_PARAMETER == err)
    {
        printf("%s\n" , "The input object lacks some of the parameters that must be filled in.");
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        ResponseErrorInfo  errorInfo = output.GetResponseErrInfo();
        printf("request_id = %s , with detail message : %s\n" , errorInfo.requestID.c_str(), errorInfo.message.c_str());
    }
    if (QS_ERR_NO_ERROR != err)
    {
        return;
    }
    printf("object(%s) has been deleted.\n" , objectkey.c_str());
    return;
}

int main()
{
    // Read necessary information from environment variables.
    char *strConfigPath = getenv("QINGSTOR_CONFIG_PATH");
    char *strBucketName = getenv("QINGSTOR_BUCKET_NAME");
    char *strZone = getenv("QINGSTOR_ZONE_NAME");
    if(!strConfigPath || !strBucketName || !strZone)
    {
        printf("Envionment variables are missing : QINGSTOR_CONFIG_PATH or QINGSTOR_BUCKET_NAME or QINGSTOR_ZONE_NAME.\n");
        return 1;
    }
    printf("QINGSTOR_CONFIG_PATH: %s.\n",strConfigPath);
    printf("QINGSTOR_BUCKET_NAME: %s.\n",strBucketName);
    printf("QINGSTOR_ZONE_NAME: %s.\n",strZone);
    // Global initialization only needs to be initialized once
    // Valid log levels are "none","debug", "info", "warn", "error", and "fatal".(default value is "None")
    QingStor::SDKOptions sdkOptions;
    sdkOptions.logLevel = Debug;
    sdkOptions.logPath = "/tmp/";
    InitializeSDK(sdkOptions);
    // Create QsConfig object , and init it with config info loaded form ConfigPath.
    // You can also set up the config configuration item separately.
    QingStor::QsConfig qsConfig;
    qsConfig.LoadConfigFile(strConfigPath);
    // Create Bucket object.
    Bucket * qsBucket = new Bucket(qsConfig, strBucketName, strZone);
    ShowHow2Do_ListObjects(qsBucket);
    std::string objectkey = "QingStor_SDK_Test_File";
    ShowHow2Do_MultipartUploadObject(qsBucket, objectkey);
    ShowHow2Do_GetObject(qsBucket, objectkey);
    ShowHow2Do_DeleteObject(qsBucket, objectkey);
    ShutdownSDK(sdkOptions);
    if(qsBucket)
    {
        delete qsBucket;
    }
    return 0;
}






