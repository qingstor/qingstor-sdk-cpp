
//Scenario Outline :
//# Initiate Multipart Upload
//When initiate multipart upload with key "<key>"
//Then initiate multipart upload status code is 200
WHEN ("^initiate multipart upload with key \"(.{1,})\"$")
{
    REGEX_PARAM (std::string, objectkey);
    ScenarioScope<TestListMultipartUploadsCtx> contextMultiPartObjectTest;
    contextMultiPartObjectTest->bucketName = (char *)"testmorvenhuang";
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    contextMultiPartObjectTest->pQsBucket = context_hdl.pQsBucket;
    qs_initiate_multipart_upload_input_t input;
    ScenarioScope<qs_initiate_multipart_upload_output_t> contextOutput;
    init_initiate_multipart_upload_input (&input);
    QsError err = qs_initiate_multipart_upload ((char *) (objectkey.c_str()), &input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR == err)
    {
        contextMultiPartObjectTest->uploadID = contextOutput->upload_id;
    }
    qs_release_service(context_hdl);
}
THEN ("^initiate multipart upload status code is (\\d+)$")
{
    REGEX_PARAM (int, expected);
    ScenarioScope<qs_initiate_multipart_upload_output_t> contextOutput;
    release_initiate_multipart_upload_output (& (*contextOutput));
    EXPECT_EQ (expected, (int)contextOutput->response_code);
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
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    REGEX_PARAM (std::string, objectkey);
    ScenarioScope<TestListMultipartUploadsCtx> contextMultiPartObjectTest;
    qs_upload_multipart_input_t input;
    ScenarioScope<qs_upload_multipart_output_t> contextOutput;
    init_upload_multipart_input (&input);
    //long length = strlen (" |thi is a Part 1| ");
    long length = 5 * 1024 * 1024; //fiveMbSize
    int part_number = 1;
    input.bodybuf = (char *)malloc (length);
    memset(input.bodybuf, 0 , length);
    input.bufLength = &length;
    input.content_length = &length;
    input.part_number = &part_number;
    input.upload_id = (char *)contextMultiPartObjectTest->uploadID.c_str();
    QsError err = qs_upload_multipart ((char *) (objectkey.c_str()), &input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR == err)
    {
        // print sth
    }
    if(input.bodybuf)
    {
        free(input.bodybuf);
        input.bodybuf = NULL;
    }
    qs_release_service(context_hdl);
}
THEN ("^upload the first part status code is (\\d+)$")
{
    REGEX_PARAM (int, expected);
    ScenarioScope<qs_upload_multipart_output_t> contextOutput;
    release_upload_multipart_output (& (*contextOutput));
    EXPECT_EQ (expected, (int)contextOutput->response_code);
}

WHEN ("^upload the second part with key \"(.{1,})\"$")
{
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    REGEX_PARAM (std::string, objectkey);
    qs_upload_multipart_input_t input;
    ScenarioScope<qs_upload_multipart_output_t> contextOutput;
    ScenarioScope<TestListMultipartUploadsCtx> contextMultiPartObjectTest;
    init_upload_multipart_input (&input);
    long length = 5 * 1024 * 1024; //fiveMbSize
    int part_number = 2;
    input.bodybuf = (char *)malloc (length);
    memset(input.bodybuf, 0 , length);
    input.bufLength = &length;
    input.content_length = &length;
    input.part_number = &part_number;
    input.upload_id = (char *)contextMultiPartObjectTest->uploadID.c_str();
    QsError err = qs_upload_multipart ((char *) (objectkey.c_str()), &input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR == err)
    {
        // print sth
    }
    if(input.bodybuf)
    {
        free(input.bodybuf);
        input.bodybuf = NULL;
    }
    qs_release_service(context_hdl);
}
THEN ("^upload the second part status code is (\\d+)$")
{
    REGEX_PARAM (int, expected);
    ScenarioScope<qs_upload_multipart_output_t> contextOutput;
    release_upload_multipart_output (& (*contextOutput));
    EXPECT_EQ (expected, (int)contextOutput->response_code);
}
WHEN ("^upload the third part with key \"(.{1,})\"$")
{
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    REGEX_PARAM (std::string, objectkey);
    qs_upload_multipart_input_t input;
    ScenarioScope<qs_upload_multipart_output_t> contextOutput;
    ScenarioScope<TestListMultipartUploadsCtx> contextMultiPartObjectTest;
    init_upload_multipart_input (&input);
    long length = 5 * 1024 * 1024; //fiveMbSize
    int part_number = 3;
    input.bodybuf = (char *)malloc (length);
    memset(input.bodybuf, 0 , length);
    input.bufLength = &length;
    input.content_length = &length;
    input.part_number = &part_number;
    input.upload_id = (char *)contextMultiPartObjectTest->uploadID.c_str();
    QsError err = qs_upload_multipart ((char *) (objectkey.c_str()), &input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR == err)
    {
    }
    if(input.bodybuf)
    {
        free(input.bodybuf);
        input.bodybuf = NULL;
    }
    qs_release_service(context_hdl);
}
THEN ("^upload the third part status code is (\\d+)$")
{
    REGEX_PARAM (int, expected);
    ScenarioScope<qs_upload_multipart_output_t> contextOutput;
    release_upload_multipart_output (& (*contextOutput));
    EXPECT_EQ (expected, (int)contextOutput->response_code);
}

