#include <stdlib.h>
#include <gtest/gtest.h>
#include "qingstor/QsList.h"
#include <cucumber-cpp/autodetect.hpp>
#include "qingstor/service_with_c_style/QingStorCStyle.h"
#include <memory>
#include <string>

using cucumber::ScenarioScope;

struct TestBucketCtx
{
    void *pQsService;
    void *pQsBucket;
};
struct TestObjectCtx
{
    void *pQsService;
    void *pQsBucket;
    std::string bucketName;
};

struct TestListMultipartUploadsCtx
{
    void *pQsService;
    void *pQsBucket;
    std::string bucketName;
    std::string objectKey;
    std::string uploadID;
};


static char* strConfigPath;

static char* strBucketName;

static char* strZone;

// read necessary information from environment variables.
void init_test_config(void)
{
    // Get QingStor config file path.
    strConfigPath = getenv("QINGSTOR_CONFIG_PATH");
    // Get QingStor bucket name.
    strBucketName = getenv("QINGSTOR_BUCKET_NAME");
    // Get QingStor zone name.
    strZone = getenv("QINGSTOR_ZONE_NAME");
    if(!strConfigPath || !strBucketName || !strZone)
    {
        printf("Envionment variables are missing : QINGSTOR_CONFIG_PATH or QINGSTOR_BUCKET_NAME or QINGSTOR_ZONE_NAME.\n");
        return;
    }
    printf("QINGSTOR_CONFIG_PATH: %s.\n",strConfigPath);
    printf("QINGSTOR_BUCKET_NAME: %s.\n",strBucketName);
    printf("QINGSTOR_ZONE_NAME: %s.\n",strZone);

    qs_init_sdk("/tmp/", Debug, true);
}

/*
Scenario: need to use QingStor service
When initialize QingStor service
Then the QingStor service is initialized
*/
WHEN("^initialize QingStor service$")
{
    init_test_config();
}

THEN("^the QingStor service is initialized$")
{
    EXPECT_EQ(NULL, NULL);
}

/*
# GET Service(List Buckets)
Scenario: list all buckets
	When list buckets
	Then list buckets status code is 200
*/
WHEN("^list buckets$")
{
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    ScenarioScope<qs_list_buckets_output_t> contextOutput;
    qs_list_buckets_input_t input;
    init_list_buckets_input(&input);
    QsError err = qs_list_buckets(&input, &(*contextOutput), context_hdl);
    if (QS_ERR_NO_ERROR != err)
    {
        // print sth
    }
    qs_release_service(context_hdl);
}

THEN("^list buckets status code is (\\d+)$")
{
    REGEX_PARAM(double, expected);
    ScenarioScope<qs_list_buckets_output_t> contextOutput;
    release_list_buckets_output(&(*contextOutput));
    EXPECT_EQ(expected, (int)contextOutput->response_code);
}
