// +-------------------------------------------------------------------------
// | Copyright (C) 2016 Yunify, Inc.
// +-------------------------------------------------------------------------
// | Licensed under the Apache License, Version 2.0 (the "License");
// | you may not use this work except in compliance with the License.
// | You may obtain a copy of the License in the LICENSE file, or at:
// |
// | http://www.apache.org/licenses/LICENSE-2.0
// |
// | Unless required by applicable law or agreed to in writing, software
// | distributed under the License is distributed on an "AS IS" BASIS,
// | WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// | See the License for the specific language governing permissions and
// | limitations under the License.
// +-------------------------------------------------------------------------

#include "QingStor.h"
#include "Bucket.h"
#include "QsConfig.h"
#include "service_with_c_style/QingStorCStyle.h"
#include "utils/QsStream.h"
#include "external/plog/Log.h"

using namespace QingStor;

void qs_init_sdk(const char *logfile_path, LogLevel qs_log_level,
                 unsigned int init_and_cleanup_curl)
{
    QingStor::SDKOptions sdkOptions;
    sdkOptions.logLevel = qs_log_level;
    sdkOptions.logPath = logfile_path;
    if (!init_and_cleanup_curl)
    {
        sdkOptions.initAndCleanupCurl = false;
    }
    else
    {
        sdkOptions.initAndCleanupCurl = true;
    }
    QingStor::InitializeSDK(sdkOptions);
}

void qs_shutdown_sdk(unsigned int init_and_cleanup_curl)
{
    QingStor::SDKOptions sdkOptions;
    if (!init_and_cleanup_curl)
    {
        sdkOptions.initAndCleanupCurl = false;
    }
    else
    {
        sdkOptions.initAndCleanupCurl = true;
    }
    QingStor::ShutdownSDK(sdkOptions);
}

qs_context_handle qs_create_service_with_configfile(const char *qs_configfile,
        const char *qs_bucket_name,
        const char *qs_bucket_zone)
{
    qs_context_handle context_hdl;
    QsConfig qsConfig;
    qsConfig.LoadConfigFile(qs_configfile);
    context_hdl.pQsService = new QingStorService(qsConfig);
    context_hdl.pQsBucket =
        new Bucket(qsConfig, qs_bucket_name, qs_bucket_zone);
    return context_hdl;
}

QS_SDK_API qs_context_handle qs_create_service(qs_config_t
        qs_config,
        const char
        *qs_bucket_name,
        const char *qs_bucket_zone)
{
    qs_context_handle context_hdl;
    QsConfig qsConfig;
    if (qs_config.additional_user_agent)
        qsConfig.additionalUserAgent = qs_config.additional_user_agent;
    if (qs_config.access_key_id)
        qsConfig.accessKeyId = qs_config.access_key_id;
    if (qs_config.secret_access_key)
        qsConfig.secretAccessKey = qs_config.secret_access_key;
    if (qs_config.host)
        qsConfig.host = qs_config.host;
    if (qs_config.protocol)
        qsConfig.protocol = qs_config.protocol;
    if (0 < qs_config.port && 65535 > qs_config.port)
    {
        qsConfig.port = qs_config.port;
    }
    if (0 <= qs_config.conn_retries && 10 > qs_config.conn_retries)
    {
        qsConfig.connectionRetries = qs_config.conn_retries;
    }
    if (0 <= qs_config.timeout_period && 100 > qs_config.timeout_period)
    {
        qsConfig.timeOutPeriod = qs_config.timeout_period;
    }
    context_hdl.pQsService = new QingStorService(qsConfig);
    context_hdl.pQsBucket =
        new Bucket(qsConfig, qs_bucket_name, qs_bucket_zone);
    return context_hdl;
}

void qs_release_service(qs_context_handle context_hdl)
{
    if (context_hdl.pQsService)
    {
        QingStorService *pQsService2Delete =
            (QingStorService *) context_hdl.pQsService;
        delete pQsService2Delete;
    }
    if (context_hdl.pQsBucket)
    {
        Bucket *pBucket2Delete = (Bucket *) context_hdl.pQsBucket;
        delete pBucket2Delete;
    }
}

void qs_set_error_info(qs_error_info_t * err_info, ResponseErrorInfo & errInfo)
{
    int codeLength = errInfo.code.length();
    if (codeLength > 0)
    {
        err_info->code = (char *) malloc(codeLength + 1);
        memset(err_info->code, 0, codeLength + 1);
        strncpy(err_info->code, errInfo.code.c_str(), codeLength);
    }
    int messageLength = errInfo.message.length();
    if (messageLength > 0)
    {
        err_info->message = (char *) malloc(messageLength + 1);
        memset(err_info->message, 0, messageLength + 1);
        strncpy(err_info->message, errInfo.message.c_str(), messageLength);
    }
    int requestIDLength = errInfo.requestID.length();
    if (requestIDLength > 0)
    {
        err_info->request_id = (char *) malloc(requestIDLength + 1);
        memset(err_info->request_id, 0, requestIDLength + 1);
        strncpy(err_info->request_id, errInfo.requestID.c_str(),
                requestIDLength);
    }
    int urlLength = errInfo.url.length();
    if (urlLength > 0)
    {
        err_info->url = (char *) malloc(urlLength + 1);
        memset(err_info->url, 0, urlLength + 1);
        strncpy(err_info->url, errInfo.url.c_str(), urlLength);
    }
}

void qs_release_error_info(qs_error_info_t * err_info)
{
    if (!err_info)
    {
        return;
    }
    if (err_info->code)
    {
        free(err_info->code);
    }
    if (err_info->message)
    {
        free(err_info->message);
    }
    if (err_info->request_id)
    {
        free(err_info->request_id);
    }
    if (err_info->url)
    {
        free(err_info->url);
    }
}

void qs_init_error_info(qs_error_info_t * err_info)
{
    err_info->code = NULL;
    err_info->message = NULL;
    err_info->request_id = NULL;
    err_info->url = NULL;
}

// list_bucketsInput init function.
void init_list_buckets_input(qs_list_buckets_input_t * input)
{
    input->location = NULL;
    return;
}

// list_bucketsoutput init function.
void init_list_buckets_output(qs_list_buckets_output_t * output)
{
    output->buckets = NULL;
    output->count = NULL;
    qs_init_error_info(&output->error_info);
    return;
}

