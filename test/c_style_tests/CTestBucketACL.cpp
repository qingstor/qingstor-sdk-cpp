//Feature: the bucket ACL feature

//////////////////////////////
/////  # PUT Bucket ACL  /////
//////////////////////////////

//Scenario: set the bucket ACL
//When put bucket ACL:
//		  """
//		  {
//			  "acl": [
//			  {
//				  "grantee": {
//					  "type": "group",
//						  "name" : "QS_ALL_USERS"
//				  },
//				  "permission" : "FULL_CONTROL"
//			  }
//			  ]
//		  }
//		  """
//Then put bucket ACL status code is 200
WHEN("^put bucket ACL:$")
{
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    qs_put_bucket_acl_input_t input;
    ScenarioScope<qs_put_bucket_acl_output_t> contextOutput;
    init_put_bucket_acl_input(&input);
    qs_acl_t acl;
    qs_grantee_t grantee;
    init_acl(&acl);
    init_grantee(&grantee);
    grantee.type = (char *)"group";
    grantee.name = (char *)"QS_ALL_USERS";
    acl.grantee = &grantee;
    acl.permission = (char *)"FULL_CONTROL";
    qs_acl_item_t acl_item;
    acl_item.content = &acl;
    qs_list_t acllist;
    input.acl = &acllist;
    qs_list_init(input.acl);
    qs_list_append(&acl_item.node, input.acl);
    QsError err = qs_put_bucket_acl(&input, &(*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
        // print sth
    }
    qs_release_service(context_hdl);
}

THEN("^put bucket ACL status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<qs_put_bucket_acl_output_t> contextOutput;
    release_put_bucket_acl_output(&(*contextOutput));
    EXPECT_EQ(expected, (int)contextOutput->response_code);
}

//////////////////////////////
/////  # GET Bucket ACL  /////
//////////////////////////////
/*
Scenario : get ACL of the bucket
When get bucket ACL
Then get bucket ACL status code is 200
And get bucket ACL should have grantee name "QS_ALL_USERS"
*/
WHEN("^get bucket ACL$")
{
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    qs_get_bucket_acl_input_t input;
    ScenarioScope<qs_get_bucket_acl_output_t> contextOutput;
    init_get_bucket_acl_input(&input);
    QsError err = qs_get_bucket_acl(&input, &(*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
        // print sth
    }
    qs_release_service(context_hdl);
}

THEN("^get bucket ACL status code is (\\d+)$")
{
    REGEX_PARAM(int, expected);
    ScenarioScope<qs_get_bucket_acl_output_t> contextOutput;
    EXPECT_EQ(expected, (int)contextOutput->response_code);
}

THEN("^get bucket ACL should have grantee name \"([^\"]*)\"$")
{
    REGEX_PARAM(std::string, expected);
    ScenarioScope<qs_get_bucket_acl_output_t> contextOutput;
    std::string granteeName = (char *)"";
    qs_acl_item_t *item;
    qs_list_t acl;
    qs_list_init(&acl);
    qs_list_for_each_entry(qs_acl_item_t, item, contextOutput->acl)
    {
        if (item->content && item->content->grantee && item->content->grantee->name)
        {
            granteeName = item->content->grantee->name;
        }
    }
    release_get_bucket_acl_output(&(*contextOutput));
    EXPECT_EQ(expected, granteeName);
}