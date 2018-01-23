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
WHEN ("^put bucket CORS:$")
{
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    ScenarioScope<qs_put_bucket_cors_output_t> contextOutput;
    qs_put_bucket_cors_input_t input;
    init_put_bucket_cors_input (&input);
    qs_cors_rule_item_t rules_item1, rules_item2;
    //qs_cors_rule_t rule1,rule2;
    qs_cors_rule_t content1, content2;
    init_cors_rule (&content1);
    init_cors_rule (&content2);
    qs_list_t allowed_headers_1;
    qs_list_t allowed_headers_2;
    qs_list_t expose_headers_1;
    qs_list_t expose_headers_2;
    qs_list_t allowed_methods_1;
    qs_list_t allowed_methods_2;
    qs_list_init (&allowed_headers_1);
    qs_list_init (&allowed_headers_2);
    qs_list_init (&expose_headers_1);
    qs_list_init (&expose_headers_2);
    qs_list_init (&allowed_methods_1);
    qs_list_init (&allowed_methods_2);
    content1.allowed_headers = &allowed_headers_1;
    content1.expose_headers = &expose_headers_1;
    content1.allowed_methods = &allowed_methods_1;
    content2.allowed_headers = &allowed_headers_2;
    content2.expose_headers = &expose_headers_2;
    content2.allowed_methods = &allowed_methods_2;
    rules_item1.content = &content1;
    rules_item2.content = &content2;
    qs_cors_rule_allowed_methods_item_t allowed_method_item1[4];
    allowed_method_item1[0].content = (char *)"PUT";
    allowed_method_item1[1].content = (char *)"GET";
    allowed_method_item1[2].content = (char *)"DELETE";
    allowed_method_item1[3].content = (char *)"POST";
    qs_cors_rule_allowed_methods_item_t allowed_method_item2[4];
    allowed_method_item2[0].content = (char *)"PUT";
    allowed_method_item2[1].content = (char *)"GET";
    allowed_method_item2[2].content = (char *)"DELETE";
    allowed_method_item2[3].content = (char *)"POST";
    qs_cors_rule_allowed_headers_item_t allowed_headers_item1;
    allowed_headers_item1.content = (char *)"*";
    qs_cors_rule_allowed_headers_item_t allowed_headers_item2;
    allowed_headers_item2.content = (char *)"*";
    qs_cors_rule_expose_headers_item_t expose_headers_item1;
    expose_headers_item1.content = (char *)"X-QS-Date";
    qs_cors_rule_expose_headers_item_t expose_headers_item2;
    expose_headers_item2.content = (char *)"X-QS-Date";
    qs_list_init (rules_item1.content->allowed_methods);
    qs_list_append (&allowed_method_item1[0].node, rules_item1.content->allowed_methods);
    qs_list_append (&allowed_method_item1[1].node, rules_item1.content->allowed_methods);
    qs_list_append (&allowed_method_item1[2].node, rules_item1.content->allowed_methods);
    qs_list_append (&allowed_method_item1[3].node, rules_item1.content->allowed_methods);
    qs_list_append (&allowed_headers_item1.node, rules_item1.content->allowed_headers);
    qs_list_append (&expose_headers_item1.node, rules_item1.content->expose_headers);
    rules_item1.content->allowed_origin = (char *)"http://*.qingcloud.com";
    int max_age_seconds = 200;
    rules_item1.content->max_age_seconds = &max_age_seconds;
    qs_list_append (&allowed_method_item2[0].node, rules_item2.content->allowed_methods);
    qs_list_append (&allowed_method_item2[1].node, rules_item2.content->allowed_methods);
    qs_list_append (&allowed_method_item2[2].node, rules_item2.content->allowed_methods);
    qs_list_append (&allowed_method_item2[3].node, rules_item2.content->allowed_methods);
    qs_list_append (&allowed_headers_item2.node, rules_item2.content->allowed_headers);
    qs_list_append (&expose_headers_item2.node, rules_item2.content->expose_headers);
    rules_item2.content->allowed_origin = (char *)"http://*.example.com";
    max_age_seconds = 400;
    rules_item2.content->max_age_seconds = &max_age_seconds;
    qs_list_t cors_rules;
    qs_list_init (&cors_rules);
    input.cors_rules = &cors_rules;
    qs_list_append (&rules_item1.node, input.cors_rules);
    qs_list_append (&rules_item2.node, input.cors_rules);
    QsError err = qs_put_bucket_cors (&input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
        // print sth
    }
    qs_release_service(context_hdl);
}

THEN ("^put bucket CORS status code is (\\d+)$")
{
    REGEX_PARAM (double, expected);
    ScenarioScope<qs_put_bucket_cors_output_t> contextOutput;
    release_put_bucket_cors_output (& (*contextOutput));
    EXPECT_EQ (expected, (int)contextOutput->response_code);
}

///////////////////////////////
/////  # GET Bucket CORS  /////
///////////////////////////////
/*
Scenario : get CORS of the bucket
	When get bucket CORS
	Then get bucket CORS status code is 200
	And get bucket CORS should have allowed origin "http://\*.qingcloud.com"
*/
WHEN ("^get bucket CORS$")
{
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    qs_get_bucket_cors_input_t input;
    ScenarioScope<qs_get_bucket_cors_output_t> contextOutput;
    init_get_bucket_cors_input (&input);
    QsError err = qs_get_bucket_cors (&input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
    }
    qs_release_service(context_hdl);
}

THEN ("^get bucket CORS status code is (\\d+)$")
{
    REGEX_PARAM (double, expected);
    ScenarioScope<qs_get_bucket_cors_output_t> contextOutput;
    EXPECT_EQ (expected, (int)contextOutput->response_code);
}

THEN ("^get bucket CORS should have allowed origin \"([^\"]*)\"$")
{
    REGEX_PARAM (std::string, expected);
    ScenarioScope<qs_get_bucket_cors_output_t> contextOutput;
    std::string allowedOrigin;
    int count = 0;
    qs_cors_rule_item_t *pos;
    qs_list_for_each_entry (qs_cors_rule_item_t, pos, contextOutput->cors_rules)
    count++;
    if (count)
    {
        qs_cors_rule_item_t *corsRule = qs_list_get_first (contextOutput->cors_rules, qs_cors_rule_item_t);
        allowedOrigin = corsRule->content->allowed_origin;
    }
    release_get_bucket_cors_output (& (*contextOutput));
    EXPECT_EQ (expected, allowedOrigin);
}

//////////////////////////////////
/////  # DELETE Bucket CORS  /////
//////////////////////////////////
/*
Scenario : delete CORS of the bucket
	When delete bucket CORS
	Then delete bucket CORS status code is 204
*/
WHEN ("^delete bucket CORS$")
{
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    qs_delete_bucket_cors_input_t input;
    ScenarioScope<qs_delete_bucket_cors_output_t> contextOutput;
    init_delete_bucket_cors_input (&input);
    QsError err = qs_delete_bucket_cors (&input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
    }
    qs_release_service(context_hdl);
}

THEN ("^delete bucket CORS status code is (\\d+)$")
{
    REGEX_PARAM (double, expected);
    ScenarioScope<qs_delete_bucket_output_t> contextOutput;
    release_delete_bucket_cors_output (& (*contextOutput));
    EXPECT_EQ (expected, (int)contextOutput->response_code);
}
