static std::iostream* Create5MbStream4UploadPart(const std::string partTag)
{
    uint32_t fiveMbSize = 5 * 1024 * 1024;
    std::stringstream patternStream;
    patternStream << "Multi-Part upload Test Part " << partTag << ":" << std::endl;
    std::string pattern = patternStream.str();
    std::string scratchString;
    scratchString.reserve(fiveMbSize);
    // 5MB is a hard minimum for multi part uploads; make sure the final string is at least that long
    uint32_t patternCopyCount = static_cast< uint32_t >( fiveMbSize / pattern.size() + 1 );
    for(uint32_t i = 0; i < patternCopyCount; ++i)
    {
        scratchString.append(pattern);
    }
    std::iostream* streamPtr = new std::stringstream(scratchString);
    streamPtr->seekg(0);
    streamPtr->seekp(0, std::ios_base::end);
    return streamPtr;
}

//Scenario Outline :
//# Initiate Multipart Upload
//When initiate multipart upload with key "<key>"
//Then initiate multipart upload status code is 200
WHEN ("^initiate multipart upload with key \"(.{1,})\"$")
{
    REGEX_PARAM (std::string, objectkey);
    ScenarioScope<TestMultipartUploadCtx> contextMultiPartObjectTest;
    contextMultiPartObjectTest->bucketName = strBucketName;
    QingStor::QsConfig qsConfig;
    qsConfig.LoadConfigFile (strConfigPath);
    contextMultiPartObjectTest->pQsBucket = new Bucket (qsConfig, strBucketName, strZone);
    Bucket qsBucket = *contextMultiPartObjectTest->pQsBucket;
    InitiateMultipartUploadInput input;
    ScenarioScope<InitiateMultipartUploadOutput> contextOutput;
    QsError err = qsBucket.InitiateMultipartUpload (objectkey, input, *contextOutput);
    if (QS_ERR_NO_ERROR == err)
    {
        contextMultiPartObjectTest->uploadID = contextOutput->GetUploadID();
    }
}
THEN ("^initiate multipart upload status code is (\\d+)$")
{
    REGEX_PARAM (double, expected);
    ScenarioScope<InitiateMultipartUploadOutput> contextOutput;
    EXPECT_EQ (expected, (double)contextOutput->GetResponseCode());
}

//# Upload Multipart
//When upload the first part with key "<key>"
//Then upload the first part status code is 201
//When upload the second part with key "<key>"
//Then upload the second part status code is 201
//When upload the third part with key "<key>"
//Then upload the third part status code is 201
WHEN ("^upload the first part with key \"(.{1,})\"$")
{
    REGEX_PARAM (std::string, objectkey);
    ScenarioScope<TestMultipartUploadCtx> contextMultiPartObjectTest;
    Bucket qsBucket = *contextMultiPartObjectTest->pQsBucket;
    UploadMultipartInput input;
    ScenarioScope<UploadMultipartOutput> contextOutput;
    std::iostream* objectStream = Create5MbStream4UploadPart("1");
    objectStream->seekg(0, objectStream->end);
    size_t streamSize = objectStream->tellg();
    objectStream->seekg(0, objectStream->beg);
    input.SetContentLength(streamSize);
    input.SetBody (objectStream);
    input.SetPartNumber (1);
    input.SetUploadID (contextMultiPartObjectTest->uploadID);
    QsError err = qsBucket.UploadMultipart (objectkey, input, *contextOutput);
    if (QS_ERR_NO_ERROR == err)
    {
    }
    delete objectStream;
}
THEN ("^upload the first part status code is (\\d+)$")
{
    REGEX_PARAM (double, expected);
    ScenarioScope<UploadMultipartOutput> contextOutput;
    EXPECT_EQ (expected, (double)contextOutput->GetResponseCode());
}

WHEN ("^upload the second part with key \"(.{1,})\"$")
{
    REGEX_PARAM (std::string, objectkey);
    ScenarioScope<TestMultipartUploadCtx> contextMultiPartObjectTest;
    Bucket qsBucket = *contextMultiPartObjectTest->pQsBucket;
    UploadMultipartInput input;
    ScenarioScope<UploadMultipartOutput> contextOutput;
    std::iostream* objectStream = Create5MbStream4UploadPart("2");
    objectStream->seekg(0, objectStream->end);
    size_t streamSize = objectStream->tellg();
    objectStream->seekg(0, objectStream->beg);
    input.SetContentLength(streamSize);
    input.SetBody (objectStream);
    input.SetPartNumber (2);
    input.SetUploadID (contextMultiPartObjectTest->uploadID);
    QsError err = qsBucket.UploadMultipart (objectkey, input, *contextOutput);
    if (QS_ERR_NO_ERROR == err)
    {
    }
    delete objectStream;
}
THEN ("^upload the second part status code is (\\d+)$")
{
    REGEX_PARAM (double, expected);
    ScenarioScope<UploadMultipartOutput> contextOutput;
    EXPECT_EQ (expected, (double)contextOutput->GetResponseCode());
}
WHEN ("^upload the third part with key \"(.{1,})\"$")
{
    REGEX_PARAM (std::string, objectkey);
    ScenarioScope<TestMultipartUploadCtx> contextMultiPartObjectTest;
    Bucket qsBucket = *contextMultiPartObjectTest->pQsBucket;
    UploadMultipartInput input;
    ScenarioScope<UploadMultipartOutput> contextOutput;
    std::iostream* objectStream = Create5MbStream4UploadPart("3");
    objectStream->seekg(0, objectStream->end);
    size_t streamSize = objectStream->tellg();
    objectStream->seekg(0, objectStream->beg);
    input.SetContentLength(streamSize);
    input.SetBody (objectStream);
    input.SetPartNumber (3);
    input.SetUploadID (contextMultiPartObjectTest->uploadID);
    QsError err = qsBucket.UploadMultipart (objectkey, input, *contextOutput);
    if (QS_ERR_NO_ERROR == err)
    {
    }
    delete objectStream;
}
THEN ("^upload the third part status code is (\\d+)$")
{
    REGEX_PARAM (double, expected);
    ScenarioScope<UploadMultipartOutput> contextOutput;
    EXPECT_EQ (expected, (double)contextOutput->GetResponseCode());
}

