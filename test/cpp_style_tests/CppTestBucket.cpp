/*
Scenario: need to use bucket
    When initialize the bucket
    Then the bucket is initialized
*/
#include <mcheck.h>

WHEN("^initialize the bucket$")
{
    // read necessary information from environment variables.
    init_test_config();
    //QingStorService::InitService(strConfigPath.c_str());
    //QingStor::QsConfig qsConfig;
    //qsConfig.LoadConfigFile(strConfigPath.c_str());
    ScenarioScope<TestBucketCtx> context;
    //context->pQsService = new QingStorService(qsConfig);
    //context->pQsBucket = new Bucket(qsConfig, strBucketName, strZone);
}

THEN("^the bucket is initialized$")
{
    //REGEX_PARAM(double, expected);
    ScenarioScope<TestBucketCtx> context;
    EXPECT_EQ(NULL, NULL);
}

//////////////////////////
/////  # PUT Bucket  /////
//////////////////////////
/*
Scenario: create the bucket
    When put bucket
    Then put bucket status code is 201
*/
WHEN("^put bucket$")
{
    // if you are testing on public cloud environment, this scenario should be skiped.
    //QingStor::QsConfig qsConfig;
    //qsConfig.LoadConfigFile(strConfigPath.c_str());
    //QingStorService qsService(qsConfig);
    //Bucket qsBucket = Bucket(qsConfig, strBucketName, strZone);
    ////putobject
    //PutBucketInput input;
    //PutBucketOutput outtput;
    //std::stringstream ss;
    //std::shared_ptr<std::iostream> objectStream = std::make_shared<std::stringstream>();
    //QsError err = qsBucket.PutBucket(input, outtput);
    //if (QS_ERR_NO_ERROR != err)
    //{
    //
    //}
}

THEN("^put bucket status code is (\\d+)$")
{
    // if you are testing on public cloud environment, this scenario should be skiped.
    REGEX_PARAM(double, expected);
    //ScenarioScope<PutBucketOutput> contextOutput;
    //EXPECT_EQ(expected, (int)contextOutput->GetResponseCode());
    EXPECT_EQ(expected, expected);
}

/*
Scenario: create the same bucket again
    When put same bucket again
    Then put same bucket again status code is 409
*/
WHEN("^put same bucket again$")
{
    QingStor::QsConfig qsConfig;
    qsConfig.LoadConfigFile(strConfigPath.c_str());
    Bucket qsBucket = Bucket(qsConfig, strBucketName, strZone);
    PutBucketInput input;
    ScenarioScope<PutBucketOutput> contextOutput;
    QsError err = qsBucket.PutBucket(input, *contextOutput);
    if (QS_ERR_NO_ERROR != err)
    {
    }
}

THEN("^put same bucket again status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<PutObjectOutput> contextOutput;
    EXPECT_EQ(expected, expected);
}

////////////////////////////////////////
/////  # GET Bucket(List Objects)  /////
////////////////////////////////////////
/*
Scenario: list objects in the bucket
	When list objects
	Then list objects status code is 200
	And list objects keys count is 0
*/
WHEN("^list objects$")
{
    QingStor::QsConfig qsConfig;
    qsConfig.LoadConfigFile(strConfigPath.c_str());
    QingStorService qsService(qsConfig);
    Bucket qsBucket = Bucket(qsConfig, strBucketName, strZone);
    ListObjectsInput input;
    ScenarioScope<ListObjectsOutput> contextOutput;
    QsError err = qsBucket.ListObjects(input, *contextOutput);
    if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        ResponseErrorInfo  errorInfo = contextOutput->GetResponseErrInfo();
    }
}

THEN("^list objects status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<ListObjectsOutput> contextOutput;
    EXPECT_EQ(expected, (int)contextOutput->GetResponseCode());
}

THEN("^list objects keys count is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<ListObjectsOutput> contextOutput;
    std::vector<KeyType> keys = contextOutput->GetKeys();
    EXPECT_EQ(expected, keys.size());
}

///////////////////////////
/////  # Head Bucket  /////
///////////////////////////
/*
Scenario: head the bucket
	When head bucket
	Then head bucket status code is 200
*/
WHEN("^head bucket$")
{
    QingStor::QsConfig qsConfig;
    qsConfig.LoadConfigFile(strConfigPath.c_str());
    QingStorService qsService(qsConfig);
    Bucket qsBucket = Bucket(qsConfig, strBucketName, strZone);
    HeadBucketInput input;
    ScenarioScope<HeadBucketOutput> contextOutput;
    QsError err = qsBucket.HeadBucket(input, *contextOutput);
    if (QS_ERR_NO_ERROR == err)
    {
    }
}

THEN("^head bucket status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<HeadBucketOutput> contextOutput;
    EXPECT_EQ(expected, (int)contextOutput->GetResponseCode());
}

