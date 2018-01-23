//// Feature: the object feature

// Scenario Outline :
// # PUT Object
// When put object with key "<key>"
// Then put object status code is 201
WHEN ("^put object with key \"(.{1,})\"$")
{
    init_test_config();
    typedef char *String;
    REGEX_PARAM (std::string, objectKey);
    ScenarioScope<TestObjectCtx> contextObjectTest;
    contextObjectTest->bucketName = strBucketName;
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    qs_put_object_input_t input;
    ScenarioScope<qs_put_object_output_t> contextOutput;
    init_put_object_input (&input);
    long length = strlen ("this is a test");
    input.bodybuf = (String)malloc (length + 1);
    memset(input.bodybuf, 0, length + 1);
    memcpy (input.bodybuf, "this is a test", length);
    input.content_length = &length;
    input.bufLength = &length;
    char * object_key = (char *)malloc(objectKey.length() + 1);
    memset(object_key,0,objectKey.length() +1 );
    strncpy(object_key, objectKey.c_str() , objectKey.length());
    QsError err = qs_put_object (object_key, &input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
    }
    if(input.bodybuf && input.bufLength)
    {
        free(input.bodybuf);
    }
    free(object_key);
    qs_release_service(context_hdl);
}

THEN ("^put object status code is (\\d+)$")
{
    REGEX_PARAM (int, expected);
    ScenarioScope<qs_put_object_output_t> contextOutput;
    release_put_object_output (& (*contextOutput));
    EXPECT_EQ (expected, (int)contextOutput->response_code);
}

//# Copy Object
//When copy object with key "<key>"
//Then copy object status code is 201
WHEN ("^copy object with key \"(.{1,})\"$")
{
    REGEX_PARAM (std::string, objectkeyFromSource);
    std::string objectkeyTopPut = objectkeyFromSource + "_copy";
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    ScenarioScope<TestObjectCtx> contextObjectTest;
    std::string copySource = (char *)"/" + contextObjectTest->bucketName + "/" + objectkeyFromSource;
    qs_put_object_input_t input;
    ScenarioScope<qs_put_object_output_t> contextOutput;
    init_put_object_input (&input);
    input.x_qs_copy_source = (char *)copySource.c_str();
    long content_length = 0;
    input.content_length = &content_length;
    char * object_key = (char *)malloc(objectkeyTopPut.length() + 1);
    memset(object_key,0,objectkeyTopPut.length() + 1);
    strncpy(object_key, objectkeyTopPut.c_str() , objectkeyTopPut.length());
    QsError err = qs_put_object (object_key, &input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
        // print sth
    }
    free(object_key);
    qs_release_service(context_hdl);
}

THEN ("^copy object status code is (\\d+)$")
{
    REGEX_PARAM (int, expected);
    ScenarioScope<qs_put_object_output_t> contextOutput;
    release_put_object_output (& (*contextOutput));
    EXPECT_EQ (expected, (int)contextOutput->response_code);
}

//# Move Object
//When move object with key "<key>"
//Then move object status code is 201
WHEN ("^move object with key \"(.{1,})\"$")
{
    REGEX_PARAM (std::string, objectkey);
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    std::string objectkeySrc = objectkey + "_copy";
    std::string objectkeyDest = objectkey + "_move";
    ScenarioScope<TestObjectCtx> contextObjectTest;
    std::string moveSource = (char *)"/" + contextObjectTest->bucketName + "/" + objectkeySrc;
    qs_put_object_input_t input;
    ScenarioScope<qs_put_object_output_t> contextOutput;
    init_put_object_input (&input);
    input.x_qs_move_source = (char *)moveSource.c_str();
    long content_length = 0;
    input.content_length = &content_length;
    char * object_key = (char *)malloc(objectkey.length() + 1);
    memset(object_key,0,objectkey.length() + 1);
    strncpy(object_key, objectkey.c_str() , objectkey.length());
    QsError err = qs_put_object (object_key, &input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
        // print sth
    }
    free(object_key);
    qs_release_service(context_hdl);
}

