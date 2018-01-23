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
WHEN ("^put bucket external mirror:$")
{
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    qs_put_bucket_external_mirror_input_t input;
    ScenarioScope<qs_put_bucket_external_mirror_output_t> contextOutput;
    init_put_bucket_external_mirror_input (&input);
    input.source_site = (char *)"https://example.com/something/";
    QsError err = qs_put_bucket_external_mirror (&input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
    }
    qs_release_service(context_hdl);
}

THEN ("^put bucket external mirror status code is (\\d+)$")
{
    REGEX_PARAM (double, expected);
    ScenarioScope<qs_put_bucket_external_mirror_output_t> contextOutput;
    release_put_bucket_external_mirror_output (& (*contextOutput));
    EXPECT_EQ (expected, (int)contextOutput->response_code);
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
WHEN ("^get bucket external mirror$")
{
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    qs_get_bucket_external_mirror_input_t input;
    ScenarioScope<qs_get_bucket_external_mirror_output_t> contextOutput;
    init_get_bucket_external_mirror_input (&input);
    QsError err = qs_get_bucket_external_mirror (&input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
    }
    qs_release_service(context_hdl);
}

THEN ("^get bucket external mirror status code is (\\d+)$")
{
    REGEX_PARAM (double, expected);
    ScenarioScope<qs_get_bucket_external_mirror_output_t> contextOutput;
    EXPECT_EQ (expected, (int)contextOutput->response_code);
}

THEN ("^get bucket external mirror should have source_site \"([^\"]*)\"$")
{
    REGEX_PARAM (std::string, expected);
    ScenarioScope<qs_get_bucket_external_mirror_output_t> contextOutput;
    std::string sourceSite = (char *)"";
    if (contextOutput->source_site)
    {
        sourceSite = contextOutput->source_site;
    }
    release_get_bucket_external_mirror_output (& (*contextOutput));
    EXPECT_EQ (expected, sourceSite);
}

///////////////////////////////////////////////
/////   # DELETE Bucket External Mirror   /////
///////////////////////////////////////////////
/*
Scenario : delete external mirror of the bucket
	When delete bucket external mirror
	Then delete bucket external mirror status code is 204
*/
WHEN ("^delete bucket external mirror$")
{
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    qs_delete_bucket_external_mirror_input_t input;
    ScenarioScope<qs_delete_bucket_external_mirror_output_t> contextOutput;
    init_delete_bucket_external_mirror_input (&input);
    QsError err = qs_delete_bucket_external_mirror (&input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
    }
    qs_release_service(context_hdl);
}

THEN ("^delete bucket external mirror status code is (\\d+)$")
{
    REGEX_PARAM (double, expected);
    ScenarioScope<qs_delete_bucket_external_mirror_output_t> contextOutput;
    release_delete_bucket_cors_output (& (*contextOutput));
    EXPECT_EQ (expected, (int)contextOutput->response_code);
}