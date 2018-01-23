////  Feature: the bucket policy feature

//////////////////////////////////
/////  # PUT Bucket policy   /////
//////////////////////////////////
/*
Scenario : set the bucket policy
		# Notice : Please set statement resource manually
		When put bucket policy :
		 """
		 {
			 "statement": [
			 {
				 "id": "allow certain site to get objects",
					 "user" : [
						 "*"
					 ],
					 "action" : [
						 "get_object"
					 ],
					 "effect" : "allow",
					 "resource" : [],
					 "condition" : {
							 "string_like": {
								 "Referer": [
									 "*.example1.com",
										 "*.example2.com"
								 ]
							 },
							 "ip_address": {
										 "source_ip": [
											 "172.16.0.0/24",
												 "172.16.1.1/32"
										 ]
									 }
						 }
			 }
			 ]
		 }
		 """
		Then put bucket policy status code is 200
*/
WHEN ("^put bucket policy:$")
{
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    ScenarioScope<qs_put_bucket_policy_output_t> contextOutput;
    qs_put_bucket_policy_input_t input;
    init_put_bucket_policy_input (&input);
    qs_list_t statement_list;
    qs_statement_item_t statement_item;
    qs_statement_t statement;
    init_statement (&statement);
    qs_list_t userlist;
    qs_list_t actionlist;
    qs_condition_t condition;
    init_condition (&condition);
    // user
    qs_list_init (&userlist);
    qs_string_item_t user_item;
    user_item.content = (char *)"*";
    qs_list_append (&user_item.node, &userlist);
    // action
    qs_list_init (&actionlist);
    qs_string_item_t action_item;
    action_item.content = (char *)"list_objects"; //"get_object";
    qs_list_append (&action_item.node, &actionlist);
    /*
    // resource
    qs_list_t resource_list;
    qs_list_init(&resource_list);
    qs_string_item_t user_item;
    user_item.content = (char *)"*";
    qs_list_append(&user_item.node, &userlist);
    */
    // condition
    qs_string_like_t string_like;
    qs_list_t referer_list;
    qs_list_init (&referer_list);
    qs_string_item_t referer_item_1, referer_item_2;
    referer_item_1.content = (char *)"*.example1.com";
    referer_item_2.content = (char *)"*.example2.com";
    qs_list_append (&referer_item_1.node, &referer_list);
    qs_list_append (&referer_item_2.node, &referer_list);
    string_like.referer = &referer_list;
    /////////////////
    qs_ip_address_t ip_address;
    qs_list_t source_ip_list;
    qs_list_init (&source_ip_list);
    qs_string_item_t source_ip_item_1, source_ip_item_2;
    source_ip_item_1.content = (char *)"172.16.0.0/24";
    source_ip_item_2.content = (char *)"172.16.1.1/32";
    qs_list_append (&source_ip_item_1.node, &source_ip_list);
    qs_list_append (&source_ip_item_2.node, &source_ip_list);
    ip_address.source_ip = &source_ip_list;
    condition.string_like = &string_like;
    condition.ip_address = &ip_address;
    // statement
    statement.id = (char *)"allow certain site to get objects";
    statement.user = &userlist;
    statement.effect = (char *)"allow";
    statement.action = &actionlist;
    statement.condition = &condition;
    // call api
    qs_list_init (&statement_list);
    statement_item.content = &statement;
    qs_list_append (&statement_item.node, &statement_list);
    input.statement = &statement_list;
    QsError err = qs_put_bucket_policy (&input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
    }
    qs_release_service(context_hdl);
}

THEN ("^put bucket policy status code is (\\d+)$")
{
    REGEX_PARAM (double, expected);
    ScenarioScope<qs_put_bucket_policy_output_t> contextOutput;
    release_put_bucket_policy_output (& (*contextOutput));
    EXPECT_EQ (expected, (int)contextOutput->response_code);
}

//////////////////////////////////
/////  # GET Bucket policy   /////
//////////////////////////////////
/*
Scenario : get policy of the bucket
		When get bucket policy
		Then get bucket policy status code is 200
		And get bucket policy should have Referer "*.example1.com"
*/
WHEN ("^get bucket policy$")
{
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    qs_get_bucket_policy_input_t input;
    ScenarioScope<qs_get_bucket_policy_output_t> contextOutput;
    init_get_bucket_policy_input (&input);
    QsError err = qs_get_bucket_policy (&input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
    }
    qs_release_service(context_hdl);
}

THEN ("^get bucket policy status code is (\\d+)$")
{
    REGEX_PARAM (double, expected);
    ScenarioScope<qs_get_bucket_policy_output_t> contextOutput;
    EXPECT_EQ (expected, (int)contextOutput->response_code);
}

THEN ("^get bucket policy should have Referer \"([^\"]*)\"$")
{
    REGEX_PARAM (std::string, expected);
    ScenarioScope<qs_get_bucket_policy_output_t> contextOutput;
    char *referer = (char *)"";
    if (!qs_is_list_empty (contextOutput->statement))
    {
        qs_statement_item_t *statement_item = qs_list_get_first (contextOutput->statement, qs_statement_item_t);
        if (statement_item->content->condition && statement_item->content->condition->string_like && !qs_is_list_empty (statement_item->content->condition->string_like->referer))
        {
            qs_string_like_referer_item_t *referer_item = qs_list_get_first (statement_item->content->condition->string_like->referer, qs_string_like_referer_item_t);
            if (referer_item)
            {
                referer = referer_item->content;
            }
        }
    }
    std::string ref = referer;
    release_get_bucket_policy_output (& (*contextOutput));
    EXPECT_EQ (expected.c_str(), ref);
}

////////////////////////////////////
/////  # DELETE Bucket policy  /////
////////////////////////////////////
/*
Scenario : delete policy of the bucket
	When delete bucket policy
	Then delete bucket policy status code is 204
*/
WHEN ("^delete bucket policy$")
{
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    qs_delete_bucket_policy_input_t input;
    ScenarioScope<qs_delete_bucket_policy_output_t> contextOutput;
    init_delete_bucket_policy_input (&input);
    QsError err = qs_delete_bucket_policy (&input, & (*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
    }
    qs_release_service(context_hdl);
}

THEN ("^delete bucket policy status code is (\\d+)$")
{
    REGEX_PARAM (int, expected);
    ScenarioScope<qs_delete_bucket_policy_output_t> contextOutput;
    release_delete_bucket_policy_output (& (*contextOutput));
    EXPECT_EQ (expected, (int)contextOutput->response_code);
}