//# List Multipart
//When list multipart with key "<key>"
//Then list multipart status code is 200
//And list multipart object parts count is 3
WHEN ("^list multipart with key \"(.{1,})\"$")
{
    REGEX_PARAM (std::string, objectkey);
    ScenarioScope<TestMultipartUploadCtx> contextMultiPartObjectTest;
    Bucket qsBucket = *contextMultiPartObjectTest->pQsBucket;
    ListMultipartInput input;
    ScenarioScope<ListMultipartOutput> contextOutput;
    input.SetUploadID (contextMultiPartObjectTest->uploadID);
    QsError err = qsBucket.ListMultipart (objectkey, input, *contextOutput);
    if (QS_ERR_NO_ERROR == err)
    {
        contextMultiPartObjectTest->objectParts = contextOutput->GetObjectParts();
    }
}

THEN ("^list multipart status code is (\\d+)$")
{
    REGEX_PARAM (double, expected);
    ScenarioScope<ListMultipartOutput> contextOutput;
    EXPECT_EQ (expected, (double)contextOutput->GetResponseCode());
}

THEN ("^list multipart object parts count is (\\d+)$")
{
    REGEX_PARAM (double, expected);
    ScenarioScope<ListMultipartOutput> contextOutput;
    EXPECT_EQ (expected, (double)contextOutput->GetCount());
}

//# Complete Multipart Upload
//When complete multipart upload with key "<key>"
//Then complete multipart upload status code is 201
WHEN ("^complete multipart upload with key \"(.{1,})\"$")
{
    REGEX_PARAM (std::string, objectkey);
    ScenarioScope<TestMultipartUploadCtx> contextMultiPartObjectTest;
    Bucket qsBucket = *contextMultiPartObjectTest->pQsBucket;
    CompleteMultipartUploadInput input;
    ScenarioScope<CompleteMultipartUploadOutput> contextOutput;
    input.SetUploadID (contextMultiPartObjectTest->uploadID);
    input.SetObjectParts(contextMultiPartObjectTest->objectParts);
    QsError err = qsBucket.CompleteMultipartUpload (objectkey, input, *contextOutput);
    if (QS_ERR_NO_ERROR == err)
    {
    }
}

THEN ("^complete multipart upload status code is (\\d+)$")
{
    REGEX_PARAM (double, expected);
    ScenarioScope<CompleteMultipartUploadOutput> contextOutput;
    EXPECT_EQ (expected, (double)contextOutput->GetResponseCode());
}

//# Abort Multipart Upload
//When abort multipart upload with key "<key>"
//Then abort multipart upload status code is 400
WHEN ("^abort multipart upload with key \"(.{1,})\"$")
{
    REGEX_PARAM (std::string, objectkey);
    ScenarioScope<TestMultipartUploadCtx> contextMultiPartObjectTest;
    Bucket qsBucket = *contextMultiPartObjectTest->pQsBucket;
    AbortMultipartUploadInput input;
    ScenarioScope<AbortMultipartUploadOutput> contextOutput;
    input.SetUploadID (contextMultiPartObjectTest->uploadID);
    QsError err = qsBucket.AbortMultipartUpload (objectkey, input, *contextOutput);
    if (QS_ERR_NO_ERROR == err)
    {
    }
}

THEN ("^abort multipart upload status code is (\\d+)$")
{
    REGEX_PARAM (double, expected);
    ScenarioScope<AbortMultipartUploadOutput> contextOutput;
    EXPECT_EQ (expected, (double)contextOutput->GetResponseCode());
}

//# DELETE Object
//When delete the multipart object with key "<key>"
//Then delete the multipart object status code is 204
WHEN ("^delete the multipart object with key \"(.{1,})\"$")
{
    REGEX_PARAM (std::string, objectkey);
    ScenarioScope<TestMultipartUploadCtx> contextMultiPartObjectTest;
    Bucket qsBucket = *contextMultiPartObjectTest->pQsBucket;
    DeleteObjectInput input;
    ScenarioScope<DeleteObjectOutput> contextOutput;
    QsError err = qsBucket.DeleteObject(objectkey, input, *contextOutput);
    if (QS_ERR_NO_ERROR == err)
    {
    }
    delete contextMultiPartObjectTest->pQsBucket;
}

THEN ("^delete the multipart object status code is (\\d+)$")
{
    REGEX_PARAM (double, expected);
    ScenarioScope<DeleteObjectOutput> contextOutput;
    EXPECT_EQ (expected, (double)contextOutput->GetResponseCode());
}
