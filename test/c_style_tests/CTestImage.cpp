//Feature: The basic image processing feature

//////////////////////////////
/////  # Image Process  /////
//////////////////////////////
/*
  Scenario Outline: 
    When image process with key "<key>" and query "<query>" 
    Then image process status code is 200 
	
    # The test.jpg is located in the fixtures directory.
    Examples:
      | key | query |
      | test.jpg | info |
      | test.jpg | crop:w_300 |
      | test.jpg | crop:w_300,h_400 |
      | test.jpg | crop:w_300,h_400,g_0 |
      | test.jpg | crop:w_300,h_400,g_1 |
      | test.jpg | crop:w_300,h_400,g_2 |
      | test.jpg | rotate:a_90 |
      | test.jpg | rotate:a_180 | 
      | test.jpg | rotate:a_270 | 
      | test.jpg | resize:w_500,h_500 |
      | test.jpg | resize:w_500,h_500,m_2 |
      | test.jpg | watermark:t_5rC05Y2w5paH5a2X,p_0.5 |
      | test.jpg | watermark:t_5rC05Y2w5paH5a2X,p_0.5,d_150 |
      | test.jpg | watermark_image:u_aHR0cHM6Ly9wZWszYS5xaW5nc3Rvci5jb20vaW1nLWRvYy1lZy9xaW5jbG91ZC5wbmc,l_10,t_10,p_2 |
      | test.jpg | format:t_jpeg |
      | test.jpg | format:t_png |
      | test.jpg | format:t_webp |
      | test.jpg | format:t_tiff |
      | test.jpg | crop:w_300\|rotate:a_90\|resize:h_200\|watermark:t_5rC05Y2w5paH5a2X,p_0.5,d_150\|format:t_png |
      | test.jpg | crop:w_300\|rotate:a_90\|resize:h_200\|watermark:t_5rC05Y2w5paH5a2X,p_0.5,d_150\|format:t_png\|info |
*/
WHEN("^image process with key \"([^\"]*)\" and query \"([^\"]*)\"$")
{

    REGEX_PARAM(std::string, objectkey);
    REGEX_PARAM(std::string, query);

    QsError err;
    init_test_config();

    ScenarioScope<TestObjectCtx> contextObjectTest;
    contextObjectTest->bucketName = strBucketName;
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    qs_put_object_input_t input;
    ScenarioScope<qs_put_object_output_t> contextOutput;
    init_put_object_input (&input);
    
    // read jpg file as input content
    char dir[PATH_MAX] = {0};
	int n = readlink("/proc/self/exe", dir, PATH_MAX);
    std::string filename = std::string(dir) + "../features/fixtures/" + objectkey;
    std::ifstream  in(filename.c_str(),std::ios::binary | std::ios::in);
    size_t streamSize = in.tellg();
    long length = (long)streamSize;
    in.seekg(0, in.beg);
    input.bodybuf = malloc (length + 1);
    memset(input.bodybuf,0,length +1 );
    in.read((char *)input.bodybuf, streamSize); 
    input.content_length = &length;
    input.bufLength = &length;

    // put obj first
    char * object_key = (char *)malloc(objectkey.length() + 1);
    memset(object_key,0,objectkey.length() +1 );
    strncpy(object_key, objectkey.c_str() , objectkey.length());
    err = qs_put_object (object_key, &input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
    }
    if(input.bodybuf && input.bufLength)
    {
        free(input.bodybuf);
    }

    qs_image_process_input_t imageProcessInput;
    ScenarioScope<qs_image_process_output_t> ctxImageProcessOutput;
    init_image_process_input(&imageProcessInput);

    imageProcessInput.action = (char *)malloc(query.length() + 1);
    memset(imageProcessInput.action,0,query.length() +1 );
    strncpy(imageProcessInput.action, query.c_str() , query.length());
    
    err = qs_image_process(object_key, &imageProcessInput,  & (*ctxImageProcessOutput) , context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
    }

    free(object_key);
    qs_release_service(context_hdl);
}

THEN("^image process status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<qs_image_process_output_t> ctxImageProcessOutput;
    EXPECT_EQ(expected, ctxImageProcessOutput->response_code);
}