//# List Multipart
//When list multipart with key "<key>"
//Then list multipart status code is 200
//And list multipart object parts count is 3
WHEN ("^list multipart with key \"(.{1,})\"$")
{
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    REGEX_PARAM (std::string, objectkey);
    ScenarioScope<TestListMultipartUploadsCtx> contextMultiPartObjectTest;
    qs_list_multipart_input_t input;
    ScenarioScope<qs_list_multipart_output_t> contextOutput;
    init_list_multipart_input (&input);
    input.upload_id = (char *)contextMultiPartObjectTest->uploadID.c_str();
    QsError err = qs_list_multipart ((char *) (objectkey.c_str()), &input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR == err)
    {
        // print sth
    }
    qs_release_service(context_hdl);
}

THEN ("^list multipart status code is (\\d+)$")
{
    REGEX_PARAM (int, expected);
    ScenarioScope<qs_list_multipart_output_t> contextOutput;
    EXPECT_EQ (expected, (int)contextOutput->response_code);
}

THEN ("^list multipart object parts count is (\\d+)$")
{
    REGEX_PARAM (int, expected);
    ScenarioScope<qs_list_multipart_output_t> contextOutput;
    int count = 0;
    if (contextOutput->count)
    {
        count = *contextOutput->count;
    }
    release_list_multipart_output (& (*contextOutput));
    EXPECT_EQ (expected, count);
}

//# Complete Multipart Upload
//When complete multipart upload with key "<key>"
//Then complete multipart upload status code is 201
WHEN ("^complete multipart upload with key \"(.{1,})\"$")
{
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    REGEX_PARAM (std::string, objectkey);
    ScenarioScope<TestListMultipartUploadsCtx> contextMultiPartObjectTest;
    qs_complete_multipart_upload_input_t input;
    ScenarioScope<qs_complete_multipart_upload_output_t> contextOutput;
    init_complete_multipart_upload_input (&input);
    qs_list_t object_parts_list;
    qs_list_init (&object_parts_list);
    qs_object_part_item_t object_parts_item_1, object_parts_item_2, object_parts_item_3;
    qs_object_part_t object_parts_1, object_parts_2, object_parts_3;
    init_object_part (&object_parts_1);
    init_object_part (&object_parts_2);
    init_object_part (&object_parts_3);
    int part_number_1 = 1;
    int part_number_2 = 2;
    int part_number_3 = 3;
    object_parts_1.part_number = &part_number_1;
    object_parts_2.part_number = &part_number_2;
    object_parts_3.part_number = &part_number_3;
    object_parts_item_1.content = &object_parts_1;
    object_parts_item_2.content = &object_parts_2;
    object_parts_item_3.content = &object_parts_3;
    qs_list_append (&object_parts_item_1.node, &object_parts_list);
    qs_list_append (&object_parts_item_2.node, &object_parts_list);
    qs_list_append (&object_parts_item_3.node, &object_parts_list);
    input.object_parts = &object_parts_list;
    input.upload_id = (char *)contextMultiPartObjectTest->uploadID.c_str();
    QsError err = qs_complete_multipart_upload ((char *) (objectkey.c_str()), &input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR == err)
    {
    }
    qs_release_service(context_hdl);
}

THEN ("^complete multipart upload status code is (\\d+)$")
{
    REGEX_PARAM (int, expected);
    ScenarioScope<qs_complete_multipart_upload_output_t> contextOutput;
    release_complete_multipart_upload_output (& (*contextOutput));
    EXPECT_EQ (expected, (int)contextOutput->response_code);
}

//# Abort Multipart Upload
//When abort multipart upload with key "<key>"
//Then abort multipart upload status code is 400
WHEN ("^abort multipart upload with key \"(.{1,})\"$")
{
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    REGEX_PARAM (std::string, objectkey);
    ScenarioScope<TestListMultipartUploadsCtx> contextMultiPartObjectTest;
    qs_abort_multipart_upload_input_t input;
    ScenarioScope<qs_abort_multipart_upload_output_t> contextOutput;
    init_abort_multipart_upload_input (&input);
    input.upload_id = (char *)contextMultiPartObjectTest->uploadID.c_str();
    QsError err = qs_abort_multipart_upload ((char *) (objectkey.c_str()), &input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR == err)
    {
    }
    qs_release_service(context_hdl);
}

THEN ("^abort multipart upload status code is (\\d+)$")
{
    REGEX_PARAM (int, expected);
    ScenarioScope<qs_abort_multipart_upload_output_t> contextOutput;
    release_abort_multipart_upload_output (& (*contextOutput));
    EXPECT_EQ (expected, (int)contextOutput->response_code);
}

//# DELETE Object
//When delete the multipart object with key "<key>"
//Then delete the multipart object status code is 204
WHEN ("^delete the multipart object with key \"(.{1,})\"$")
{
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    REGEX_PARAM (std::string, objectkey);
    qs_delete_object_input_t input;
    ScenarioScope<qs_delete_object_output_t> contextOutput;
    init_delete_object_input (&input);
    QsError err = qs_delete_object ((char *) (objectkey.c_str()), &input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR == err)
    {
        // print sth
    }
    qs_release_service(context_hdl);
}

THEN ("^delete the multipart object status code is (\\d+)$")
{
    REGEX_PARAM (int, expected);
    ScenarioScope<qs_delete_object_output_t> contextOutput;
    release_delete_object_output (& (*contextOutput));
    EXPECT_EQ (expected, (int)contextOutput->response_code);
}