THEN ("^move object status code is (\\d+)$")
{
    REGEX_PARAM (int, expected);
    ScenarioScope<qs_put_object_output_t> contextOutput;
    release_put_object_output (& (*contextOutput));
    EXPECT_EQ (expected, (int)contextOutput->response_code);
}

//# GET Object
//When get object with key "<key>"
//Then get object status code is 200
//And get object content length is 1048576
WHEN ("^get object with key \"(.{1,})\"$")
{
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    REGEX_PARAM (std::string, objectkeyToGet);
    qs_get_object_input_t input;
    ScenarioScope<qs_get_object_output_t> contextOutput;
    init_get_object_input (&input);
    char * object_key = (char *)malloc(objectkeyToGet.length() + 1);
    memset(object_key,0,objectkeyToGet.length()+1);
    strncpy(object_key, objectkeyToGet.c_str() , objectkeyToGet.length());
    QsError err = qs_get_object (object_key, &input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
        // print sth
    }
    free(object_key);
    qs_release_service(context_hdl);
}

THEN ("^get object status code is (\\d+)$")
{
    REGEX_PARAM (int, expected);
    ScenarioScope<qs_get_object_output_t> contextOutput;
    EXPECT_EQ (expected, (int)contextOutput->response_code);
}

THEN ("^get object content length is (\\d+)$")
{
    REGEX_PARAM (int, expected);
    (void)expected;
    ScenarioScope<qs_get_object_output_t> contextOutput;
    int objectLen = 0;
    if (contextOutput->bufLength && contextOutput->bodybuf)
    {
        objectLen = (int) (*contextOutput->bufLength);
    }
    int exceptedLen = strlen ("this is a test");
    release_get_object_output (& (*contextOutput));
    EXPECT_EQ (exceptedLen, objectLen);
}

//# GET Object with Content - Type
//When get object "<key>" with content type "video/mp4; charset=utf8"
//Then get object content type is "video/mp4; charset=utf8"
WHEN ("^get object \"(.{1,})\" with content type \"(.{1,})\"$")
{
    REGEX_PARAM (std::string, objectkey);
    ScenarioScope<TestObjectCtx> contextObjectTest;
}

THEN ("^get object content type is \"(.{1,})\"$")
{
    //typedef char* String;
    REGEX_PARAM (std::string, expected);
    EXPECT_EQ (expected, "video/mp4; charset=utf8");
}

//# GET Object with Query Signature
//When get object "<key>" with query signature
//Then get object with query signature content length is 1048576
WHEN ("^get object \"(.{1,})\" with query signature$")
{
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    REGEX_PARAM (std::string, objectkey);
    qs_get_object_input_t input;
    ScenarioScope<qs_get_object_output_t> contextOutput;
    init_get_object_input (&input);
    char * object_key = (char *)malloc(objectkey.length() + 1);
    memset(object_key,0,objectkey.length() + 1);
    strncpy(object_key, objectkey.c_str() , objectkey.length());
    QsError err = qs_get_object (object_key, &input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
        // print sth
    }
    free(object_key);
    qs_release_service(context_hdl);
}

THEN ("^get object with query signature content length is (\\d+)$")
{
    ScenarioScope<qs_get_object_output_t> contextOutput;
    int objectLen = 0;
    if (contextOutput->bufLength && contextOutput->bodybuf)
    {
        objectLen = (int) (*contextOutput->bufLength);
    }
    int exceptedLen = strlen ("this is a test");
    release_get_object_output (& (*contextOutput));
    EXPECT_EQ (exceptedLen, objectLen);
}

