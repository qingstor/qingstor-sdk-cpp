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
WHEN("^put bucket policy:$")
{
    QingStor::QsConfig qsConfig;
    qsConfig.LoadConfigFile(strConfigPath.c_str());
    QingStorService qsService(qsConfig);
    Bucket qsBucket = Bucket(qsConfig, strBucketName, strZone);
    PutBucketPolicyInput input;
    ScenarioScope<PutBucketPolicyOutput> contextOutput;
    std::vector < StatementType > statementVec;
    StatementType statement;
    // set ID
    statement.SetID("allow certain site to get objects");
    // set user
    std::vector < std::string > userVec;
    userVec.push_back("*");
    statement.SetUser(userVec);
    // set action
    std::vector < std::string > actionVec;
    actionVec.push_back("get_object");
    statement.SetAction(actionVec);
    // set effect
    statement.SetEffect("allow");
    // set resource
    std::string resource = strBucketName + "/*";
    std::vector < std::string > resourceVec;
    resourceVec.push_back(resource);
    statement.SetResource(resourceVec);
    // set condition
    ConditionType condition;
    // set condition stringlike
    StringLikeType stringLike;
    std::vector < std::string > referer;
    referer.push_back("*.example1.com");
    referer.push_back("*.example2.com");
    stringLike.SetReferer(referer);
    condition.SetStringLike(stringLike);
    //set condition ip_address
    std::vector < std::string > sourceIPVec;
    sourceIPVec.push_back("172.16.0.0/24");
    sourceIPVec.push_back("172.16.1.1/32");
    IPAddressType ipAddress;
    ipAddress.SetSourceIP(sourceIPVec);
    condition.SetIPAddress(ipAddress);
    statement.SetCondition(condition);
    statementVec.push_back(statement);
    input.SetStatement(statementVec);
    QsError err = qsBucket.PutBucketPolicy(input, *contextOutput);
    if (QS_ERR_NO_ERROR != err)
    {
    }
}

THEN("^put bucket policy status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<PutBucketACLOutput> contextOutput;
    EXPECT_EQ(expected, (int)contextOutput->GetResponseCode());
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
WHEN("^get bucket policy$")
{
    QingStor::QsConfig qsConfig;
    qsConfig.LoadConfigFile(strConfigPath.c_str());
    QingStorService qsService(qsConfig);
    Bucket qsBucket = Bucket(qsConfig, strBucketName, strZone);
    GetBucketPolicyInput input;
    ScenarioScope<GetBucketPolicyOutput> contextOutput;
    QsError err = qsBucket.GetBucketPolicy(input, *contextOutput);
    if (QS_ERR_NO_ERROR != err)
    {
    }
}

THEN("^get bucket policy status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<GetBucketPolicyOutput> contextOutput;
    EXPECT_EQ(expected, (int)contextOutput->GetResponseCode());
}

THEN("^get bucket policy should have Referer \"([^\"]*)\"$")
{
    REGEX_PARAM(std::string, expected);
    ScenarioScope<GetBucketPolicyOutput> contextOutput;
    ConditionType condition;
    StringLikeType striinglike;
    std::vector<std::string> refererList;
    std::string referer = "";
    std::vector<StatementType> statementList = contextOutput->GetStatement();
    if (statementList.size())
    {
        StatementType statement = statementList.at(0);
        condition = statement.GetCondition();
        striinglike = condition.GetStringLike();
        refererList = striinglike.GetReferer();
        if (refererList.size())
        {
            referer = refererList.at(0);
        }
    }
    EXPECT_EQ(expected, referer);
}

//////////////////////////////////
/////  # DELETE Bucket policy  /////
//////////////////////////////////
/*
Scenario : delete policy of the bucket
	When delete bucket policy
	Then delete bucket policy status code is 204
*/
WHEN("^delete bucket policy$")
{
    QingStor::QsConfig qsConfig;
    qsConfig.LoadConfigFile(strConfigPath);
    QingStorService qsService(qsConfig);
    Bucket qsBucket = Bucket(qsConfig, strBucketName, strZone);
    DeleteBucketPolicyInput input;
    ScenarioScope<DeleteBucketPolicyOutput> contextOutput;
    QsError err = qsBucket.DeleteBucketPolicy(input, *contextOutput);
    if (QS_ERR_NO_ERROR != err)
    {
    }
}

THEN("^delete bucket policy status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<DeleteBucketCORSOutput> contextOutput;
    EXPECT_EQ(expected, (int)contextOutput->GetResponseCode());
}