// list_buckets Output release function.
void release_list_buckets_output(qs_list_buckets_output_t * output)
{
    if (output->buckets)
    {
        qs_bucket_item_t *item = NULL;
        qs_bucket_item_t *item_to_delete = NULL;
        qs_list_for_each_entry(qs_bucket_item_t, item, output->buckets)
        {
            if (item_to_delete)
            {
                free(item_to_delete);
            }
            item_to_delete = item;
            release_bucket(item->content);
            free(item->content);
        }
        if (item_to_delete)
        {
            free(item_to_delete);
        }
        free(output->buckets);
    }
    if (output->count)
    {
        free(output->count);
    }
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_list_buckets(qs_list_buckets_input_t * input,
                        qs_list_buckets_output_t * output,
                        qs_context_handle context_hdl)
{
    //init class ListBucketsinputCpp
    ListBucketsInput inputCpp;
    ListBucketsOutput outputCpp;
    // packer cpp input
    if (input->location)
    {
        inputCpp.SetLocation(input->location);
    }
    // init output
    init_list_buckets_output(output);
    // call cpp op
    QingStorService *qsService = (QingStorService *) (context_hdl.pQsService);
    QsError err = qsService->ListBuckets(inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        output->buckets = (qs_list_t *) malloc(sizeof(qs_list_t));
        qs_list_init(output->buckets);
        std::vector < BucketType > buckets = outputCpp.GetBuckets();
        for (std::vector < BucketType >::iterator it = buckets.begin();
                it != buckets.end(); it++)
        {
            qs_bucket_item_t *item =
                (qs_bucket_item_t *) malloc(sizeof(qs_bucket_item_t));
            item->content = it->toCStyleObj();
            qs_list_append(&item->node, output->buckets);
        }
        output->count = (int *) malloc(sizeof(int));
        *output->count = outputCpp.GetCount();
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// delete_bucketInput init function.
void init_delete_bucket_input(qs_delete_bucket_input_t * input)
{
    // nothing to do;
    return;
}

// delete_bucketoutput init function.
void init_delete_bucket_output(qs_delete_bucket_output_t * output)
{
    qs_init_error_info(&output->error_info);
    return;
}

// delete_bucket Output release function.
void release_delete_bucket_output(qs_delete_bucket_output_t * output)
{
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_delete_bucket(qs_delete_bucket_input_t * input,
                         qs_delete_bucket_output_t * output,
                         qs_context_handle context_hdl)
{
    //init class DeleteBucketinputCpp
    DeleteBucketInput inputCpp;
    DeleteBucketOutput outputCpp;
    // packer cpp input
    // init output
    init_delete_bucket_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err = qsBucket->DeleteBucket(inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// delete_bucket_corsInput init function.
void init_delete_bucket_cors_input(qs_delete_bucket_cors_input_t * input)
{
    // nothing to do;
    return;
}

// delete_bucket_corsoutput init function.
void init_delete_bucket_cors_output(qs_delete_bucket_cors_output_t * output)
{
    qs_init_error_info(&output->error_info);
    return;
}

// delete_bucket_cors Output release function.
void release_delete_bucket_cors_output(qs_delete_bucket_cors_output_t * output)
{
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_delete_bucket_cors(qs_delete_bucket_cors_input_t * input,
                              qs_delete_bucket_cors_output_t * output,
                              qs_context_handle context_hdl)
{
    //init class DeleteBucketCORSinputCpp
    DeleteBucketCORSInput inputCpp;
    DeleteBucketCORSOutput outputCpp;
    // packer cpp input
    // init output
    init_delete_bucket_cors_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err = qsBucket->DeleteBucketCORS(inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// delete_bucket_external_mirrorInput init function.
void
init_delete_bucket_external_mirror_input
(qs_delete_bucket_external_mirror_input_t * input)
{
    // nothing to do;
    return;
}

// delete_bucket_external_mirroroutput init function.
void
init_delete_bucket_external_mirror_output
(qs_delete_bucket_external_mirror_output_t * output)
{
    qs_init_error_info(&output->error_info);
    return;
}

// delete_bucket_external_mirror Output release function.
void
release_delete_bucket_external_mirror_output
(qs_delete_bucket_external_mirror_output_t * output)
{
    qs_release_error_info(&output->error_info);
    return;
}

QsError
qs_delete_bucket_external_mirror(qs_delete_bucket_external_mirror_input_t *
                                 input,
                                 qs_delete_bucket_external_mirror_output_t *
                                 output, qs_context_handle context_hdl)
{
    //init class DeleteBucketExternalMirrorinputCpp
    DeleteBucketExternalMirrorInput inputCpp;
    DeleteBucketExternalMirrorOutput outputCpp;
    // packer cpp input
    // init output
    init_delete_bucket_external_mirror_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err = qsBucket->DeleteBucketExternalMirror(inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// delete_bucket_policyInput init function.
void init_delete_bucket_policy_input(qs_delete_bucket_policy_input_t * input)
{
    // nothing to do;
    return;
}

// delete_bucket_policyoutput init function.
void init_delete_bucket_policy_output(qs_delete_bucket_policy_output_t * output)
{
    qs_init_error_info(&output->error_info);
    return;
}

// delete_bucket_policy Output release function.
void release_delete_bucket_policy_output(qs_delete_bucket_policy_output_t *
        output)
{
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_delete_bucket_policy(qs_delete_bucket_policy_input_t * input,
                                qs_delete_bucket_policy_output_t * output,
                                qs_context_handle context_hdl)
{
    //init class DeleteBucketPolicyinputCpp
    DeleteBucketPolicyInput inputCpp;
    DeleteBucketPolicyOutput outputCpp;
    // packer cpp input
    // init output
    init_delete_bucket_policy_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err = qsBucket->DeleteBucketPolicy(inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// delete_multiple_objectsInput init function.
void init_delete_multiple_objects_input(qs_delete_multiple_objects_input_t *
                                        input)
{
    input->content_md5 = NULL;
    input->objects = NULL;
    input->quiet = NULL;
    return;
}

// delete_multiple_objectsoutput init function.
void init_delete_multiple_objects_output(qs_delete_multiple_objects_output_t *
        output)
{
    output->deleted = NULL;
    output->errors = NULL;
    qs_init_error_info(&output->error_info);
    return;
}

// delete_multiple_objects Output release function.
void release_delete_multiple_objects_output(qs_delete_multiple_objects_output_t
        * output)
{
    if (output->deleted)
    {
        qs_key_item_t *item = NULL;
        qs_key_item_t *item_to_delete = NULL;
        qs_list_for_each_entry(qs_key_item_t, item, output->deleted)
        {
            if (item_to_delete)
            {
                free(item_to_delete);
            }
            item_to_delete = item;
            release_key(item->content);
            free(item->content);
        }
        if (item_to_delete)
        {
            free(item_to_delete);
        }
        free(output->deleted);
    }
    if (output->errors)
    {
        qs_key_delete_error_item_t *item = NULL;
        qs_key_delete_error_item_t *item_to_delete = NULL;
        qs_list_for_each_entry(qs_key_delete_error_item_t, item, output->errors)
        {
            if (item_to_delete)
            {
                free(item_to_delete);
            }
            item_to_delete = item;
            release_key_delete_error(item->content);
            free(item->content);
        }
        if (item_to_delete)
        {
            free(item_to_delete);
        }
        free(output->errors);
    }
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_delete_multiple_objects(qs_delete_multiple_objects_input_t * input,
                                   qs_delete_multiple_objects_output_t * output,
                                   qs_context_handle context_hdl)
{
    //init class DeleteMultipleObjectsinputCpp
    DeleteMultipleObjectsInput inputCpp;
    DeleteMultipleObjectsOutput outputCpp;
    // packer cpp input
    if (input->content_md5)
    {
        inputCpp.SetContentMD5(input->content_md5);
    }
    if (input->objects)
    {
        //qs_list_t list_objects;
        //qs_list_init(list_objects);
        std::vector < KeyType > Objects;
        qs_key_item_t *item;
        qs_list_for_each_entry(qs_key_item_t, item, input->objects)
        {
            Objects.push_back(*item->content);
        }
        inputCpp.SetObjects(Objects);
    }
    if (input->quiet)
    {
        inputCpp.SetQuiet(*input->quiet);
    }
    // init output
    init_delete_multiple_objects_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err = qsBucket->DeleteMultipleObjects(inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        output->deleted = (qs_list_t *) malloc(sizeof(qs_list_t));
        qs_list_init(output->deleted);
        std::vector < KeyType > deleted = outputCpp.GetDeleted();
        for (std::vector < KeyType >::iterator it = deleted.begin();
                it != deleted.end(); it++)
        {
            qs_key_item_t *item =
                (qs_key_item_t *) malloc(sizeof(qs_key_item_t));
            item->content = it->toCStyleObj();
            qs_list_append(&item->node, output->deleted);
        }
        output->errors = (qs_list_t *) malloc(sizeof(qs_list_t));
        qs_list_init(output->errors);
        std::vector < KeyDeleteErrorType > errors = outputCpp.GetErrors();
        for (std::vector < KeyDeleteErrorType >::iterator it = errors.begin();
                it != errors.end(); it++)
        {
            qs_key_delete_error_item_t *item =
                (qs_key_delete_error_item_t *)
                malloc(sizeof(qs_key_delete_error_item_t));
            item->content = it->toCStyleObj();
            qs_list_append(&item->node, output->errors);
        }
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// get_bucket_aclInput init function.
void init_get_bucket_acl_input(qs_get_bucket_acl_input_t * input)
{
    // nothing to do;
    return;
}

// get_bucket_acloutput init function.
void init_get_bucket_acl_output(qs_get_bucket_acl_output_t * output)
{
    output->acl = NULL;
    output->owner = NULL;
    qs_init_error_info(&output->error_info);
    return;
}

// get_bucket_acl Output release function.
void release_get_bucket_acl_output(qs_get_bucket_acl_output_t * output)
{
    if (output->acl)
    {
        qs_acl_item_t *item = NULL;
        qs_acl_item_t *item_to_delete = NULL;
        qs_list_for_each_entry(qs_acl_item_t, item, output->acl)
        {
            if (item_to_delete)
            {
                free(item_to_delete);
            }
            item_to_delete = item;
            release_acl(item->content);
            free(item->content);
        }
        if (item_to_delete)
        {
            free(item_to_delete);
        }
        free(output->acl);
    }
    if (output->owner)
    {
        release_owner(output->owner);
        free(output->owner);
    }
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_get_bucket_acl(qs_get_bucket_acl_input_t * input,
                          qs_get_bucket_acl_output_t * output,
                          qs_context_handle context_hdl)
{
    //init class GetBucketACLinputCpp
    GetBucketACLInput inputCpp;
    GetBucketACLOutput outputCpp;
    // packer cpp input
    // init output
    init_get_bucket_acl_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err = qsBucket->GetBucketACL(inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        output->acl = (qs_list_t *) malloc(sizeof(qs_list_t));
        qs_list_init(output->acl);
        std::vector < ACLType > acl = outputCpp.GetACL();
        for (std::vector < ACLType >::iterator it = acl.begin();
                it != acl.end(); it++)
        {
            qs_acl_item_t *item =
                (qs_acl_item_t *) malloc(sizeof(qs_acl_item_t));
            item->content = it->toCStyleObj();
            qs_list_append(&item->node, output->acl);
        }
        output->owner = outputCpp.GetOwner().toCStyleObj();
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// get_bucket_corsInput init function.
void init_get_bucket_cors_input(qs_get_bucket_cors_input_t * input)
{
    // nothing to do;
    return;
}

// get_bucket_corsoutput init function.
void init_get_bucket_cors_output(qs_get_bucket_cors_output_t * output)
{
    output->cors_rules = NULL;
    qs_init_error_info(&output->error_info);
    return;
}

// get_bucket_cors Output release function.
void release_get_bucket_cors_output(qs_get_bucket_cors_output_t * output)
{
    if (output->cors_rules)
    {
        qs_cors_rule_item_t *item = NULL;
        qs_cors_rule_item_t *item_to_delete = NULL;
        qs_list_for_each_entry(qs_cors_rule_item_t, item, output->cors_rules)
        {
            if (item_to_delete)
            {
                free(item_to_delete);
            }
            item_to_delete = item;
            release_cors_rule(item->content);
            free(item->content);
        }
        if (item_to_delete)
        {
            free(item_to_delete);
        }
        free(output->cors_rules);
    }
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_get_bucket_cors(qs_get_bucket_cors_input_t * input,
                           qs_get_bucket_cors_output_t * output,
                           qs_context_handle context_hdl)
{
    //init class GetBucketCORSinputCpp
    GetBucketCORSInput inputCpp;
    GetBucketCORSOutput outputCpp;
    // packer cpp input
    // init output
    init_get_bucket_cors_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err = qsBucket->GetBucketCORS(inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        output->cors_rules = (qs_list_t *) malloc(sizeof(qs_list_t));
        qs_list_init(output->cors_rules);
        std::vector < CORSRuleType > corsRules = outputCpp.GetCORSRules();
        for (std::vector < CORSRuleType >::iterator it = corsRules.begin();
                it != corsRules.end(); it++)
        {
            qs_cors_rule_item_t *item =
                (qs_cors_rule_item_t *) malloc(sizeof(qs_cors_rule_item_t));
            item->content = it->toCStyleObj();
            qs_list_append(&item->node, output->cors_rules);
        }
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// get_bucket_external_mirrorInput init function.
void init_get_bucket_external_mirror_input(qs_get_bucket_external_mirror_input_t
        * input)
{
    // nothing to do;
    return;
}

// get_bucket_external_mirroroutput init function.
void
init_get_bucket_external_mirror_output(qs_get_bucket_external_mirror_output_t *
                                       output)
{
    output->source_site = NULL;
    qs_init_error_info(&output->error_info);
    return;
}

// get_bucket_external_mirror Output release function.
void
release_get_bucket_external_mirror_output(qs_get_bucket_external_mirror_output_t
        * output)
{
    if (output->source_site)
    {
        free(output->source_site);
    }
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_get_bucket_external_mirror(qs_get_bucket_external_mirror_input_t *
                                      input,
                                      qs_get_bucket_external_mirror_output_t *
                                      output, qs_context_handle context_hdl)
{
    //init class GetBucketExternalMirrorinputCpp
    GetBucketExternalMirrorInput inputCpp;
    GetBucketExternalMirrorOutput outputCpp;
    // packer cpp input
    // init output
    init_get_bucket_external_mirror_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err = qsBucket->GetBucketExternalMirror(inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        int SourceSiteLength = outputCpp.GetSourceSite().length();
        if (SourceSiteLength > 0)
        {
            output->source_site = (char *) malloc(SourceSiteLength + 1);
            memset(output->source_site, 0, SourceSiteLength + 1);
            strncpy(output->source_site, outputCpp.GetSourceSite().c_str(),
                    SourceSiteLength);
        }
        else
        {
            output->source_site = NULL;
        }
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// get_bucket_policyInput init function.
void init_get_bucket_policy_input(qs_get_bucket_policy_input_t * input)
{
    // nothing to do;
    return;
}

// get_bucket_policyoutput init function.
void init_get_bucket_policy_output(qs_get_bucket_policy_output_t * output)
{
    output->statement = NULL;
    qs_init_error_info(&output->error_info);
    return;
}

// get_bucket_policy Output release function.
void release_get_bucket_policy_output(qs_get_bucket_policy_output_t * output)
{
    if (output->statement)
    {
        qs_statement_item_t *item = NULL;
        qs_statement_item_t *item_to_delete = NULL;
        qs_list_for_each_entry(qs_statement_item_t, item, output->statement)
        {
            if (item_to_delete)
            {
                free(item_to_delete);
            }
            item_to_delete = item;
            release_statement(item->content);
            free(item->content);
        }
        if (item_to_delete)
        {
            free(item_to_delete);
        }
        free(output->statement);
    }
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_get_bucket_policy(qs_get_bucket_policy_input_t * input,
                             qs_get_bucket_policy_output_t * output,
                             qs_context_handle context_hdl)
{
    //init class GetBucketPolicyinputCpp
    GetBucketPolicyInput inputCpp;
    GetBucketPolicyOutput outputCpp;
    // packer cpp input
    // init output
    init_get_bucket_policy_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err = qsBucket->GetBucketPolicy(inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        output->statement = (qs_list_t *) malloc(sizeof(qs_list_t));
        qs_list_init(output->statement);
        std::vector < StatementType > statement = outputCpp.GetStatement();
        for (std::vector < StatementType >::iterator it = statement.begin();
                it != statement.end(); it++)
        {
            qs_statement_item_t *item =
                (qs_statement_item_t *) malloc(sizeof(qs_statement_item_t));
            item->content = it->toCStyleObj();
            qs_list_append(&item->node, output->statement);
        }
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// get_bucket_statisticsInput init function.
void init_get_bucket_statistics_input(qs_get_bucket_statistics_input_t * input)
{
    // nothing to do;
    return;
}

// get_bucket_statisticsoutput init function.
void init_get_bucket_statistics_output(qs_get_bucket_statistics_output_t *
                                       output)
{
    output->count = NULL;
    output->created = NULL;
    output->location = NULL;
    output->name = NULL;
    output->size = NULL;
    output->status = NULL;
    output->url = NULL;
    qs_init_error_info(&output->error_info);
    return;
}

// get_bucket_statistics Output release function.
void release_get_bucket_statistics_output(qs_get_bucket_statistics_output_t *
        output)
{
    if (output->count)
    {
        free(output->count);
    }
    if (output->created)
    {
        free(output->created);
    }
    if (output->location)
    {
        free(output->location);
    }
    if (output->name)
    {
        free(output->name);
    }
    if (output->size)
    {
        free(output->size);
    }
    if (output->status)
    {
        free(output->status);
    }
    if (output->url)
    {
        free(output->url);
    }
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_get_bucket_statistics(qs_get_bucket_statistics_input_t * input,
                                 qs_get_bucket_statistics_output_t * output,
                                 qs_context_handle context_hdl)
{
    //init class GetBucketStatisticsinputCpp
    GetBucketStatisticsInput inputCpp;
    GetBucketStatisticsOutput outputCpp;
    // packer cpp input
    // init output
    init_get_bucket_statistics_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err = qsBucket->GetBucketStatistics(inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        output->count = (long *) malloc(sizeof(long));
        *output->count = outputCpp.GetCount();
        int CreatedLength = outputCpp.GetCreated().length();
        if (CreatedLength > 0)
        {
            output->created = (char *) malloc(CreatedLength + 1);
            memset(output->created, 0, CreatedLength + 1);
            strncpy(output->created, outputCpp.GetCreated().c_str(),
                    CreatedLength);
        }
        else
        {
            output->created = NULL;
        }
        int LocationLength = outputCpp.GetLocation().length();
        if (LocationLength > 0)
        {
            output->location = (char *) malloc(LocationLength + 1);
            memset(output->location, 0, LocationLength + 1);
            strncpy(output->location, outputCpp.GetLocation().c_str(),
                    LocationLength);
        }
        else
        {
            output->location = NULL;
        }
        int NameLength = outputCpp.GetName().length();
        if (NameLength > 0)
        {
            output->name = (char *) malloc(NameLength + 1);
            memset(output->name, 0, NameLength + 1);
            strncpy(output->name, outputCpp.GetName().c_str(), NameLength);
        }
        else
        {
            output->name = NULL;
        }
        output->size = (long *) malloc(sizeof(long));
        *output->size = outputCpp.GetSize();
        int StatusLength = outputCpp.GetStatus().length();
        if (StatusLength > 0)
        {
            output->status = (char *) malloc(StatusLength + 1);
            memset(output->status, 0, StatusLength + 1);
            strncpy(output->status, outputCpp.GetStatus().c_str(),
                    StatusLength);
        }
        else
        {
            output->status = NULL;
        }
        int URLLength = outputCpp.GetURL().length();
        if (URLLength > 0)
        {
            output->url = (char *) malloc(URLLength + 1);
            memset(output->url, 0, URLLength + 1);
            strncpy(output->url, outputCpp.GetURL().c_str(), URLLength);
        }
        else
        {
            output->url = NULL;
        }
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// head_bucketInput init function.
void init_head_bucket_input(qs_head_bucket_input_t * input)
{
    // nothing to do;
    return;
}

// head_bucketoutput init function.
void init_head_bucket_output(qs_head_bucket_output_t * output)
{
    qs_init_error_info(&output->error_info);
    return;
}

// head_bucket Output release function.
void release_head_bucket_output(qs_head_bucket_output_t * output)
{
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_head_bucket(qs_head_bucket_input_t * input,
                       qs_head_bucket_output_t * output,
                       qs_context_handle context_hdl)
{
    //init class HeadBucketinputCpp
    HeadBucketInput inputCpp;
    HeadBucketOutput outputCpp;
    // packer cpp input
    // init output
    init_head_bucket_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err = qsBucket->HeadBucket(inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// list_multipart_uploadsInput init function.
void init_list_multipart_uploads_input(qs_list_multipart_uploads_input_t *
                                       input)
{
    input->delimiter = NULL;
    input->key_marker = NULL;
    input->limit = NULL;
    input->prefix = NULL;
    input->upload_id_marker = NULL;
    return;
}

// list_multipart_uploadsoutput init function.
void init_list_multipart_uploads_output(qs_list_multipart_uploads_output_t *
                                        output)
{
    output->common_prefixes = NULL;
    output->delimiter = NULL;
    output->limit = NULL;
    output->marker = NULL;
    output->name = NULL;
    output->next_key_marker = NULL;
    output->next_upload_id_marker = NULL;
    output->prefix = NULL;
    output->uploads = NULL;
    qs_init_error_info(&output->error_info);
    return;
}

// list_multipart_uploads Output release function.
void release_list_multipart_uploads_output(qs_list_multipart_uploads_output_t *
        output)
{
    if (output->common_prefixes)
    {
        qs_string_item_t *item = NULL;
        qs_string_item_t *item_to_delete = NULL;
        qs_list_for_each_entry(qs_string_item_t, item, output->common_prefixes)
        {
            if (item_to_delete)
            {
                free(item_to_delete);
            }
            item_to_delete = item;
            free(item->content);
        }
        if (item_to_delete)
        {
            free(item_to_delete);
        }
        free(output->common_prefixes);
    }
    if (output->delimiter)
    {
        free(output->delimiter);
    }
    if (output->limit)
    {
        free(output->limit);
    }
    if (output->marker)
    {
        free(output->marker);
    }
    if (output->name)
    {
        free(output->name);
    }
    if (output->next_key_marker)
    {
        free(output->next_key_marker);
    }
    if (output->next_upload_id_marker)
    {
        free(output->next_upload_id_marker);
    }
    if (output->prefix)
    {
        free(output->prefix);
    }
    if (output->uploads)
    {
        qs_uploads_item_t *item = NULL;
        qs_uploads_item_t *item_to_delete = NULL;
        qs_list_for_each_entry(qs_uploads_item_t, item, output->uploads)
        {
            if (item_to_delete)
            {
                free(item_to_delete);
            }
            item_to_delete = item;
            release_uploads(item->content);
            free(item->content);
        }
        if (item_to_delete)
        {
            free(item_to_delete);
        }
        free(output->uploads);
    }
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_list_multipart_uploads(qs_list_multipart_uploads_input_t * input,
                                  qs_list_multipart_uploads_output_t * output,
                                  qs_context_handle context_hdl)
{
    //init class ListMultipartUploadsinputCpp
    ListMultipartUploadsInput inputCpp;
    ListMultipartUploadsOutput outputCpp;
    // packer cpp input
    if (input->delimiter)
    {
        inputCpp.SetDelimiter(input->delimiter);
    }
    if (input->key_marker)
    {
        inputCpp.SetKeyMarker(input->key_marker);
    }
    if (input->limit)
    {
        inputCpp.SetLimit(*input->limit);
    }
    if (input->prefix)
    {
        inputCpp.SetPrefix(input->prefix);
    }
    if (input->upload_id_marker)
    {
        inputCpp.SetUploadIDMarker(input->upload_id_marker);
    }
    // init output
    init_list_multipart_uploads_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err = qsBucket->ListMultipartUploads(inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        output->common_prefixes = (qs_list_t *) malloc(sizeof(qs_list_t));
        qs_list_init(output->common_prefixes);
        std::vector < std::string > commonPrefixes =
            outputCpp.GetCommonPrefixes();
        for (std::vector < std::string >::iterator it = commonPrefixes.begin();
                it != commonPrefixes.end(); it++)
        {
            qs_string_item_t *item =
                (qs_string_item_t *) malloc(sizeof(qs_string_item_t));
            int CommonPrefixesLength = it->length();
            if (CommonPrefixesLength > 0)
            {
                item->content = (char *) malloc(CommonPrefixesLength + 1);
                memset(item->content, 0, CommonPrefixesLength + 1);
                item->content = (char *) malloc(CommonPrefixesLength + 1);
                strncpy(item->content, it->c_str(), CommonPrefixesLength);
            }
            else
            {
                item->content = NULL;
            }
            qs_list_append(&item->node, output->common_prefixes);
        }
        int DelimiterLength = outputCpp.GetDelimiter().length();
        if (DelimiterLength > 0)
        {
            output->delimiter = (char *) malloc(DelimiterLength + 1);
            memset(output->delimiter, 0, DelimiterLength + 1);
            strncpy(output->delimiter, outputCpp.GetDelimiter().c_str(),
                    DelimiterLength);
        }
        else
        {
            output->delimiter = NULL;
        }
        output->limit = (int *) malloc(sizeof(int));
        *output->limit = outputCpp.GetLimit();
        int MarkerLength = outputCpp.GetMarker().length();
        if (MarkerLength > 0)
        {
            output->marker = (char *) malloc(MarkerLength + 1);
            memset(output->marker, 0, MarkerLength + 1);
            strncpy(output->marker, outputCpp.GetMarker().c_str(),
                    MarkerLength);
        }
        else
        {
            output->marker = NULL;
        }
        int NameLength = outputCpp.GetName().length();
        if (NameLength > 0)
        {
            output->name = (char *) malloc(NameLength + 1);
            memset(output->name, 0, NameLength + 1);
            strncpy(output->name, outputCpp.GetName().c_str(), NameLength);
        }
        else
        {
            output->name = NULL;
        }
        int NextKeyMarkerLength = outputCpp.GetNextKeyMarker().length();
        if (NextKeyMarkerLength > 0)
        {
            output->next_key_marker = (char *) malloc(NextKeyMarkerLength + 1);
            memset(output->next_key_marker, 0, NextKeyMarkerLength + 1);
            strncpy(output->next_key_marker,
                    outputCpp.GetNextKeyMarker().c_str(), NextKeyMarkerLength);
        }
        else
        {
            output->next_key_marker = NULL;
        }
        int NextUploadIDMarkerLength =
            outputCpp.GetNextUploadIDMarker().length();
        if (NextUploadIDMarkerLength > 0)
        {
            output->next_upload_id_marker =
                (char *) malloc(NextUploadIDMarkerLength + 1);
            memset(output->next_upload_id_marker, 0,
                   NextUploadIDMarkerLength + 1);
            strncpy(output->next_upload_id_marker,
                    outputCpp.GetNextUploadIDMarker().c_str(),
                    NextUploadIDMarkerLength);
        }
        else
        {
            output->next_upload_id_marker = NULL;
        }
        int PrefixLength = outputCpp.GetPrefix().length();
        if (PrefixLength > 0)
        {
            output->prefix = (char *) malloc(PrefixLength + 1);
            memset(output->prefix, 0, PrefixLength + 1);
            strncpy(output->prefix, outputCpp.GetPrefix().c_str(),
                    PrefixLength);
        }
        else
        {
            output->prefix = NULL;
        }
        output->uploads = (qs_list_t *) malloc(sizeof(qs_list_t));
        qs_list_init(output->uploads);
        std::vector < UploadsType > uploads = outputCpp.GetUploads();
        for (std::vector < UploadsType >::iterator it = uploads.begin();
                it != uploads.end(); it++)
        {
            qs_uploads_item_t *item =
                (qs_uploads_item_t *) malloc(sizeof(qs_uploads_item_t));
            item->content = it->toCStyleObj();
            qs_list_append(&item->node, output->uploads);
        }
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// list_objectsInput init function.
void init_list_objects_input(qs_list_objects_input_t * input)
{
    input->delimiter = NULL;
    input->limit = NULL;
    input->marker = NULL;
    input->prefix = NULL;
    return;
}

// list_objectsoutput init function.
void init_list_objects_output(qs_list_objects_output_t * output)
{
    output->common_prefixes = NULL;
    output->delimiter = NULL;
    output->keys = NULL;
    output->limit = NULL;
    output->marker = NULL;
    output->name = NULL;
    output->next_marker = NULL;
    output->owner = NULL;
    output->prefix = NULL;
    qs_init_error_info(&output->error_info);
    return;
}

// list_objects Output release function.
void release_list_objects_output(qs_list_objects_output_t * output)
{
    if (output->common_prefixes)
    {
        qs_string_item_t *item = NULL;
        qs_string_item_t *item_to_delete = NULL;
        qs_list_for_each_entry(qs_string_item_t, item, output->common_prefixes)
        {
            if (item_to_delete)
            {
                free(item_to_delete);
            }
            item_to_delete = item;
            free(item->content);
        }
        if (item_to_delete)
        {
            free(item_to_delete);
        }
        free(output->common_prefixes);
    }
    if (output->delimiter)
    {
        free(output->delimiter);
    }
    if (output->keys)
    {
        qs_key_item_t *item = NULL;
        qs_key_item_t *item_to_delete = NULL;
        qs_list_for_each_entry(qs_key_item_t, item, output->keys)
        {
            if (item_to_delete)
            {
                free(item_to_delete);
            }
            item_to_delete = item;
            release_key(item->content);
            free(item->content);
        }
        if (item_to_delete)
        {
            free(item_to_delete);
        }
        free(output->keys);
    }
    if (output->limit)
    {
        free(output->limit);
    }
    if (output->marker)
    {
        free(output->marker);
    }
    if (output->name)
    {
        free(output->name);
    }
    if (output->next_marker)
    {
        free(output->next_marker);
    }
    if (output->owner)
    {
        release_owner(output->owner);
        free(output->owner);
    }
    if (output->prefix)
    {
        free(output->prefix);
    }
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_list_objects(qs_list_objects_input_t * input,
                        qs_list_objects_output_t * output,
                        qs_context_handle context_hdl)
{
    //init class ListObjectsinputCpp
    ListObjectsInput inputCpp;
    ListObjectsOutput outputCpp;
    // packer cpp input
    if (input->delimiter)
    {
        inputCpp.SetDelimiter(input->delimiter);
    }
    if (input->limit)
    {
        inputCpp.SetLimit(*input->limit);
    }
    if (input->marker)
    {
        inputCpp.SetMarker(input->marker);
    }
    if (input->prefix)
    {
        inputCpp.SetPrefix(input->prefix);
    }
    // init output
    init_list_objects_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err = qsBucket->ListObjects(inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        output->common_prefixes = (qs_list_t *) malloc(sizeof(qs_list_t));
        qs_list_init(output->common_prefixes);
        std::vector < std::string > commonPrefixes =
            outputCpp.GetCommonPrefixes();
        for (std::vector < std::string >::iterator it = commonPrefixes.begin();
                it != commonPrefixes.end(); it++)
        {
            qs_string_item_t *item =
                (qs_string_item_t *) malloc(sizeof(qs_string_item_t));
            int CommonPrefixesLength = it->length();
            if (CommonPrefixesLength > 0)
            {
                item->content = (char *) malloc(CommonPrefixesLength + 1);
                memset(item->content, 0, CommonPrefixesLength + 1);
                item->content = (char *) malloc(CommonPrefixesLength + 1);
                strncpy(item->content, it->c_str(), CommonPrefixesLength);
            }
            else
            {
                item->content = NULL;
            }
            qs_list_append(&item->node, output->common_prefixes);
        }
        int DelimiterLength = outputCpp.GetDelimiter().length();
        if (DelimiterLength > 0)
        {
            output->delimiter = (char *) malloc(DelimiterLength + 1);
            memset(output->delimiter, 0, DelimiterLength + 1);
            strncpy(output->delimiter, outputCpp.GetDelimiter().c_str(),
                    DelimiterLength);
        }
        else
        {
            output->delimiter = NULL;
        }
        output->keys = (qs_list_t *) malloc(sizeof(qs_list_t));
        qs_list_init(output->keys);
        std::vector < KeyType > keys = outputCpp.GetKeys();
        for (std::vector < KeyType >::iterator it = keys.begin();
                it != keys.end(); it++)
        {
            qs_key_item_t *item =
                (qs_key_item_t *) malloc(sizeof(qs_key_item_t));
            item->content = it->toCStyleObj();
            qs_list_append(&item->node, output->keys);
        }
        output->limit = (int *) malloc(sizeof(int));
        *output->limit = outputCpp.GetLimit();
        int MarkerLength = outputCpp.GetMarker().length();
        if (MarkerLength > 0)
        {
            output->marker = (char *) malloc(MarkerLength + 1);
            memset(output->marker, 0, MarkerLength + 1);
            strncpy(output->marker, outputCpp.GetMarker().c_str(),
                    MarkerLength);
        }
        else
        {
            output->marker = NULL;
        }
        int NameLength = outputCpp.GetName().length();
        if (NameLength > 0)
        {
            output->name = (char *) malloc(NameLength + 1);
            memset(output->name, 0, NameLength + 1);
            strncpy(output->name, outputCpp.GetName().c_str(), NameLength);
        }
        else
        {
            output->name = NULL;
        }
        int NextMarkerLength = outputCpp.GetNextMarker().length();
        if (NextMarkerLength > 0)
        {
            output->next_marker = (char *) malloc(NextMarkerLength + 1);
            memset(output->next_marker, 0, NextMarkerLength + 1);
            strncpy(output->next_marker, outputCpp.GetNextMarker().c_str(),
                    NextMarkerLength);
        }
        else
        {
            output->next_marker = NULL;
        }
        output->owner = outputCpp.GetOwner().toCStyleObj();
        int PrefixLength = outputCpp.GetPrefix().length();
        if (PrefixLength > 0)
        {
            output->prefix = (char *) malloc(PrefixLength + 1);
            memset(output->prefix, 0, PrefixLength + 1);
            strncpy(output->prefix, outputCpp.GetPrefix().c_str(),
                    PrefixLength);
        }
        else
        {
            output->prefix = NULL;
        }
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// put_bucketInput init function.
void init_put_bucket_input(qs_put_bucket_input_t * input)
{
    // nothing to do;
    return;
}

// put_bucketoutput init function.
void init_put_bucket_output(qs_put_bucket_output_t * output)
{
    qs_init_error_info(&output->error_info);
    return;
}

// put_bucket Output release function.
void release_put_bucket_output(qs_put_bucket_output_t * output)
{
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_put_bucket(qs_put_bucket_input_t * input,
                      qs_put_bucket_output_t * output,
                      qs_context_handle context_hdl)
{
    //init class PutBucketinputCpp
    PutBucketInput inputCpp;
    PutBucketOutput outputCpp;
    // packer cpp input
    // init output
    init_put_bucket_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err = qsBucket->PutBucket(inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// put_bucket_aclInput init function.
void init_put_bucket_acl_input(qs_put_bucket_acl_input_t * input)
{
    input->acl = NULL;
    return;
}

// put_bucket_acloutput init function.
void init_put_bucket_acl_output(qs_put_bucket_acl_output_t * output)
{
    qs_init_error_info(&output->error_info);
    return;
}

// put_bucket_acl Output release function.
void release_put_bucket_acl_output(qs_put_bucket_acl_output_t * output)
{
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_put_bucket_acl(qs_put_bucket_acl_input_t * input,
                          qs_put_bucket_acl_output_t * output,
                          qs_context_handle context_hdl)
{
    //init class PutBucketACLinputCpp
    PutBucketACLInput inputCpp;
    PutBucketACLOutput outputCpp;
    // packer cpp input
    if (input->acl)
    {
        //qs_list_t list_acl;
        //qs_list_init(list_acl);
        std::vector < ACLType > ACL;
        qs_acl_item_t *item;
        qs_list_for_each_entry(qs_acl_item_t, item, input->acl)
        {
            ACL.push_back(*item->content);
        }
        inputCpp.SetACL(ACL);
    }
    // init output
    init_put_bucket_acl_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err = qsBucket->PutBucketACL(inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// put_bucket_corsInput init function.
void init_put_bucket_cors_input(qs_put_bucket_cors_input_t * input)
{
    input->cors_rules = NULL;
    return;
}

// put_bucket_corsoutput init function.
void init_put_bucket_cors_output(qs_put_bucket_cors_output_t * output)
{
    qs_init_error_info(&output->error_info);
    return;
}

// put_bucket_cors Output release function.
void release_put_bucket_cors_output(qs_put_bucket_cors_output_t * output)
{
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_put_bucket_cors(qs_put_bucket_cors_input_t * input,
                           qs_put_bucket_cors_output_t * output,
                           qs_context_handle context_hdl)
{
    //init class PutBucketCORSinputCpp
    PutBucketCORSInput inputCpp;
    PutBucketCORSOutput outputCpp;
    // packer cpp input
    if (input->cors_rules)
    {
        //qs_list_t list_cors_rules;
        //qs_list_init(list_cors_rules);
        std::vector < CORSRuleType > CORSRules;
        qs_cors_rule_item_t *item;
        qs_list_for_each_entry(qs_cors_rule_item_t, item, input->cors_rules)
        {
            CORSRules.push_back(*item->content);
        }
        inputCpp.SetCORSRules(CORSRules);
    }
    // init output
    init_put_bucket_cors_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err = qsBucket->PutBucketCORS(inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// put_bucket_external_mirrorInput init function.
void init_put_bucket_external_mirror_input(qs_put_bucket_external_mirror_input_t
        * input)
{
    input->source_site = NULL;
    return;
}

// put_bucket_external_mirroroutput init function.
void
init_put_bucket_external_mirror_output(qs_put_bucket_external_mirror_output_t *
                                       output)
{
    qs_init_error_info(&output->error_info);
    return;
}

// put_bucket_external_mirror Output release function.
void
release_put_bucket_external_mirror_output(qs_put_bucket_external_mirror_output_t
        * output)
{
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_put_bucket_external_mirror(qs_put_bucket_external_mirror_input_t *
                                      input,
                                      qs_put_bucket_external_mirror_output_t *
                                      output, qs_context_handle context_hdl)
{
    //init class PutBucketExternalMirrorinputCpp
    PutBucketExternalMirrorInput inputCpp;
    PutBucketExternalMirrorOutput outputCpp;
    // packer cpp input
    if (input->source_site)
    {
        inputCpp.SetSourceSite(input->source_site);
    }
    // init output
    init_put_bucket_external_mirror_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err = qsBucket->PutBucketExternalMirror(inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// put_bucket_policyInput init function.
void init_put_bucket_policy_input(qs_put_bucket_policy_input_t * input)
{
    input->statement = NULL;
    return;
}

// put_bucket_policyoutput init function.
void init_put_bucket_policy_output(qs_put_bucket_policy_output_t * output)
{
    qs_init_error_info(&output->error_info);
    return;
}

// put_bucket_policy Output release function.
void release_put_bucket_policy_output(qs_put_bucket_policy_output_t * output)
{
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_put_bucket_policy(qs_put_bucket_policy_input_t * input,
                             qs_put_bucket_policy_output_t * output,
                             qs_context_handle context_hdl)
{
    //init class PutBucketPolicyinputCpp
    PutBucketPolicyInput inputCpp;
    PutBucketPolicyOutput outputCpp;
    // packer cpp input
    if (input->statement)
    {
        //qs_list_t list_statement;
        //qs_list_init(list_statement);
        std::vector < StatementType > Statement;
        qs_statement_item_t *item;
        qs_list_for_each_entry(qs_statement_item_t, item, input->statement)
        {
            Statement.push_back(*item->content);
        }
        inputCpp.SetStatement(Statement);
    }
    // init output
    init_put_bucket_policy_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err = qsBucket->PutBucketPolicy(inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// abort_multipart_uploadInput init function.
void init_abort_multipart_upload_input(qs_abort_multipart_upload_input_t *
                                       input)
{
    input->upload_id = NULL;
    return;
}

// abort_multipart_uploadoutput init function.
void init_abort_multipart_upload_output(qs_abort_multipart_upload_output_t *
                                        output)
{
    qs_init_error_info(&output->error_info);
    return;
}

// abort_multipart_upload Output release function.
void release_abort_multipart_upload_output(qs_abort_multipart_upload_output_t *
        output)
{
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_abort_multipart_upload(char *objectKey,
                                  qs_abort_multipart_upload_input_t * input,
                                  qs_abort_multipart_upload_output_t * output,
                                  qs_context_handle context_hdl)
{
    //init class AbortMultipartUploadinputCpp
    AbortMultipartUploadInput inputCpp;
    AbortMultipartUploadOutput outputCpp;
    // packer cpp input
    if (input->upload_id)
    {
        inputCpp.SetUploadID(input->upload_id);
    }
    // init output
    init_abort_multipart_upload_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err =
        qsBucket->AbortMultipartUpload(objectKey, inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// complete_multipart_uploadInput init function.
void init_complete_multipart_upload_input(qs_complete_multipart_upload_input_t *
        input)
{
    input->upload_id = NULL;
    input->etag = NULL;
    input->x_qs_encryption_customer_algorithm = NULL;
    input->x_qs_encryption_customer_key = NULL;
    input->x_qs_encryption_customer_key_md5 = NULL;
    input->object_parts = NULL;
    return;
}

// complete_multipart_uploadoutput init function.
void init_complete_multipart_upload_output(qs_complete_multipart_upload_output_t
        * output)
{
    output->x_qs_encryption_customer_algorithm = NULL;
    qs_init_error_info(&output->error_info);
    return;
}

// complete_multipart_upload Output release function.
void
release_complete_multipart_upload_output(qs_complete_multipart_upload_output_t *
        output)
{
    if (output->x_qs_encryption_customer_algorithm)
    {
        free(output->x_qs_encryption_customer_algorithm);
    }
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_complete_multipart_upload(char *objectKey,
                                     qs_complete_multipart_upload_input_t *
                                     input,
                                     qs_complete_multipart_upload_output_t *
                                     output, qs_context_handle context_hdl)
{
    //init class CompleteMultipartUploadinputCpp
    CompleteMultipartUploadInput inputCpp;
    CompleteMultipartUploadOutput outputCpp;
    // packer cpp input
    if (input->upload_id)
    {
        inputCpp.SetUploadID(input->upload_id);
    }
    if (input->etag)
    {
        inputCpp.SetETag(input->etag);
    }
    if (input->x_qs_encryption_customer_algorithm)
    {
        inputCpp.SetXQSEncryptionCustomerAlgorithm(input->
                x_qs_encryption_customer_algorithm);
    }
    if (input->x_qs_encryption_customer_key)
    {
        inputCpp.SetXQSEncryptionCustomerKey(input->
                                             x_qs_encryption_customer_key);
    }
    if (input->x_qs_encryption_customer_key_md5)
    {
        inputCpp.SetXQSEncryptionCustomerKeyMD5(input->
                                                x_qs_encryption_customer_key_md5);
    }
    if (input->object_parts)
    {
        //qs_list_t list_object_parts;
        //qs_list_init(list_object_parts);
        std::vector < ObjectPartType > ObjectParts;
        qs_object_part_item_t *item;
        qs_list_for_each_entry(qs_object_part_item_t, item, input->object_parts)
        {
            ObjectParts.push_back(*item->content);
        }
        inputCpp.SetObjectParts(ObjectParts);
    }
    // init output
    init_complete_multipart_upload_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err =
        qsBucket->CompleteMultipartUpload(objectKey, inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        int XQSEncryptionCustomerAlgorithmLength =
            outputCpp.GetXQSEncryptionCustomerAlgorithm().length();
        if (XQSEncryptionCustomerAlgorithmLength > 0)
        {
            output->x_qs_encryption_customer_algorithm =
                (char *) malloc(XQSEncryptionCustomerAlgorithmLength + 1);
            memset(output->x_qs_encryption_customer_algorithm, 0,
                   XQSEncryptionCustomerAlgorithmLength + 1);
            strncpy(output->x_qs_encryption_customer_algorithm,
                    outputCpp.GetXQSEncryptionCustomerAlgorithm().c_str(),
                    XQSEncryptionCustomerAlgorithmLength);
        }
        else
        {
            output->x_qs_encryption_customer_algorithm = NULL;
        }
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// delete_objectInput init function.
void init_delete_object_input(qs_delete_object_input_t * input)
{
    // nothing to do;
    return;
}

// delete_objectoutput init function.
void init_delete_object_output(qs_delete_object_output_t * output)
{
    qs_init_error_info(&output->error_info);
    return;
}

// delete_object Output release function.
void release_delete_object_output(qs_delete_object_output_t * output)
{
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_delete_object(char *objectKey, qs_delete_object_input_t * input,
                         qs_delete_object_output_t * output,
                         qs_context_handle context_hdl)
{
    //init class DeleteObjectinputCpp
    DeleteObjectInput inputCpp;
    DeleteObjectOutput outputCpp;
    // packer cpp input
    // init output
    init_delete_object_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err = qsBucket->DeleteObject(objectKey, inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// get_objectInput init function.
void init_get_object_input(qs_get_object_input_t * input)
{
    input->response_cache_control = NULL;
    input->response_content_disposition = NULL;
    input->response_content_encoding = NULL;
    input->response_content_language = NULL;
    input->response_content_type = NULL;
    input->response_expires = NULL;
    input->if_match = NULL;
    input->if_modified_since = NULL;
    input->if_none_match = NULL;
    input->if_unmodified_since = NULL;
    input->range = NULL;
    input->x_qs_encryption_customer_algorithm = NULL;
    input->x_qs_encryption_customer_key = NULL;
    input->x_qs_encryption_customer_key_md5 = NULL;
    return;
}

// get_objectoutput init function.
void init_get_object_output(qs_get_object_output_t * output)
{
    output->cache_control = NULL;
    output->content_disposition = NULL;
    output->content_encoding = NULL;
    output->content_language = NULL;
    output->content_length = NULL;
    output->content_range = NULL;
    output->content_type = NULL;
    output->etag = NULL;
    output->expires = NULL;
    output->last_modified = NULL;
    output->x_qs_encryption_customer_algorithm = NULL;
    output->bufLength = NULL;
    output->bodybuf = NULL;
    qs_init_error_info(&output->error_info);
    qs_init_error_info(&output->error_info);
    qs_init_error_info(&output->error_info);
    qs_init_error_info(&output->error_info);
    return;
}

// get_object Output release function.
void release_get_object_output(qs_get_object_output_t * output)
{
    if (output->cache_control)
    {
        free(output->cache_control);
    }
    if (output->content_disposition)
    {
        free(output->content_disposition);
    }
    if (output->content_encoding)
    {
        free(output->content_encoding);
    }
    if (output->content_language)
    {
        free(output->content_language);
    }
    if (output->content_length)
    {
        free(output->content_length);
    }
    if (output->content_range)
    {
        free(output->content_range);
    }
    if (output->content_type)
    {
        free(output->content_type);
    }
    if (output->etag)
    {
        free(output->etag);
    }
    if (output->expires)
    {
        free(output->expires);
    }
    if (output->last_modified)
    {
        free(output->last_modified);
    }
    if (output->x_qs_encryption_customer_algorithm)
    {
        free(output->x_qs_encryption_customer_algorithm);
    }
    // release binary body content
    if (output->bodybuf)
    {
        free(output->bodybuf);
    }
    if (output->bufLength)
    {
        free(output->bufLength);
    }
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_get_object(char *objectKey, qs_get_object_input_t * input,
                      qs_get_object_output_t * output,
                      qs_context_handle context_hdl)
{
    //init class GetObjectinputCpp
    GetObjectInput inputCpp;
    GetObjectOutput outputCpp;
    // packer cpp input
    if (input->response_cache_control)
    {
        inputCpp.SetResponseCacheControl(input->response_cache_control);
    }
    if (input->response_content_disposition)
    {
        inputCpp.SetResponseContentDisposition(input->
                                               response_content_disposition);
    }
    if (input->response_content_encoding)
    {
        inputCpp.SetResponseContentEncoding(input->response_content_encoding);
    }
    if (input->response_content_language)
    {
        inputCpp.SetResponseContentLanguage(input->response_content_language);
    }
    if (input->response_content_type)
    {
        inputCpp.SetResponseContentType(input->response_content_type);
    }
    if (input->response_expires)
    {
        inputCpp.SetResponseExpires(input->response_expires);
    }
    if (input->if_match)
    {
        inputCpp.SetIfMatch(input->if_match);
    }
    if (input->if_modified_since)
    {
        inputCpp.SetIfModifiedSince(input->if_modified_since);
    }
    if (input->if_none_match)
    {
        inputCpp.SetIfNoneMatch(input->if_none_match);
    }
    if (input->if_unmodified_since)
    {
        inputCpp.SetIfUnmodifiedSince(input->if_unmodified_since);
    }
    if (input->range)
    {
        inputCpp.SetRange(input->range);
    }
    if (input->x_qs_encryption_customer_algorithm)
    {
        inputCpp.SetXQSEncryptionCustomerAlgorithm(input->
                x_qs_encryption_customer_algorithm);
    }
    if (input->x_qs_encryption_customer_key)
    {
        inputCpp.SetXQSEncryptionCustomerKey(input->
                                             x_qs_encryption_customer_key);
    }
    if (input->x_qs_encryption_customer_key_md5)
    {
        inputCpp.SetXQSEncryptionCustomerKeyMD5(input->
                                                x_qs_encryption_customer_key_md5);
    }
    // init output
    init_get_object_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err = qsBucket->GetObject(objectKey, inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        int CacheControlLength = outputCpp.GetCacheControl().length();
        if (CacheControlLength > 0)
        {
            output->cache_control = (char *) malloc(CacheControlLength + 1);
            memset(output->cache_control, 0, CacheControlLength + 1);
            strncpy(output->cache_control, outputCpp.GetCacheControl().c_str(),
                    CacheControlLength);
        }
        else
        {
            output->cache_control = NULL;
        }
        int ContentDispositionLength =
            outputCpp.GetContentDisposition().length();
        if (ContentDispositionLength > 0)
        {
            output->content_disposition =
                (char *) malloc(ContentDispositionLength + 1);
            memset(output->content_disposition, 0,
                   ContentDispositionLength + 1);
            strncpy(output->content_disposition,
                    outputCpp.GetContentDisposition().c_str(),
                    ContentDispositionLength);
        }
        else
        {
            output->content_disposition = NULL;
        }
        int ContentEncodingLength = outputCpp.GetContentEncoding().length();
        if (ContentEncodingLength > 0)
        {
            output->content_encoding =
                (char *) malloc(ContentEncodingLength + 1);
            memset(output->content_encoding, 0, ContentEncodingLength + 1);
            strncpy(output->content_encoding,
                    outputCpp.GetContentEncoding().c_str(),
                    ContentEncodingLength);
        }
        else
        {
            output->content_encoding = NULL;
        }
        int ContentLanguageLength = outputCpp.GetContentLanguage().length();
        if (ContentLanguageLength > 0)
        {
            output->content_language =
                (char *) malloc(ContentLanguageLength + 1);
            memset(output->content_language, 0, ContentLanguageLength + 1);
            strncpy(output->content_language,
                    outputCpp.GetContentLanguage().c_str(),
                    ContentLanguageLength);
        }
        else
        {
            output->content_language = NULL;
        }
        output->content_length = (long *) malloc(sizeof(long));
        *output->content_length = outputCpp.GetContentLength();
        int ContentRangeLength = outputCpp.GetContentRange().length();
        if (ContentRangeLength > 0)
        {
            output->content_range = (char *) malloc(ContentRangeLength + 1);
            memset(output->content_range, 0, ContentRangeLength + 1);
            strncpy(output->content_range, outputCpp.GetContentRange().c_str(),
                    ContentRangeLength);
        }
        else
        {
            output->content_range = NULL;
        }
        int ContentTypeLength = outputCpp.GetContentType().length();
        if (ContentTypeLength > 0)
        {
            output->content_type = (char *) malloc(ContentTypeLength + 1);
            memset(output->content_type, 0, ContentTypeLength + 1);
            strncpy(output->content_type, outputCpp.GetContentType().c_str(),
                    ContentTypeLength);
        }
        else
        {
            output->content_type = NULL;
        }
        int ETagLength = outputCpp.GetETag().length();
        if (ETagLength > 0)
        {
            output->etag = (char *) malloc(ETagLength + 1);
            memset(output->etag, 0, ETagLength + 1);
            strncpy(output->etag, outputCpp.GetETag().c_str(), ETagLength);
        }
        else
        {
            output->etag = NULL;
        }
        int ExpiresLength = outputCpp.GetExpires().length();
        if (ExpiresLength > 0)
        {
            output->expires = (char *) malloc(ExpiresLength + 1);
            memset(output->expires, 0, ExpiresLength + 1);
            strncpy(output->expires, outputCpp.GetExpires().c_str(),
                    ExpiresLength);
        }
        else
        {
            output->expires = NULL;
        }
        int LastModifiedLength = outputCpp.GetLastModified().length();
        if (LastModifiedLength > 0)
        {
            output->last_modified = (char *) malloc(LastModifiedLength + 1);
            memset(output->last_modified, 0, LastModifiedLength + 1);
            strncpy(output->last_modified, outputCpp.GetLastModified().c_str(),
                    LastModifiedLength);
        }
        else
        {
            output->last_modified = NULL;
        }
        int XQSEncryptionCustomerAlgorithmLength =
            outputCpp.GetXQSEncryptionCustomerAlgorithm().length();
        if (XQSEncryptionCustomerAlgorithmLength > 0)
        {
            output->x_qs_encryption_customer_algorithm =
                (char *) malloc(XQSEncryptionCustomerAlgorithmLength + 1);
            memset(output->x_qs_encryption_customer_algorithm, 0,
                   XQSEncryptionCustomerAlgorithmLength + 1);
            strncpy(output->x_qs_encryption_customer_algorithm,
                    outputCpp.GetXQSEncryptionCustomerAlgorithm().c_str(),
                    XQSEncryptionCustomerAlgorithmLength);
        }
        else
        {
            output->x_qs_encryption_customer_algorithm = NULL;
        }
        std::iostream * respStreamBody = outputCpp.GetBody();
        if (respStreamBody)
        {
            respStreamBody->seekg(0, outputCpp.GetBody()->end);
            size_t streamSize = outputCpp.GetBody()->tellg();
            respStreamBody->seekg(0, outputCpp.GetBody()->beg);
            output->bodybuf = (void *) malloc(streamSize);
            output->bufLength = (int64_t *) malloc(sizeof(int64_t));
            //size_t readCount = (streamSize > *output->bufLength)? *output->bufLength : streamSize;
            respStreamBody->read((char *) output->bodybuf, streamSize);
            *output->bufLength =
                static_cast < int64_t > (respStreamBody->gcount());;
            //clean up
            delete respStreamBody;
        }
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// head_objectInput init function.
void init_head_object_input(qs_head_object_input_t * input)
{
    input->if_match = NULL;
    input->if_modified_since = NULL;
    input->if_none_match = NULL;
    input->if_unmodified_since = NULL;
    input->x_qs_encryption_customer_algorithm = NULL;
    input->x_qs_encryption_customer_key = NULL;
    input->x_qs_encryption_customer_key_md5 = NULL;
    return;
}

// head_objectoutput init function.
void init_head_object_output(qs_head_object_output_t * output)
{
    output->content_length = NULL;
    output->content_type = NULL;
    output->etag = NULL;
    output->last_modified = NULL;
    output->x_qs_encryption_customer_algorithm = NULL;
    qs_init_error_info(&output->error_info);
    return;
}

// head_object Output release function.
void release_head_object_output(qs_head_object_output_t * output)
{
    if (output->content_length)
    {
        free(output->content_length);
    }
    if (output->content_type)
    {
        free(output->content_type);
    }
    if (output->etag)
    {
        free(output->etag);
    }
    if (output->last_modified)
    {
        free(output->last_modified);
    }
    if (output->x_qs_encryption_customer_algorithm)
    {
        free(output->x_qs_encryption_customer_algorithm);
    }
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_head_object(char *objectKey, qs_head_object_input_t * input,
                       qs_head_object_output_t * output,
                       qs_context_handle context_hdl)
{
    //init class HeadObjectinputCpp
    HeadObjectInput inputCpp;
    HeadObjectOutput outputCpp;
    // packer cpp input
    if (input->if_match)
    {
        inputCpp.SetIfMatch(input->if_match);
    }
    if (input->if_modified_since)
    {
        inputCpp.SetIfModifiedSince(input->if_modified_since);
    }
    if (input->if_none_match)
    {
        inputCpp.SetIfNoneMatch(input->if_none_match);
    }
    if (input->if_unmodified_since)
    {
        inputCpp.SetIfUnmodifiedSince(input->if_unmodified_since);
    }
    if (input->x_qs_encryption_customer_algorithm)
    {
        inputCpp.SetXQSEncryptionCustomerAlgorithm(input->
                x_qs_encryption_customer_algorithm);
    }
    if (input->x_qs_encryption_customer_key)
    {
        inputCpp.SetXQSEncryptionCustomerKey(input->
                                             x_qs_encryption_customer_key);
    }
    if (input->x_qs_encryption_customer_key_md5)
    {
        inputCpp.SetXQSEncryptionCustomerKeyMD5(input->
                                                x_qs_encryption_customer_key_md5);
    }
    // init output
    init_head_object_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err = qsBucket->HeadObject(objectKey, inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        output->content_length = (long *) malloc(sizeof(long));
        *output->content_length = outputCpp.GetContentLength();
        int ContentTypeLength = outputCpp.GetContentType().length();
        if (ContentTypeLength > 0)
        {
            output->content_type = (char *) malloc(ContentTypeLength + 1);
            memset(output->content_type, 0, ContentTypeLength + 1);
            strncpy(output->content_type, outputCpp.GetContentType().c_str(),
                    ContentTypeLength);
        }
        else
        {
            output->content_type = NULL;
        }
        int ETagLength = outputCpp.GetETag().length();
        if (ETagLength > 0)
        {
            output->etag = (char *) malloc(ETagLength + 1);
            memset(output->etag, 0, ETagLength + 1);
            strncpy(output->etag, outputCpp.GetETag().c_str(), ETagLength);
        }
        else
        {
            output->etag = NULL;
        }
        int LastModifiedLength = outputCpp.GetLastModified().length();
        if (LastModifiedLength > 0)
        {
            output->last_modified = (char *) malloc(LastModifiedLength + 1);
            memset(output->last_modified, 0, LastModifiedLength + 1);
            strncpy(output->last_modified, outputCpp.GetLastModified().c_str(),
                    LastModifiedLength);
        }
        else
        {
            output->last_modified = NULL;
        }
        int XQSEncryptionCustomerAlgorithmLength =
            outputCpp.GetXQSEncryptionCustomerAlgorithm().length();
        if (XQSEncryptionCustomerAlgorithmLength > 0)
        {
            output->x_qs_encryption_customer_algorithm =
                (char *) malloc(XQSEncryptionCustomerAlgorithmLength + 1);
            memset(output->x_qs_encryption_customer_algorithm, 0,
                   XQSEncryptionCustomerAlgorithmLength + 1);
            strncpy(output->x_qs_encryption_customer_algorithm,
                    outputCpp.GetXQSEncryptionCustomerAlgorithm().c_str(),
                    XQSEncryptionCustomerAlgorithmLength);
        }
        else
        {
            output->x_qs_encryption_customer_algorithm = NULL;
        }
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// image_processInput init function.
void init_image_process_input(qs_image_process_input_t * input)
{
    input->action = NULL;
    input->response_cache_control = NULL;
    input->response_content_disposition = NULL;
    input->response_content_encoding = NULL;
    input->response_content_language = NULL;
    input->response_content_type = NULL;
    input->response_expires = NULL;
    input->if_modified_since = NULL;
    return;
}

// image_processoutput init function.
void init_image_process_output(qs_image_process_output_t * output)
{
    output->content_length = NULL;
    output->bufLength = NULL;
    output->bodybuf = NULL;
    qs_init_error_info(&output->error_info);
    qs_init_error_info(&output->error_info);
    return;
}

// image_process Output release function.
void release_image_process_output(qs_image_process_output_t * output)
{
    if (output->content_length)
    {
        free(output->content_length);
    }
    // release binary body content
    if (output->bodybuf)
    {
        free(output->bodybuf);
    }
    if (output->bufLength)
    {
        free(output->bufLength);
    }
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_image_process(char *objectKey, qs_image_process_input_t * input,
                         qs_image_process_output_t * output,
                         qs_context_handle context_hdl)
{
    //init class ImageProcessinputCpp
    ImageProcessInput inputCpp;
    ImageProcessOutput outputCpp;
    // packer cpp input
    if (input->action)
    {
        inputCpp.SetAction(input->action);
    }
    if (input->response_cache_control)
    {
        inputCpp.SetResponseCacheControl(input->response_cache_control);
    }
    if (input->response_content_disposition)
    {
        inputCpp.SetResponseContentDisposition(input->
                                               response_content_disposition);
    }
    if (input->response_content_encoding)
    {
        inputCpp.SetResponseContentEncoding(input->response_content_encoding);
    }
    if (input->response_content_language)
    {
        inputCpp.SetResponseContentLanguage(input->response_content_language);
    }
    if (input->response_content_type)
    {
        inputCpp.SetResponseContentType(input->response_content_type);
    }
    if (input->response_expires)
    {
        inputCpp.SetResponseExpires(input->response_expires);
    }
    if (input->if_modified_since)
    {
        inputCpp.SetIfModifiedSince(input->if_modified_since);
    }
    // init output
    init_image_process_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err = qsBucket->ImageProcess(objectKey, inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        output->content_length = (long *) malloc(sizeof(long));
        *output->content_length = outputCpp.GetContentLength();
        std::iostream * respStreamBody = outputCpp.GetBody();
        if (respStreamBody)
        {
            respStreamBody->seekg(0, outputCpp.GetBody()->end);
            size_t streamSize = outputCpp.GetBody()->tellg();
            respStreamBody->seekg(0, outputCpp.GetBody()->beg);
            output->bodybuf = (void *) malloc(streamSize);
            output->bufLength = (int64_t *) malloc(sizeof(int64_t));
            //size_t readCount = (streamSize > *output->bufLength)? *output->bufLength : streamSize;
            respStreamBody->read((char *) output->bodybuf, streamSize);
            *output->bufLength =
                static_cast < int64_t > (respStreamBody->gcount());;
            //clean up
            delete respStreamBody;
        }
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// initiate_multipart_uploadInput init function.
void init_initiate_multipart_upload_input(qs_initiate_multipart_upload_input_t *
        input)
{
    input->content_type = NULL;
    input->x_qs_encryption_customer_algorithm = NULL;
    input->x_qs_encryption_customer_key = NULL;
    input->x_qs_encryption_customer_key_md5 = NULL;
    return;
}

// initiate_multipart_uploadoutput init function.
void init_initiate_multipart_upload_output(qs_initiate_multipart_upload_output_t
        * output)
{
    output->x_qs_encryption_customer_algorithm = NULL;
    output->bucket = NULL;
    output->key = NULL;
    output->upload_id = NULL;
    qs_init_error_info(&output->error_info);
    return;
}

// initiate_multipart_upload Output release function.
void
release_initiate_multipart_upload_output(qs_initiate_multipart_upload_output_t *
        output)
{
    if (output->x_qs_encryption_customer_algorithm)
    {
        free(output->x_qs_encryption_customer_algorithm);
    }
    if (output->bucket)
    {
        free(output->bucket);
    }
    if (output->key)
    {
        free(output->key);
    }
    if (output->upload_id)
    {
        free(output->upload_id);
    }
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_initiate_multipart_upload(char *objectKey,
                                     qs_initiate_multipart_upload_input_t *
                                     input,
                                     qs_initiate_multipart_upload_output_t *
                                     output, qs_context_handle context_hdl)
{
    //init class InitiateMultipartUploadinputCpp
    InitiateMultipartUploadInput inputCpp;
    InitiateMultipartUploadOutput outputCpp;
    // packer cpp input
    if (input->content_type)
    {
        inputCpp.SetContentType(input->content_type);
    }
    if (input->x_qs_encryption_customer_algorithm)
    {
        inputCpp.SetXQSEncryptionCustomerAlgorithm(input->
                x_qs_encryption_customer_algorithm);
    }
    if (input->x_qs_encryption_customer_key)
    {
        inputCpp.SetXQSEncryptionCustomerKey(input->
                                             x_qs_encryption_customer_key);
    }
    if (input->x_qs_encryption_customer_key_md5)
    {
        inputCpp.SetXQSEncryptionCustomerKeyMD5(input->
                                                x_qs_encryption_customer_key_md5);
    }
    // init output
    init_initiate_multipart_upload_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err =
        qsBucket->InitiateMultipartUpload(objectKey, inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        int XQSEncryptionCustomerAlgorithmLength =
            outputCpp.GetXQSEncryptionCustomerAlgorithm().length();
        if (XQSEncryptionCustomerAlgorithmLength > 0)
        {
            output->x_qs_encryption_customer_algorithm =
                (char *) malloc(XQSEncryptionCustomerAlgorithmLength + 1);
            memset(output->x_qs_encryption_customer_algorithm, 0,
                   XQSEncryptionCustomerAlgorithmLength + 1);
            strncpy(output->x_qs_encryption_customer_algorithm,
                    outputCpp.GetXQSEncryptionCustomerAlgorithm().c_str(),
                    XQSEncryptionCustomerAlgorithmLength);
        }
        else
        {
            output->x_qs_encryption_customer_algorithm = NULL;
        }
        int BucketLength = outputCpp.GetBucket().length();
        if (BucketLength > 0)
        {
            output->bucket = (char *) malloc(BucketLength + 1);
            memset(output->bucket, 0, BucketLength + 1);
            strncpy(output->bucket, outputCpp.GetBucket().c_str(),
                    BucketLength);
        }
        else
        {
            output->bucket = NULL;
        }
        int KeyLength = outputCpp.GetKey().length();
        if (KeyLength > 0)
        {
            output->key = (char *) malloc(KeyLength + 1);
            memset(output->key, 0, KeyLength + 1);
            strncpy(output->key, outputCpp.GetKey().c_str(), KeyLength);
        }
        else
        {
            output->key = NULL;
        }
        int UploadIDLength = outputCpp.GetUploadID().length();
        if (UploadIDLength > 0)
        {
            output->upload_id = (char *) malloc(UploadIDLength + 1);
            memset(output->upload_id, 0, UploadIDLength + 1);
            strncpy(output->upload_id, outputCpp.GetUploadID().c_str(),
                    UploadIDLength);
        }
        else
        {
            output->upload_id = NULL;
        }
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// list_multipartInput init function.
void init_list_multipart_input(qs_list_multipart_input_t * input)
{
    input->limit = NULL;
    input->part_number_marker = NULL;
    input->upload_id = NULL;
    return;
}

// list_multipartoutput init function.
void init_list_multipart_output(qs_list_multipart_output_t * output)
{
    output->count = NULL;
    output->object_parts = NULL;
    qs_init_error_info(&output->error_info);
    return;
}

// list_multipart Output release function.
void release_list_multipart_output(qs_list_multipart_output_t * output)
{
    if (output->count)
    {
        free(output->count);
    }
    if (output->object_parts)
    {
        qs_object_part_item_t *item = NULL;
        qs_object_part_item_t *item_to_delete = NULL;
        qs_list_for_each_entry(qs_object_part_item_t, item,
                               output->object_parts)
        {
            if (item_to_delete)
            {
                free(item_to_delete);
            }
            item_to_delete = item;
            release_object_part(item->content);
            free(item->content);
        }
        if (item_to_delete)
        {
            free(item_to_delete);
        }
        free(output->object_parts);
    }
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_list_multipart(char *objectKey, qs_list_multipart_input_t * input,
                          qs_list_multipart_output_t * output,
                          qs_context_handle context_hdl)
{
    //init class ListMultipartinputCpp
    ListMultipartInput inputCpp;
    ListMultipartOutput outputCpp;
    // packer cpp input
    if (input->limit)
    {
        inputCpp.SetLimit(*input->limit);
    }
    if (input->part_number_marker)
    {
        inputCpp.SetPartNumberMarker(*input->part_number_marker);
    }
    if (input->upload_id)
    {
        inputCpp.SetUploadID(input->upload_id);
    }
    // init output
    init_list_multipart_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err = qsBucket->ListMultipart(objectKey, inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        output->count = (int *) malloc(sizeof(int));
        *output->count = outputCpp.GetCount();
        output->object_parts = (qs_list_t *) malloc(sizeof(qs_list_t));
        qs_list_init(output->object_parts);
        std::vector < ObjectPartType > objectParts = outputCpp.GetObjectParts();
        for (std::vector < ObjectPartType >::iterator it = objectParts.begin();
                it != objectParts.end(); it++)
        {
            qs_object_part_item_t *item =
                (qs_object_part_item_t *) malloc(sizeof(qs_object_part_item_t));
            item->content = it->toCStyleObj();
            qs_list_append(&item->node, output->object_parts);
        }
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// options_objectInput init function.
void init_options_object_input(qs_options_object_input_t * input)
{
    input->access_control_request_headers = NULL;
    input->access_control_request_method = NULL;
    input->origin = NULL;
    return;
}

// options_objectoutput init function.
void init_options_object_output(qs_options_object_output_t * output)
{
    output->access_control_allow_headers = NULL;
    output->access_control_allow_methods = NULL;
    output->access_control_allow_origin = NULL;
    output->access_control_expose_headers = NULL;
    output->access_control_max_age = NULL;
    qs_init_error_info(&output->error_info);
    return;
}

// options_object Output release function.
void release_options_object_output(qs_options_object_output_t * output)
{
    if (output->access_control_allow_headers)
    {
        free(output->access_control_allow_headers);
    }
    if (output->access_control_allow_methods)
    {
        free(output->access_control_allow_methods);
    }
    if (output->access_control_allow_origin)
    {
        free(output->access_control_allow_origin);
    }
    if (output->access_control_expose_headers)
    {
        free(output->access_control_expose_headers);
    }
    if (output->access_control_max_age)
    {
        free(output->access_control_max_age);
    }
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_options_object(char *objectKey, qs_options_object_input_t * input,
                          qs_options_object_output_t * output,
                          qs_context_handle context_hdl)
{
    //init class OptionsObjectinputCpp
    OptionsObjectInput inputCpp;
    OptionsObjectOutput outputCpp;
    // packer cpp input
    if (input->access_control_request_headers)
    {
        inputCpp.SetAccessControlRequestHeaders(input->
                                                access_control_request_headers);
    }
    if (input->access_control_request_method)
    {
        inputCpp.SetAccessControlRequestMethod(input->
                                               access_control_request_method);
    }
    if (input->origin)
    {
        inputCpp.SetOrigin(input->origin);
    }
    // init output
    init_options_object_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err = qsBucket->OptionsObject(objectKey, inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        int AccessControlAllowHeadersLength =
            outputCpp.GetAccessControlAllowHeaders().length();
        if (AccessControlAllowHeadersLength > 0)
        {
            output->access_control_allow_headers =
                (char *) malloc(AccessControlAllowHeadersLength + 1);
            memset(output->access_control_allow_headers, 0,
                   AccessControlAllowHeadersLength + 1);
            strncpy(output->access_control_allow_headers,
                    outputCpp.GetAccessControlAllowHeaders().c_str(),
                    AccessControlAllowHeadersLength);
        }
        else
        {
            output->access_control_allow_headers = NULL;
        }
        int AccessControlAllowMethodsLength =
            outputCpp.GetAccessControlAllowMethods().length();
        if (AccessControlAllowMethodsLength > 0)
        {
            output->access_control_allow_methods =
                (char *) malloc(AccessControlAllowMethodsLength + 1);
            memset(output->access_control_allow_methods, 0,
                   AccessControlAllowMethodsLength + 1);
            strncpy(output->access_control_allow_methods,
                    outputCpp.GetAccessControlAllowMethods().c_str(),
                    AccessControlAllowMethodsLength);
        }
        else
        {
            output->access_control_allow_methods = NULL;
        }
        int AccessControlAllowOriginLength =
            outputCpp.GetAccessControlAllowOrigin().length();
        if (AccessControlAllowOriginLength > 0)
        {
            output->access_control_allow_origin =
                (char *) malloc(AccessControlAllowOriginLength + 1);
            memset(output->access_control_allow_origin, 0,
                   AccessControlAllowOriginLength + 1);
            strncpy(output->access_control_allow_origin,
                    outputCpp.GetAccessControlAllowOrigin().c_str(),
                    AccessControlAllowOriginLength);
        }
        else
        {
            output->access_control_allow_origin = NULL;
        }
        int AccessControlExposeHeadersLength =
            outputCpp.GetAccessControlExposeHeaders().length();
        if (AccessControlExposeHeadersLength > 0)
        {
            output->access_control_expose_headers =
                (char *) malloc(AccessControlExposeHeadersLength + 1);
            memset(output->access_control_expose_headers, 0,
                   AccessControlExposeHeadersLength + 1);
            strncpy(output->access_control_expose_headers,
                    outputCpp.GetAccessControlExposeHeaders().c_str(),
                    AccessControlExposeHeadersLength);
        }
        else
        {
            output->access_control_expose_headers = NULL;
        }
        int AccessControlMaxAgeLength =
            outputCpp.GetAccessControlMaxAge().length();
        if (AccessControlMaxAgeLength > 0)
        {
            output->access_control_max_age =
                (char *) malloc(AccessControlMaxAgeLength + 1);
            memset(output->access_control_max_age, 0,
                   AccessControlMaxAgeLength + 1);
            strncpy(output->access_control_max_age,
                    outputCpp.GetAccessControlMaxAge().c_str(),
                    AccessControlMaxAgeLength);
        }
        else
        {
            output->access_control_max_age = NULL;
        }
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    return err;
}

// put_objectInput init function.
void init_put_object_input(qs_put_object_input_t * input)
{
    input->content_length = NULL;
    input->content_md5 = NULL;
    input->content_type = NULL;
    input->expect = NULL;
    input->x_qs_copy_source = NULL;
    input->x_qs_copy_source_encryption_customer_algorithm = NULL;
    input->x_qs_copy_source_encryption_customer_key = NULL;
    input->x_qs_copy_source_encryption_customer_key_md5 = NULL;
    input->x_qs_copy_source_if_match = NULL;
    input->x_qs_copy_source_if_modified_since = NULL;
    input->x_qs_copy_source_if_none_match = NULL;
    input->x_qs_copy_source_if_unmodified_since = NULL;
    input->x_qs_encryption_customer_algorithm = NULL;
    input->x_qs_encryption_customer_key = NULL;
    input->x_qs_encryption_customer_key_md5 = NULL;
    input->x_qs_fetch_if_unmodified_since = NULL;
    input->x_qs_fetch_source = NULL;
    input->x_qs_move_source = NULL;
    input->bufLength = NULL;
    input->bodybuf = NULL;
    return;
}

// put_objectoutput init function.
void init_put_object_output(qs_put_object_output_t * output)
{
    output->etag = NULL;
    output->x_qs_encryption_customer_algorithm = NULL;
    qs_init_error_info(&output->error_info);
    return;
}

// put_object Output release function.
void release_put_object_output(qs_put_object_output_t * output)
{
    if (output->etag)
    {
        free(output->etag);
    }
    if (output->x_qs_encryption_customer_algorithm)
    {
        free(output->x_qs_encryption_customer_algorithm);
    }
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_put_object(char *objectKey, qs_put_object_input_t * input,
                      qs_put_object_output_t * output,
                      qs_context_handle context_hdl)
{
    //init class PutObjectinputCpp
    PutObjectInput inputCpp;
    PutObjectOutput outputCpp;
    std::iostream * reqStreamBody = NULL;
    // packer cpp input
    if (input->content_length)
    {
        inputCpp.SetContentLength(*input->content_length);
    }
    if (input->content_md5)
    {
        inputCpp.SetContentMD5(input->content_md5);
    }
    if (input->content_type)
    {
        inputCpp.SetContentType(input->content_type);
    }
    if (input->expect)
    {
        inputCpp.SetExpect(input->expect);
    }
    if (input->x_qs_copy_source)
    {
        inputCpp.SetXQSCopySource(input->x_qs_copy_source);
    }
    if (input->x_qs_copy_source_encryption_customer_algorithm)
    {
        inputCpp.SetXQSCopySourceEncryptionCustomerAlgorithm(input->
                x_qs_copy_source_encryption_customer_algorithm);
    }
    if (input->x_qs_copy_source_encryption_customer_key)
    {
        inputCpp.SetXQSCopySourceEncryptionCustomerKey(input->
                x_qs_copy_source_encryption_customer_key);
    }
    if (input->x_qs_copy_source_encryption_customer_key_md5)
    {
        inputCpp.SetXQSCopySourceEncryptionCustomerKeyMD5(input->
                x_qs_copy_source_encryption_customer_key_md5);
    }
    if (input->x_qs_copy_source_if_match)
    {
        inputCpp.SetXQSCopySourceIfMatch(input->x_qs_copy_source_if_match);
    }
    if (input->x_qs_copy_source_if_modified_since)
    {
        inputCpp.SetXQSCopySourceIfModifiedSince(input->
                x_qs_copy_source_if_modified_since);
    }
    if (input->x_qs_copy_source_if_none_match)
    {
        inputCpp.SetXQSCopySourceIfNoneMatch(input->
                                             x_qs_copy_source_if_none_match);
    }
    if (input->x_qs_copy_source_if_unmodified_since)
    {
        inputCpp.SetXQSCopySourceIfUnmodifiedSince(input->
                x_qs_copy_source_if_unmodified_since);
    }
    if (input->x_qs_encryption_customer_algorithm)
    {
        inputCpp.SetXQSEncryptionCustomerAlgorithm(input->
                x_qs_encryption_customer_algorithm);
    }
    if (input->x_qs_encryption_customer_key)
    {
        inputCpp.SetXQSEncryptionCustomerKey(input->
                                             x_qs_encryption_customer_key);
    }
    if (input->x_qs_encryption_customer_key_md5)
    {
        inputCpp.SetXQSEncryptionCustomerKeyMD5(input->
                                                x_qs_encryption_customer_key_md5);
    }
    if (input->x_qs_fetch_if_unmodified_since)
    {
        inputCpp.SetXQSFetchIfUnmodifiedSince(input->
                                              x_qs_fetch_if_unmodified_since);
    }
    if (input->x_qs_fetch_source)
    {
        inputCpp.SetXQSFetchSource(input->x_qs_fetch_source);
    }
    if (input->x_qs_move_source)
    {
        inputCpp.SetXQSMoveSource(input->x_qs_move_source);
    }
    if (input->bodybuf)
    {
        reqStreamBody = new QsStream();
        reqStreamBody->write(static_cast < char *>(input->bodybuf),
                             (size_t) * input->bufLength);
        inputCpp.SetBody(reqStreamBody);
    }
    // init output
    init_put_object_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err = qsBucket->PutObject(objectKey, inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        int ETagLength = outputCpp.GetETag().length();
        if (ETagLength > 0)
        {
            output->etag = (char *) malloc(ETagLength + 1);
            memset(output->etag, 0, ETagLength + 1);
            strncpy(output->etag, outputCpp.GetETag().c_str(), ETagLength);
        }
        else
        {
            output->etag = NULL;
        }
        int XQSEncryptionCustomerAlgorithmLength =
            outputCpp.GetXQSEncryptionCustomerAlgorithm().length();
        if (XQSEncryptionCustomerAlgorithmLength > 0)
        {
            output->x_qs_encryption_customer_algorithm =
                (char *) malloc(XQSEncryptionCustomerAlgorithmLength + 1);
            memset(output->x_qs_encryption_customer_algorithm, 0,
                   XQSEncryptionCustomerAlgorithmLength + 1);
            strncpy(output->x_qs_encryption_customer_algorithm,
                    outputCpp.GetXQSEncryptionCustomerAlgorithm().c_str(),
                    XQSEncryptionCustomerAlgorithmLength);
        }
        else
        {
            output->x_qs_encryption_customer_algorithm = NULL;
        }
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    // clean up
    if (reqStreamBody)
    {
        delete reqStreamBody;
        reqStreamBody = NULL;
    }
    return err;
}

// upload_multipartInput init function.
void init_upload_multipart_input(qs_upload_multipart_input_t * input)
{
    input->part_number = NULL;
    input->upload_id = NULL;
    input->content_length = NULL;
    input->content_md5 = NULL;
    input->x_qs_copy_range = NULL;
    input->x_qs_copy_source = NULL;
    input->x_qs_copy_source_encryption_customer_algorithm = NULL;
    input->x_qs_copy_source_encryption_customer_key = NULL;
    input->x_qs_copy_source_encryption_customer_key_md5 = NULL;
    input->x_qs_copy_source_if_match = NULL;
    input->x_qs_copy_source_if_modified_since = NULL;
    input->x_qs_copy_source_if_none_match = NULL;
    input->x_qs_copy_source_if_unmodified_since = NULL;
    input->x_qs_encryption_customer_algorithm = NULL;
    input->x_qs_encryption_customer_key = NULL;
    input->x_qs_encryption_customer_key_md5 = NULL;
    input->bufLength = NULL;
    input->bodybuf = NULL;
    return;
}

// upload_multipartoutput init function.
void init_upload_multipart_output(qs_upload_multipart_output_t * output)
{
    output->etag = NULL;
    output->x_qs_content_copy_range = NULL;
    output->x_qs_encryption_customer_algorithm = NULL;
    qs_init_error_info(&output->error_info);
    return;
}

// upload_multipart Output release function.
void release_upload_multipart_output(qs_upload_multipart_output_t * output)
{
    if (output->etag)
    {
        free(output->etag);
    }
    if (output->x_qs_content_copy_range)
    {
        free(output->x_qs_content_copy_range);
    }
    if (output->x_qs_encryption_customer_algorithm)
    {
        free(output->x_qs_encryption_customer_algorithm);
    }
    qs_release_error_info(&output->error_info);
    return;
}

QsError qs_upload_multipart(char *objectKey,
                            qs_upload_multipart_input_t * input,
                            qs_upload_multipart_output_t * output,
                            qs_context_handle context_hdl)
{
    //init class UploadMultipartinputCpp
    UploadMultipartInput inputCpp;
    UploadMultipartOutput outputCpp;
    std::iostream * reqStreamBody = NULL;
    // packer cpp input
    if (input->part_number)
    {
        inputCpp.SetPartNumber(*input->part_number);
    }
    if (input->upload_id)
    {
        inputCpp.SetUploadID(input->upload_id);
    }
    if (input->content_length)
    {
        inputCpp.SetContentLength(*input->content_length);
    }
    if (input->content_md5)
    {
        inputCpp.SetContentMD5(input->content_md5);
    }
    if (input->x_qs_copy_range)
    {
        inputCpp.SetXQSCopyRange(input->x_qs_copy_range);
    }
    if (input->x_qs_copy_source)
    {
        inputCpp.SetXQSCopySource(input->x_qs_copy_source);
    }
    if (input->x_qs_copy_source_encryption_customer_algorithm)
    {
        inputCpp.SetXQSCopySourceEncryptionCustomerAlgorithm(input->
                x_qs_copy_source_encryption_customer_algorithm);
    }
    if (input->x_qs_copy_source_encryption_customer_key)
    {
        inputCpp.SetXQSCopySourceEncryptionCustomerKey(input->
                x_qs_copy_source_encryption_customer_key);
    }
    if (input->x_qs_copy_source_encryption_customer_key_md5)
    {
        inputCpp.SetXQSCopySourceEncryptionCustomerKeyMD5(input->
                x_qs_copy_source_encryption_customer_key_md5);
    }
    if (input->x_qs_copy_source_if_match)
    {
        inputCpp.SetXQSCopySourceIfMatch(input->x_qs_copy_source_if_match);
    }
    if (input->x_qs_copy_source_if_modified_since)
    {
        inputCpp.SetXQSCopySourceIfModifiedSince(input->
                x_qs_copy_source_if_modified_since);
    }
    if (input->x_qs_copy_source_if_none_match)
    {
        inputCpp.SetXQSCopySourceIfNoneMatch(input->
                                             x_qs_copy_source_if_none_match);
    }
    if (input->x_qs_copy_source_if_unmodified_since)
    {
        inputCpp.SetXQSCopySourceIfUnmodifiedSince(input->
                x_qs_copy_source_if_unmodified_since);
    }
    if (input->x_qs_encryption_customer_algorithm)
    {
        inputCpp.SetXQSEncryptionCustomerAlgorithm(input->
                x_qs_encryption_customer_algorithm);
    }
    if (input->x_qs_encryption_customer_key)
    {
        inputCpp.SetXQSEncryptionCustomerKey(input->
                                             x_qs_encryption_customer_key);
    }
    if (input->x_qs_encryption_customer_key_md5)
    {
        inputCpp.SetXQSEncryptionCustomerKeyMD5(input->
                                                x_qs_encryption_customer_key_md5);
    }
    if (input->bodybuf)
    {
        reqStreamBody = new QsStream();
        reqStreamBody->write(static_cast < char *>(input->bodybuf),
                             (size_t) * input->bufLength);
        inputCpp.SetBody(reqStreamBody);
    }
    // init output
    init_upload_multipart_output(output);
    // call cpp op
    Bucket *qsBucket = (Bucket *) (context_hdl.pQsBucket);
    QsError err = qsBucket->UploadMultipart(objectKey, inputCpp, outputCpp);
    if (QS_ERR_NO_ERROR == err)
    {
        // uppacker cpp output
        int ETagLength = outputCpp.GetETag().length();
        if (ETagLength > 0)
        {
            output->etag = (char *) malloc(ETagLength + 1);
            memset(output->etag, 0, ETagLength + 1);
            strncpy(output->etag, outputCpp.GetETag().c_str(), ETagLength);
        }
        else
        {
            output->etag = NULL;
        }
        int XQSContentCopyRangeLength =
            outputCpp.GetXQSContentCopyRange().length();
        if (XQSContentCopyRangeLength > 0)
        {
            output->x_qs_content_copy_range =
                (char *) malloc(XQSContentCopyRangeLength + 1);
            memset(output->x_qs_content_copy_range, 0,
                   XQSContentCopyRangeLength + 1);
            strncpy(output->x_qs_content_copy_range,
                    outputCpp.GetXQSContentCopyRange().c_str(),
                    XQSContentCopyRangeLength);
        }
        else
        {
            output->x_qs_content_copy_range = NULL;
        }
        int XQSEncryptionCustomerAlgorithmLength =
            outputCpp.GetXQSEncryptionCustomerAlgorithm().length();
        if (XQSEncryptionCustomerAlgorithmLength > 0)
        {
            output->x_qs_encryption_customer_algorithm =
                (char *) malloc(XQSEncryptionCustomerAlgorithmLength + 1);
            memset(output->x_qs_encryption_customer_algorithm, 0,
                   XQSEncryptionCustomerAlgorithmLength + 1);
            strncpy(output->x_qs_encryption_customer_algorithm,
                    outputCpp.GetXQSEncryptionCustomerAlgorithm().c_str(),
                    XQSEncryptionCustomerAlgorithmLength);
        }
        else
        {
            output->x_qs_encryption_customer_algorithm = NULL;
        }
        output->response_code = (int) outputCpp.GetResponseCode();
    }
    else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
    {
        // if got unexcepted response
        output->response_code = (int) outputCpp.GetResponseCode();
        ResponseErrorInfo errorInfo = outputCpp.GetResponseErrInfo();
        LOGW << "Got unexcepted response with code:" << errorInfo.
             code << " " << errorInfo.message;
        qs_set_error_info(&output->error_info, errorInfo);
    }
    // clean up
    if (reqStreamBody)
    {
        delete reqStreamBody;
        reqStreamBody = NULL;
    }
    return err;
}
