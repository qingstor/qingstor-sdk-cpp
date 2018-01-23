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
    QingStor::QsConfig qsConfig;
    qsConfig.LoadConfigFile(strConfigPath.c_str());
    QingStorService qsService(qsConfig);
    Bucket qsBucket = Bucket(qsConfig, strBucketName, strZone);
    PutBucketACLInput input;
    ScenarioScope<PutBucketACLOutput> contextOutput;
    std::vector<ACLType> aclList;
    ACLType acl;
    GranteeType grantee;
    //grantee.SetID("1");
    grantee.SetType("group");
    grantee.SetName("QS_ALL_USERS");
    acl.SetGrantee(grantee);
    acl.SetPermission("FULL_CONTROL");
    aclList.push_back(acl);
    input.SetACL(aclList);
    QsError err = qsBucket.PutBucketACL(input, *contextOutput);
    if (QS_ERR_NO_ERROR != err)
    {
    }
}

THEN("^put bucket ACL status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<PutBucketACLOutput> contextOutput;
    EXPECT_EQ(expected, (int)contextOutput->GetResponseCode());
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
    QingStor::QsConfig qsConfig;
    qsConfig.LoadConfigFile(strConfigPath.c_str());
    QingStorService qsService(qsConfig);
    Bucket qsBucket = Bucket(qsConfig, strBucketName, strZone);
    GetBucketACLInput input;
    ScenarioScope<GetBucketACLOutput> contextOutput;
    QsError err = qsBucket.GetBucketACL(input, *contextOutput);
    if (QS_ERR_NO_ERROR != err)
    {
    }
}

THEN("^get bucket ACL status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<GetBucketACLOutput> contextOutput;
    EXPECT_EQ(expected, (int)contextOutput->GetResponseCode());
}

THEN("^get bucket ACL should have grantee name \"([^\"]*)\"$")
{
    REGEX_PARAM(std::string, expected);
    ScenarioScope<GetBucketACLOutput> contextOutput;
    std::string granteeName = "";
    if (contextOutput->GetACL().size())
    {
        granteeName = contextOutput->GetACL().at(1).GetGrantee().GetName();
    }
    EXPECT_EQ(expected, granteeName);
}