//# Head Object
//When head object with key "<key>"
//Then head object status code is 200
WHEN ("^head object with key \"(.{1,})\"$")
{
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    REGEX_PARAM (std::string, objectkey);
    qs_head_object_input_t input;
    ScenarioScope<qs_head_object_output_t> contextOutput;
    init_head_object_input (&input);
    char * object_key = (char *)malloc(objectkey.length() + 1);
    memset(object_key,0,objectkey.length() + 1);
    strncpy(object_key, objectkey.c_str() , objectkey.length());
    QsError err = qs_head_object (object_key, &input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
        // print sth
    }
    free(object_key);
    qs_release_service(context_hdl);
}

THEN ("^head object status code is (\\d+)$")
{
    REGEX_PARAM (int, expected);
    ScenarioScope<qs_head_object_output_t> contextOutput;
    release_head_object_output (& (*contextOutput));
    EXPECT_EQ (expected, (int)contextOutput->response_code);
}

//# Options Object
//When options object "<key>" with method "GET" and origin "qingcloud.com"
//Then options object status code is 200
WHEN ("^options object \"(.{1,})\" with method \"([^\"]*)\" and origin \"([^\"]*)\"$")
{
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    REGEX_PARAM (std::string, objectkey);
    qs_options_object_input_t input;
    ScenarioScope<qs_options_object_output_t> contextOutput;
    init_options_object_input (&input);
    input.access_control_request_method = (char *)"GET";
    input.origin = (char *)"qingcloud.com";
    char * object_key = (char *)malloc(objectkey.length() + 1);
    memset(object_key,0,objectkey.length() + 1);
    strncpy(object_key, objectkey.c_str() , objectkey.length());
    QsError err = qs_options_object (object_key, &input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
        // print sth
    }
    free(object_key);
    qs_release_service(context_hdl);
}

THEN ("^options object status code is (\\d+)$")
{
    REGEX_PARAM (int, expected);
    ScenarioScope<qs_options_object_output_t> contextOutput;
    release_options_object_output (& (*contextOutput));
    EXPECT_EQ (expected, (int)contextOutput->response_code);
}

//# DELETE Object
//When delete object with key "<key>"
//Then delete object status code is 204
//When delete the move object with key "<key>"
//Then delete the move object status code is 204
WHEN ("^delete object with key \"(.{1,})\"$")
{
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    REGEX_PARAM (std::string, objectkey);
    qs_delete_object_input_t input;
    ScenarioScope<qs_delete_object_output_t> contextOutput;
    init_delete_object_input (&input);
    char * object_key = (char *)malloc(objectkey.length() + 1);
    memset(object_key,0,objectkey.length() + 1);
    strncpy(object_key, objectkey.c_str() , objectkey.length());
    QsError err = qs_delete_object (object_key, &input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
        // print sth
    }
    free(object_key);
    qs_release_service(context_hdl);
}

THEN ("^delete object status code is (\\d+)$")
{
    REGEX_PARAM (int, expected);
    ScenarioScope<qs_delete_object_output_t> contextOutput;
    release_delete_object_output (& (*contextOutput));
    EXPECT_EQ (expected, (int)contextOutput->response_code);
}

WHEN ("delete the move object with key \"(.{1,})\"$")
{
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    REGEX_PARAM (std::string, objectkey);
    std::string objectkeyToDel = objectkey + "_move";
    qs_delete_object_input_t input;
    ScenarioScope<qs_delete_object_output_t> contextOutput;
    init_delete_object_input (&input);
    char * object_key = (char *)malloc(objectkey.length() + 1);
    memset(object_key,0,objectkey.length() + 1);
    strncpy(object_key, objectkey.c_str() , objectkey.length());
    QsError err = qs_delete_object (object_key, &input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
        // print sth
    }
    free(object_key);
    qs_release_service(context_hdl);
}

THEN ("^delete the move object status code is (\\d+)$")
{
    REGEX_PARAM (int, expected);
    ScenarioScope<qs_delete_object_output_t> contextOutput;
    release_delete_object_output (& (*contextOutput));
    EXPECT_EQ (expected, (int)contextOutput->response_code);
}
