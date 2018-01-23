//////////Feature: the bucket CORS feature

///////////////////////////////
/////  # PUT Bucket CORS  /////
///////////////////////////////
//Scenario : set the bucket CORS
//		 When put bucket CORS :
//		 """
//		 {
//			 "cors_rules": [
//			 {
//				 "allowed_origin": "http://*.qingcloud.com",
//					 "allowed_methods" : [
//						 "PUT",
//							 "GET",
//							 "DELETE",
//							 "POST"
//					 ],
//					 "allowed_headers": [
//						 "X-QS-Date",
//							 "Content-Type",
//							 "Content-MD5",
//							 "Authorization"
//					 ],
//					 "max_age_seconds": 200,
//					 "expose_headers" : [
//						 "X-QS-Date"
//					 ]
//			 },
//			 {
//				 "allowed_origin": "http://*.example.com",
//				 "allowed_methods" : [
//					 "PUT",
//						 "GET",
//						 "DELETE",
//						 "POST"
//				 ],
//				 "allowed_headers": [
//					 "*"
//				 ],
//				 "max_age_seconds" : 400
//			 }
//			 ]
//		 }
//		 """
//		Then put bucket CORS status code is 200
WHEN("^put bucket CORS:$")
{
    QingStor::QsConfig qsConfig;
    qsConfig.LoadConfigFile(strConfigPath);
    QingStorService qsService(qsConfig);
    Bucket qsBucket = Bucket(qsConfig, strBucketName, strZone);
    PutBucketCORSInput input;
    ScenarioScope<PutBucketCORSOutput> contextOutput;
    std::vector<CORSRuleType> rules;
    CORSRuleType rule1;
    CORSRuleType rule2;
    std::vector<std::string> allowedMethods;
    allowedMethods.push_back("PUT");
    allowedMethods.push_back("GET");
    allowedMethods.push_back("DELETE");
    allowedMethods.push_back("POST");
    std::vector<std::string> allowedHeaders;
    allowedHeaders.push_back("X-QS-Date");
    allowedHeaders.push_back("Content-Type");
    allowedHeaders.push_back("Content-MD5");
    allowedHeaders.push_back("Authorization");
    std::vector<std::string> allowedAllHeaders;
    allowedAllHeaders.push_back("*");
    std::vector<std::string> exposeHeaders;
    exposeHeaders.push_back("X-QS-Date");
    rule1.SetAllowedOrigin("http://*.qingcloud.com");
    rule1.SetAllowedMethods(allowedMethods);
    rule1.SetExposeHeaders(exposeHeaders);
    rule1.SetAllowedHeaders(allowedHeaders);
    rule1.SetMaxAgeSeconds(200);
    rule2.SetAllowedOrigin("http://*.example.com");
    rule2.SetAllowedMethods(allowedMethods);
    rule2.SetAllowedHeaders(allowedAllHeaders);
    rule2.SetMaxAgeSeconds(400);
    rules.push_back(rule1);
    rules.push_back(rule2);
    input.SetCORSRules(rules);
    QsError err = qsBucket.PutBucketCORS(input, *contextOutput);
    if (QS_ERR_NO_ERROR != err)
    {
    }
}

THEN("^put bucket CORS status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<PutBucketCORSOutput> contextOutput;
    EXPECT_EQ(expected, (int)contextOutput->GetResponseCode());
}

///////////////////////////////
/////  # GET Bucket CORS  /////
///////////////////////////////
/*
Scenario : get CORS of the bucket
	When get bucket CORS
	Then get bucket CORS status code is 200
	And get bucket CORS should have allowed origin "http://*.qingcloud.com"
*/
WHEN("^get bucket CORS$")
{
    QingStor::QsConfig qsConfig;
    qsConfig.LoadConfigFile(strConfigPath);
    QingStorService qsService(qsConfig);
    Bucket qsBucket = Bucket(qsConfig, strBucketName, strZone);
    GetBucketCORSInput input;
    ScenarioScope<GetBucketCORSOutput> contextOutput;
    QsError err = qsBucket.GetBucketCORS(input, *contextOutput);
    if (QS_ERR_NO_ERROR != err)
    {
    }
}

THEN("^get bucket CORS status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<GetBucketCORSOutput> contextOutput;
    EXPECT_EQ(expected, (int)contextOutput->GetResponseCode());
}

THEN("^get bucket CORS should have allowed origin \"([^\"]*)\"$")
{
    REGEX_PARAM(std::string, expected);
    ScenarioScope<GetBucketCORSOutput> contextOutput;
    std::string allowedOrigin = "";
    if (contextOutput->GetCORSRules().size())
    {
        CORSRuleType corsRule = contextOutput->GetCORSRules().at(0);
        allowedOrigin = corsRule.GetAllowedOrigin();
    }
    EXPECT_EQ(expected, allowedOrigin);
}

//////////////////////////////////
/////  # DELETE Bucket CORS  /////
//////////////////////////////////
/*
Scenario : delete CORS of the bucket
	When delete bucket CORS
	Then delete bucket CORS status code is 204
*/
WHEN("^delete bucket CORS$")
{
    QingStor::QsConfig qsConfig;
    qsConfig.LoadConfigFile(strConfigPath);
    QingStorService qsService(qsConfig);
    Bucket qsBucket = Bucket(qsConfig, strBucketName, strZone);
    DeleteBucketCORSInput input;
    ScenarioScope<DeleteBucketCORSOutput> contextOutput;
    QsError err = qsBucket.DeleteBucketCORS(input, *contextOutput);
    if (QS_ERR_NO_ERROR != err)
    {
    }
}

THEN("^delete bucket CORS status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<DeleteBucketCORSOutput> contextOutput;
    EXPECT_EQ(expected, (int)contextOutput->GetResponseCode());
}