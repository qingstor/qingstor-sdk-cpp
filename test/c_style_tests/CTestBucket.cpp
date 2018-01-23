//  Scenario: need to use bucket
//    When initialize the bucket
//    Then the bucket is initialized

WHEN("^initialize the bucket$")
{
    init_test_config();
}

THEN("^the bucket is initialized$")
{
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
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    qs_put_bucket_input_t input;
    init_put_bucket_input(&input);
    ScenarioScope<qs_put_bucket_output_t> contextOutput;
    QsError err = qs_put_bucket(&input, &(*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
    }
    qs_release_service(context_hdl);
}

THEN("^put bucket status code is (\\d+)$")
{
    ScenarioScope<qs_put_bucket_output_t> contextOutput;
    release_put_bucket_output(&(*contextOutput));
    EXPECT_EQ(NULL, NULL);
}

/*
Scenario: create the same bucket again
When put same bucket again
Then put same bucket again status code is 409
*/
WHEN("^put same bucket again$")
{
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    qs_put_bucket_input_t input;
    init_put_bucket_input(&input);
    ScenarioScope<qs_put_bucket_output_t> contextOutput;
    QsError err = qs_put_bucket(&input, &(*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
        // print sth
    }
    qs_release_service(context_hdl);
}

THEN("^put same bucket again status code is (\\d+)$")
{
    REGEX_PARAM(int, expected);
    ScenarioScope<qs_put_bucket_output_t> contextOutput;
    release_put_bucket_output(&(*contextOutput));
    EXPECT_EQ(expected, (int)contextOutput->response_code);
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
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    ScenarioScope<qs_list_objects_output_t> contextOutput;
    qs_list_objects_input_t input;
    init_list_objects_input(&input);
    QsError err = qs_list_objects(&input, &(*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
    }
    qs_release_service(context_hdl);
}

THEN("^list objects status code is (\\d+)$")
{
    REGEX_PARAM(int, expected);
    ScenarioScope<qs_list_objects_output_t> contextOutput;
    EXPECT_EQ(expected, (int)contextOutput->response_code);
}

THEN("^list objects keys count is (\\d+)$")
{
    REGEX_PARAM(int, expected);
    ScenarioScope<qs_list_objects_output_t> contextOutput;
    qs_list_t *keys = contextOutput->keys;
    int count = 0;
    qs_key_item_t *pos;
    qs_list_for_each_entry(qs_key_item_t, pos, keys)
    {
        count++;
    }
    release_list_objects_output(&(*contextOutput));
    EXPECT_EQ(expected, count);
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
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    qs_head_bucket_input_t input;
    ScenarioScope<qs_head_bucket_output_t> contextOutput;
    init_head_bucket_input(&input);
    QsError err = qs_head_bucket(&input, &(*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR == err)
    {
        // print sth
    }
    qs_release_service(context_hdl);
}

THEN("^head bucket status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<qs_head_bucket_output_t> contextOutput;
    release_head_bucket_output(&(*contextOutput));
    EXPECT_EQ(expected, (int)contextOutput->response_code);
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
    // do nothing
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    qs_delete_multiple_objects_input_t input;
    init_delete_multiple_objects_input(&input);
    ScenarioScope<qs_delete_multiple_objects_output_t> contextOutput;
    QsError err = qs_delete_multiple_objects(&input, &(*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR == err)
    {
        // print sth
    }
    qs_release_service(context_hdl);
}

THEN("^delete multiple objects code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<qs_delete_multiple_objects_output_t> contextOutput;
    release_delete_multiple_objects_output(&(*contextOutput));
    EXPECT_EQ(expected, expected);
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
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    qs_get_bucket_statistics_input_t input;
    init_get_bucket_statistics_input(&input);
    ScenarioScope<qs_get_bucket_statistics_output_t> contextOutput;
    QsError err = qs_get_bucket_statistics(&input, &(*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR == err)
    {
        // print sth
    }
    qs_release_service(context_hdl);
}

THEN("^get bucket statistics status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<qs_get_bucket_statistics_output_t> contextOutput;
    EXPECT_EQ(expected, (int)contextOutput->response_code);
}

THEN("get bucket statistics status is \"([^\"]*)\"$")
{
    REGEX_PARAM(std::string, expected);
    ScenarioScope<qs_get_bucket_statistics_output_t> contextOutput;
    std::string status = contextOutput->status;
    release_get_bucket_statistics_output(&(*contextOutput));
    EXPECT_EQ(expected, status);
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
    // do nothing
}

THEN("^delete bucket status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    EXPECT_EQ(NULL, NULL);
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
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    ScenarioScope<TestListMultipartUploadsCtx> contextGiven;
    contextGiven->objectKey = (char *)"testInitMultipartUpload.txt";
    qs_initiate_multipart_upload_input_t input;
    ScenarioScope<qs_initiate_multipart_upload_output_t> contextOutput;
    init_initiate_multipart_upload_input(&input);
    QsError err = qs_initiate_multipart_upload((char *)contextGiven->objectKey.c_str(), &input, &(*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR == err && contextOutput->response_code == 200)
    {
        contextGiven->uploadID = contextOutput->upload_id;
    }
    release_initiate_multipart_upload_output(&(*contextOutput));
    qs_upload_multipart_input_t multipartInput;
    qs_upload_multipart_output_t multipartOutput;
    init_upload_multipart_input(&multipartInput);
    printf(" |thi is a Part 3| ");
    long length = strlen(" |thi is a Part 3| ");
    int part_number = strlen(" |thi is a Part 3| ");
    multipartInput.bodybuf = (char *)malloc(length);
    memcpy(multipartInput.bodybuf, " |thi is a Part 3| ", length);
    multipartInput.content_length = &length;
    multipartInput.part_number = &part_number;
    multipartInput.upload_id = (char *)contextGiven->uploadID.c_str();
    multipartInput.bufLength = &length;
    err = qs_upload_multipart((char *)contextGiven->objectKey.c_str(), &multipartInput, &multipartOutput, context_hdl);
    if (QS_ERR_NO_ERROR == err)
    {
    }
    release_upload_multipart_output(&multipartOutput);
    if(multipartInput.bodybuf && multipartInput.content_length)
    {
        free(multipartInput.bodybuf);
    }
    qs_release_service(context_hdl);
}

WHEN("^list multipart uploads$")
{
    ScenarioScope<TestListMultipartUploadsCtx> contextGiven;
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    qs_list_multipart_uploads_input_t input;
    ScenarioScope<qs_list_multipart_uploads_output_t> contextOutput;
    init_list_multipart_uploads_input(&input);
    QsError err = qs_list_multipart_uploads(&input, &(*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR == err)
    {
        // print sth
    }
    qs_release_service(context_hdl);
}

THEN("^list multipart uploads count is (\\d+)$")
{
    REGEX_PARAM(int, expected);
    ScenarioScope<qs_list_multipart_uploads_output_t> contextOutput;
    int count = 0;
    qs_uploads_item_t *pos;
    if(contextOutput->uploads)
    {
        qs_list_for_each_entry(qs_uploads_item_t, pos, contextOutput->uploads)
        {
            count++;
        }
    }
    release_list_multipart_uploads_output(&(*contextOutput));
    // clean env.
    ScenarioScope<TestListMultipartUploadsCtx> contextGiven;
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    qs_delete_object_input_t input;
    qs_delete_object_output_t output;
    init_delete_object_input(&input);
    QsError err = qs_delete_object((char *)contextGiven->objectKey.c_str(), &input, &output, context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
        // print sth
    }
    qs_release_service(context_hdl);
    EXPECT_EQ(expected, count);
}