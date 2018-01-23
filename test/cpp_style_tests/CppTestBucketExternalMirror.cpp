
///// Feature: the bucket external mirror feature

////////////////////////////////////////////
/////    # PUT Bucket External Mirror  /////
////////////////////////////////////////////
/*
Scenario : set the bucket external mirror
		When put bucket external mirror :
		"""
		{
			"source_site": "https://example.com/something/"
		}
		"""
		Then put bucket external mirror status code is 200
*/
WHEN("^put bucket external mirror:$")
{
    QingStor::QsConfig qsConfig;
    qsConfig.LoadConfigFile(strConfigPath.c_str());
    QingStorService qsService(qsConfig);
    Bucket qsBucket = Bucket(qsConfig, strBucketName, strZone);
    PutBucketExternalMirrorInput input;
    ScenarioScope<PutBucketExternalMirrorOutput> contextOutput;
    input.SetSourceSite("https://example.com/something/");
    QsError err = qsBucket.PutBucketExternalMirror(input, *contextOutput);
    if (QS_ERR_NO_ERROR != err)
    {
    }
}

THEN("^put bucket external mirror status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<PutBucketExternalMirrorOutput> contextOutput;
    EXPECT_EQ(expected, (int)contextOutput->GetResponseCode());
}

////////////////////////////////////////////
/////   # GET Bucket External Mirror   /////
////////////////////////////////////////////
/*
Scenario : get external mirror of the bucket
	When get bucket external mirror
	Then get bucket external mirror status code is 200
	And get bucket external mirror should have source_site "https://example.com/something/"
*/
WHEN("^get bucket external mirror$")
{
    QingStor::QsConfig qsConfig;
    qsConfig.LoadConfigFile(strConfigPath.c_str());
    QingStorService qsService(qsConfig);
    Bucket qsBucket = Bucket(qsConfig, strBucketName, strZone);
    GetBucketExternalMirrorInput input;
    ScenarioScope<GetBucketExternalMirrorOutput> contextOutput;
    QsError err = qsBucket.GetBucketExternalMirror(input, *contextOutput);
    if (QS_ERR_NO_ERROR != err)
    {
    }
}

THEN("^get bucket external mirror status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<GetBucketExternalMirrorOutput> contextOutput;
    EXPECT_EQ(expected, (int)contextOutput->GetResponseCode());
}

THEN("^get bucket external mirror should have source_site \"([^\"]*)\"$")
{
    REGEX_PARAM(std::string, expected);
    ScenarioScope<GetBucketExternalMirrorOutput> contextOutput;
    EXPECT_EQ(expected, contextOutput->GetSourceSite());
}

///////////////////////////////////////////////
/////   # DELETE Bucket External Mirror   /////
///////////////////////////////////////////////
/*
Scenario : delete external mirror of the bucket
	When delete bucket external mirror
	Then delete bucket external mirror status code is 204
*/
WHEN("^delete bucket external mirror$")
{
    QingStor::QsConfig qsConfig;
    qsConfig.LoadConfigFile(strConfigPath.c_str());
    QingStorService qsService(qsConfig);
    Bucket qsBucket = Bucket(qsConfig, strBucketName, strZone);
    DeleteBucketExternalMirrorInput input;
    ScenarioScope<DeleteBucketExternalMirrorOutput> contextOutput;
    QsError err = qsBucket.DeleteBucketExternalMirror(input, *contextOutput);
    if (QS_ERR_NO_ERROR != err)
    {
    }
}

THEN("^delete bucket external mirror status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<DeleteBucketExternalMirrorOutput> contextOutput;
    EXPECT_EQ(expected, (int)contextOutput->GetResponseCode());
}