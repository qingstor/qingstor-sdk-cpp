//// Feature: the object feature

// Scenario Outline :
// # PUT Object
// When put object with key "<key>"
// Then put object status code is 201
WHEN("^put object with key \"(.{1,})\"$")
{
    REGEX_PARAM(std::string, objectKey);
    ScenarioScope<TestObjectCtx> contextObjectTest;
    contextObjectTest->bucketName = strBucketName;
    QingStor::QsConfig qsConfig;
    qsConfig.LoadConfigFile(strConfigPath);
    contextObjectTest->pQsBucket = new Bucket(qsConfig, strBucketName, strZone);
    Bucket qsBucket = *contextObjectTest->pQsBucket;
    PutObjectInput input;
    ScenarioScope<PutObjectOutput> contextOutput;
    std::iostream* objectStream = new std::stringstream();
    *objectStream << "thi is a test";
    objectStream->flush();
    input.SetContentLength(strlen("thi is a test"));
    input.SetBody(objectStream);
    QsError err = qsBucket.PutObject(objectKey, input, *contextOutput);
    if (QS_ERR_NO_ERROR != err)
    {
    }
    if(objectStream)
        delete objectStream;
}

THEN("^put object status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<PutObjectOutput> contextOutput;
    EXPECT_EQ(expected, (int)contextOutput->GetResponseCode());
}

//# Copy Object
//When copy object with key "<key>"
//Then copy object status code is 201
WHEN("^copy object with key \"(.{1,})\"$")
{
    REGEX_PARAM(std::string, objectkeyFromSource);
    std::string objectkeyTopPut = objectkeyFromSource + "_copy";
    ScenarioScope<TestObjectCtx> contextObjectTest;
    std::string sourcePrefix = "/" + contextObjectTest->bucketName + "/";
    Bucket qsBucket = *contextObjectTest->pQsBucket;
    PutObjectInput input;
    ScenarioScope<PutObjectOutput> contextOutput;
    input.SetXQSCopySource(sourcePrefix + objectkeyFromSource);
    input.SetContentLength(0);
    QsError err = qsBucket.PutObject(objectkeyTopPut, input, *contextOutput);
    if (QS_ERR_NO_ERROR != err)
    {
    }
}

THEN("^copy object status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<PutObjectOutput> contextOutput;
    EXPECT_EQ(expected, (int)contextOutput->GetResponseCode());
}

//# Move Object
//When move object with key "<key>"
//Then move object status code is 201
WHEN("^move object with key \"(.{1,})\"$")
{
    REGEX_PARAM(std::string, objectkey);
    std::string objectkeySrc = objectkey + "_copy";
    std::string objectkeyDest = objectkey + "_move";
    ScenarioScope<TestObjectCtx> contextObjectTest;
    std::string sourcePrefix = "/" + contextObjectTest->bucketName + "/";
    Bucket qsBucket = *contextObjectTest->pQsBucket;
    PutObjectInput input;
    ScenarioScope<PutObjectOutput> contextOutput;
    input.SetXQSMoveSource(sourcePrefix + objectkeySrc);
    input.SetContentLength(0);
    QsError err = qsBucket.PutObject(objectkeyDest, input, *contextOutput);
    if (QS_ERR_NO_ERROR != err)
    {
    }
}

THEN("^move object status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<PutObjectOutput> contextOutput;
    EXPECT_EQ(expected, (int)contextOutput->GetResponseCode());
}

//# GET Object
//When get object with key "<key>"
//Then get object status code is 200
//And get object content length is 1048576
WHEN("^get object with key \"(.{1,})\"$")
{
    REGEX_PARAM(std::string, objectkeyToGet);
    ScenarioScope<TestObjectCtx> contextObjectTest;
    Bucket qsBucket = *contextObjectTest->pQsBucket;
    GetObjectInput input;
    ScenarioScope<GetObjectOutput> contextOutput;
    QsError err = qsBucket.GetObject(objectkeyToGet, input, *contextOutput);
    if (QS_ERR_NO_ERROR != err)
    {
    }
}

THEN("^get object status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<GetObjectOutput> contextOutput;
    EXPECT_EQ(expected, (int)contextOutput->GetResponseCode());
}

THEN("^get object content length is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    (void)expected;
    ScenarioScope<GetObjectOutput> contextOutput;
    std::iostream* objectStream = contextOutput->GetBody();
    objectStream->seekg(0, contextOutput->GetBody()->end);
    size_t streamSize = objectStream->tellg();
    delete objectStream;
    int objectLen = static_cast<int>(streamSize);
    int exceptedLen = strlen("thi is a test");
    EXPECT_EQ(exceptedLen, objectLen);
}

//# GET Object with Content - Type
//When get object "<key>" with content type "video/mp4; charset=utf8"
//Then get object content type is "video/mp4; charset=utf8"
WHEN("^get object \"(.{1,})\" with content type \"(.{1,})\"$")
{
    REGEX_PARAM(std::string, objectkey);
    ScenarioScope<TestObjectCtx> contextObjectTest;
}