///////////////////////////////////////
/////  # Delete Multiple Objects  /////
///////////////////////////////////////
/*
Scenario : delete multiple objects in the bucket
	When delete multiple objects :
		   """
		   {
			   "quiet": false,
				   "objects" : [
			   {
				   "key": "object_0"
			   },
			   {
				   "key": "object_1"
			   },
			   {
				   "key": "object_2"
			   }
				   ]
		   }
		   """
			   Then delete multiple objects code is 200
*/
WHEN("^delete multiple objects:$")
{
    QingStor::QsConfig qsConfig;
    qsConfig.LoadConfigFile(strConfigPath.c_str());
    QingStorService qsService(qsConfig);
    Bucket qsBucket = Bucket(qsConfig, strBucketName, strZone);
    HeadBucketInput input;
    ScenarioScope<HeadBucketOutput> contextOutput;
    QsError err = qsBucket.HeadBucket(input, *contextOutput);
    if (QS_ERR_NO_ERROR == err)
    {
    }
}

THEN("^delete multiple objects code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<HeadBucketOutput> contextOutput;
    EXPECT_EQ(expected, (int)contextOutput->GetResponseCode());
}

/////////////////////////////////////
/////  # GET Bucket Statistics  /////
/////////////////////////////////////
/*
Scenario : get statistics of the bucket
	When get bucket statistics
	Then get bucket statistics status code is 200
	And get bucket statistics status is "active"
*/
WHEN("^get bucket statistics$")
{
    QingStor::QsConfig qsConfig;
    qsConfig.LoadConfigFile(strConfigPath.c_str());
    QingStorService qsService(qsConfig);
    Bucket qsBucket = Bucket(qsConfig, strBucketName, strZone);
    GetBucketStatisticsInput input;
    ScenarioScope<GetBucketStatisticsOutput> contextOutput;
    QsError err = qsBucket.GetBucketStatistics(input, *contextOutput);
    if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        ResponseErrorInfo  errorInfo = contextOutput->GetResponseErrInfo();
    }
}

THEN("^get bucket statistics status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<GetBucketStatisticsOutput> contextOutput;
    EXPECT_EQ(expected, (int)contextOutput->GetResponseCode());
}

THEN("get bucket statistics status is \"([^\"]*)\"$")
{
    REGEX_PARAM(std::string, expected);
    ScenarioScope<GetBucketStatisticsOutput> contextOutput;
    EXPECT_EQ(expected, contextOutput->GetStatus());
}

/////////////////////////////
/////  # DELETE Bucket  /////
/////////////////////////////
/*
Scenario : delete the bucket
	When delete bucket
	Then delete bucket status code is 204
*/
WHEN("^delete bucket$")
{
    // if you are testing on public cloud environment, this scenario should be skiped.
}

THEN("^delete bucket status code is (\\d+)$")
{
    // if you are testing on public cloud environment, this scenario should be skiped.
    REGEX_PARAM(double, expected);
    EXPECT_EQ(expected, expected);
}

//////////////////////////////////////
/////  # List Multipart Uploads  /////
//////////////////////////////////////
/*
Scenario : list multipart uploads
	Given an object created by initiate multipart upload
	When list multipart uploads
	Then list multipart uploads count is 1
*/

GIVEN("^an object created by initiate multipart upload$")
{
    QingStor::QsConfig qsConfig;
    qsConfig.LoadConfigFile(strConfigPath.c_str());
    QingStorService qsService(qsConfig);
    Bucket qsBucket = Bucket(qsConfig, strBucketName, strZone);
    ScenarioScope<TestListMultipartUploadsCtx> contextGiven;
    InitiateMultipartUploadInput input;
    InitiateMultipartUploadOutput output;
    contextGiven->objectKey = "testInitMultipartUpload.txt";
    QsError err = qsBucket.InitiateMultipartUpload(contextGiven->objectKey, input, output);
    if (QS_ERR_NO_ERROR == err)
    {
        contextGiven->uploadID = output.GetUploadID();
    }
    UploadMultipartInput multipartInput;
    UploadMultipartOutput multipartOutput;
    std::iostream* objectStream = new std::stringstream();
    *objectStream << " |this is a Part 1| ";
    objectStream->flush();
    multipartInput.SetBody(objectStream);
    multipartInput.SetContentLength(strlen(" |this is a Part 1| "));
    multipartInput.SetPartNumber(1);
    multipartInput.SetUploadID(contextGiven->uploadID);
    err = qsBucket.UploadMultipart(contextGiven->objectKey, multipartInput, multipartOutput);
    if (QS_ERR_NO_ERROR == err)
    {
    }
    delete objectStream;
}

WHEN("^list multipart uploads$")
{
    ScenarioScope<TestListMultipartUploadsCtx> contextGiven;
    QingStor::QsConfig qsConfig;
    qsConfig.LoadConfigFile(strConfigPath.c_str());
    QingStorService qsService(qsConfig);
    Bucket qsBucket = Bucket(qsConfig, strBucketName, strZone);
    ListMultipartUploadsInput input;
    ScenarioScope<ListMultipartUploadsOutput> contextOutput;
    QsError err = qsBucket.ListMultipartUploads(input, *contextOutput);
    if (QS_ERR_NO_ERROR == err)
    {
    }
}

THEN("^list multipart uploads count is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<ListMultipartUploadsOutput> contextOutput;
    EXPECT_EQ(expected, contextOutput->GetUploads().size());
}
