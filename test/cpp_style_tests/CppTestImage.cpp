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

    QsError err = QS_ERR_NO_ERROR; 
    ScenarioScope<TestObjectCtx> contextObjectTest;
    contextObjectTest->bucketName = strBucketName;
    QingStor::QsConfig qsConfig;
    qsConfig.LoadConfigFile(strConfigPath);
    contextObjectTest->pQsBucket = new Bucket(qsConfig, strBucketName, strZone);

    // read jpg file as input content
    char dir[PATH_MAX] = {0};
	int n = readlink("/proc/self/exe", dir, PATH_MAX);
    std::string filename = std::string(dir) + "../features/fixtures/" + objectkey;


    std::iostream * objectStream = new std::fstream(filename.c_str(), std::ios::binary | std::ios::in);
    objectStream->seekg(0, objectStream->end);
    size_t streamSize = objectStream->tellg();
    objectStream->seekg(0, objectStream->beg);
 
    // put obj first
    Bucket qsBucket = *contextObjectTest->pQsBucket;
    PutObjectInput putobjInput;
    ScenarioScope<PutObjectOutput> ctxPutObjOutput;
    putobjInput.SetBody(objectStream);
    putobjInput.SetContentLength(streamSize);
    err = qsBucket.PutObject(objectkey, putobjInput, *ctxPutObjOutput);
    if (QS_ERR_NO_ERROR != err)
    {
    }
    if(objectStream)
        delete objectStream;

    ImageProcessInput imageProcessInput;
    ScenarioScope<ImageProcessOutput> ctxImageProcessOutput;
    imageProcessInput.SetAction(query);
    err = qsBucket.ImageProcess(objectkey, imageProcessInput, *ctxImageProcessOutput);
    if (QS_ERR_NO_ERROR != err)
    {
    }
}

THEN("^image process status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<ImageProcessOutput> contextOutput;
    EXPECT_EQ(expected, (int)contextOutput->GetResponseCode());
}