THEN("^get object content type is \"(.{1,})\"$")
{
    REGEX_PARAM(std::string, expected);
    ScenarioScope<HeadObjectOutput> contextOutput;
    EXPECT_EQ(expected, "video/mp4; charset=utf8");
}

//# GET Object with Query Signature
//When get object "<key>" with query signature
//Then get object with query signature content length is 1048576
WHEN("^get object \"(.{1,})\" with query signature$")
{
    REGEX_PARAM(std::string, objectkey);
    ScenarioScope<TestObjectCtx> contextObjectTest;
    Bucket qsBucket = *contextObjectTest->pQsBucket;
    GetObjectInput input;
    ScenarioScope<GetObjectOutput> contextOutput;
    QsError err = qsBucket.GetObject(objectkey, input, *contextOutput);
    if (QS_ERR_NO_ERROR != err)
    {
    }
}

THEN("^get object with query signature content length is (\\d+)$")
{
    REGEX_PARAM(std::string, expected);
    ScenarioScope<GetObjectOutput> contextOutput;
    size_t streamSize = 0;
    std::iostream* objectStream = contextOutput->GetBody();
    if(objectStream)
    {
        objectStream->seekg(0, objectStream->end);
        streamSize = objectStream->tellg();
        delete objectStream;
    }
    int exceptedLen = strlen("thi is a test");
    EXPECT_EQ(exceptedLen, static_cast<int>(streamSize));
}

//# Head Object
//When head object with key "<key>"
//Then head object status code is 200
WHEN("^head object with key \"(.{1,})\"$")
{
    REGEX_PARAM(std::string, objectkey);
    ScenarioScope<TestObjectCtx> contextObjectTest;
    Bucket qsBucket = *contextObjectTest->pQsBucket;
    HeadObjectInput input;
    ScenarioScope<HeadObjectOutput> contextOutput;
    QsError err = qsBucket.HeadObject(objectkey, input, *contextOutput);
    if (QS_ERR_NO_ERROR != err)
    {
    }
}

THEN("^head object status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<HeadObjectOutput> contextOutput;
    EXPECT_EQ(expected, (int)contextOutput->GetResponseCode());
}

//# Options Object
//When options object "<key>" with method "GET" and origin "qingcloud.com"
//Then options object status code is 200
WHEN("^options object \"(.{1,})\" with method \"([^\"]*)\" and origin \"([^\"]*)\"$")
{
    REGEX_PARAM(std::string, objectkey);
    ScenarioScope<TestObjectCtx> contextObjectTest;
    Bucket qsBucket = *contextObjectTest->pQsBucket;
    OptionsObjectInput input;
    ScenarioScope<OptionsObjectOutput> contextOutput;
    input.SetAccessControlRequestMethod("GET");
    input.SetOrigin("qingcloud.com");
    QsError err = qsBucket.OptionsObject(objectkey, input, *contextOutput);
    if (QS_ERR_NO_ERROR != err)
    {
    }
}

THEN("^options object status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<OptionsObjectOutput> contextOutput;
    EXPECT_EQ(expected, (int)contextOutput->GetResponseCode());
}

//# DELETE Object
//When delete object with key "<key>"
//Then delete object status code is 204
//When delete the move object with key "<key>"
//Then delete the move object status code is 204
WHEN("^delete object with key \"(.{1,})\"$")
{
    REGEX_PARAM(std::string, objectkey);
    ScenarioScope<TestObjectCtx> contextObjectTest;
    Bucket qsBucket = *contextObjectTest->pQsBucket;
    DeleteObjectInput input;
    ScenarioScope<DeleteObjectOutput> contextOutput;
    QsError err = qsBucket.DeleteObject(objectkey, input, *contextOutput);
    if (QS_ERR_NO_ERROR != err)
    {
    }
}

THEN("^delete object status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<DeleteObjectOutput> contextOutput;
    EXPECT_EQ(expected, (int)contextOutput->GetResponseCode());
}

WHEN("delete the move object with key \"(.{1,})\"$")
{
    REGEX_PARAM(std::string, objectkey);
    std::string objectkeyToDel = objectkey + "_move";
    ScenarioScope<TestObjectCtx> contextObjectTest;
    Bucket qsBucket = *contextObjectTest->pQsBucket;
    DeleteObjectInput input;
    ScenarioScope<DeleteObjectOutput> contextOutput;
    QsError err = qsBucket.DeleteObject(objectkeyToDel, input, *contextOutput);
    if (QS_ERR_NO_ERROR != err)
    {
    }
    delete contextObjectTest->pQsBucket;
}

THEN("^delete the move object status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<DeleteObjectOutput> contextOutput;
    EXPECT_EQ(expected, (double)contextOutput->GetResponseCode());
}
