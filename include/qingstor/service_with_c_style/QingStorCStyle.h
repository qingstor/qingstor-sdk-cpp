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

#pragma once

#include  "../QsSdkOption.h"
#include  "Types.h"

#ifdef  __cplusplus
extern "C" {
#endif

typedef struct
{
    void *pQsService;
    void *pQsBucket;
} qs_context_handle;

typedef struct
{
    const char *additional_user_agent;
    const char *access_key_id;
    const char *secret_access_key;
    const char *host;
    const char *protocol;
    int port;
    int conn_retries;
    int timeout_period;
} qs_config_t;

// "init_and_cleanup_curl": SDK wide options for curl
// If it is being used then we automatically initialize and clean it up.
// If this is a problem for you, set this to false.
QS_SDK_API void qs_init_sdk(const char *logfile_path, LogLevel qs_log_level,
                            unsigned int init_and_cleanup_curl);

QS_SDK_API void qs_shutdown_sdk(unsigned int init_and_cleanup_curl);

// Create service and get contex handle which is used with erery SDK API.
QS_SDK_API qs_context_handle qs_create_service(qs_config_t qs_config,
        const char *qs_bucket_name,
        const char *qs_bucket_zone);

// Same to fuction "qs_create_service".Specify the path to config file
// instead of providing config structure.
QS_SDK_API qs_context_handle qs_create_service_with_configfile(const char
        *qs_config_path, const char
        *qs_bucket_name, const char
        *qs_bucket_zone);

// Release contex handle created by functuin "qs_create_service".
QS_SDK_API void qs_release_service(qs_context_handle context_hdl);

// list_bucketsInput presents input for list_buckets.
typedef struct
{
    //Limits results to buckets that in the location
    char *location;
} qs_list_buckets_input_t;

// list_bucketsInput init function.
void init_list_buckets_input(qs_list_buckets_input_t * input);

typedef qs_default_input_s qs_delete_bucket_input_t;
// delete_bucketInput init function.
void init_delete_bucket_input(qs_delete_bucket_input_t * input);

typedef qs_default_input_s qs_delete_bucket_cors_input_t;
// delete_bucket_corsInput init function.
void init_delete_bucket_cors_input(qs_delete_bucket_cors_input_t * input);

typedef qs_default_input_s qs_delete_bucket_external_mirror_input_t;
// delete_bucket_external_mirrorInput init function.
void init_delete_bucket_external_mirror_input
(qs_delete_bucket_external_mirror_input_t * input);

typedef qs_default_input_s qs_delete_bucket_policy_input_t;
// delete_bucket_policyInput init function.
void init_delete_bucket_policy_input(qs_delete_bucket_policy_input_t *
                                     input);

// delete_multiple_objectsInput presents input for delete_multiple_objects.
typedef struct
{
    //Object MD5sum
    char *content_md5;		// Required
    //A list of keys to delete

    qs_list_t *objects;		// Required
    //Whether to return the list of deleted objects
    int *quiet;
} qs_delete_multiple_objects_input_t;

// delete_multiple_objectsInput init function.
void init_delete_multiple_objects_input(qs_delete_multiple_objects_input_t *
                                        input);

typedef qs_default_input_s qs_get_bucket_acl_input_t;
// get_bucket_aclInput init function.
void init_get_bucket_acl_input(qs_get_bucket_acl_input_t * input);

typedef qs_default_input_s qs_get_bucket_cors_input_t;
// get_bucket_corsInput init function.
void init_get_bucket_cors_input(qs_get_bucket_cors_input_t * input);

typedef qs_default_input_s qs_get_bucket_external_mirror_input_t;
// get_bucket_external_mirrorInput init function.
void init_get_bucket_external_mirror_input
(qs_get_bucket_external_mirror_input_t * input);

typedef qs_default_input_s qs_get_bucket_policy_input_t;
// get_bucket_policyInput init function.
void init_get_bucket_policy_input(qs_get_bucket_policy_input_t * input);

typedef qs_default_input_s qs_get_bucket_statistics_input_t;
// get_bucket_statisticsInput init function.
void init_get_bucket_statistics_input(qs_get_bucket_statistics_input_t *
                                      input);

typedef qs_default_input_s qs_head_bucket_input_t;
// head_bucketInput init function.
void init_head_bucket_input(qs_head_bucket_input_t * input);

// list_multipart_uploadsInput presents input for list_multipart_uploads.
typedef struct
{
    //Put all keys that share a common prefix into a list
    char *delimiter;
    //Limit results returned from the first key after key_marker sorted by alphabetical order
    char *key_marker;
    //Results count limit
    int *limit;
    //Limits results to keys that begin with the prefix
    char *prefix;
    //Limit results returned from the first uploading segment after upload_id_marker sorted by the time of upload_id
    char *upload_id_marker;
} qs_list_multipart_uploads_input_t;

// list_multipart_uploadsInput init function.
void init_list_multipart_uploads_input(qs_list_multipart_uploads_input_t *
                                       input);

// list_objectsInput presents input for list_objects.
typedef struct
{
    //Put all keys that share a common prefix into a list
    char *delimiter;
    //Results count limit
    int *limit;
    //Limit results to keys that start at this marker
    char *marker;
    //Limits results to keys that begin with the prefix
    char *prefix;
} qs_list_objects_input_t;

// list_objectsInput init function.
void init_list_objects_input(qs_list_objects_input_t * input);

typedef qs_default_input_s qs_put_bucket_input_t;
// put_bucketInput init function.
void init_put_bucket_input(qs_put_bucket_input_t * input);

// put_bucket_aclInput presents input for put_bucket_acl.
typedef struct
{
    //Bucket ACL rules

    qs_list_t *acl;			// Required
} qs_put_bucket_acl_input_t;

// put_bucket_aclInput init function.
void init_put_bucket_acl_input(qs_put_bucket_acl_input_t * input);

// put_bucket_corsInput presents input for put_bucket_cors.
typedef struct
{
    //Bucket CORS rules

    qs_list_t *cors_rules;	// Required
} qs_put_bucket_cors_input_t;

// put_bucket_corsInput init function.
void init_put_bucket_cors_input(qs_put_bucket_cors_input_t * input);

// put_bucket_external_mirrorInput presents input for put_bucket_external_mirror.
typedef struct
{
    //Source site url
    char *source_site;		// Required
} qs_put_bucket_external_mirror_input_t;

// put_bucket_external_mirrorInput init function.
void init_put_bucket_external_mirror_input
(qs_put_bucket_external_mirror_input_t * input);

// put_bucket_policyInput presents input for put_bucket_policy.
typedef struct
{
    //Bucket policy statement

    qs_list_t *statement;	// Required
} qs_put_bucket_policy_input_t;

// put_bucket_policyInput init function.
void init_put_bucket_policy_input(qs_put_bucket_policy_input_t * input);

// abort_multipart_uploadInput presents input for abort_multipart_upload.
typedef struct
{
    //Object multipart upload ID
    char *upload_id;		// Required
} qs_abort_multipart_upload_input_t;

// abort_multipart_uploadInput init function.
void init_abort_multipart_upload_input(qs_abort_multipart_upload_input_t *
                                       input);

// complete_multipart_uploadInput presents input for complete_multipart_upload.
typedef struct
{
    //Object multipart upload ID
    char *upload_id;		// Required
    //MD5sum of the object part
    char *etag;
    //Encryption algorithm of the object
    char *x_qs_encryption_customer_algorithm;
    //Encryption key of the object
    char *x_qs_encryption_customer_key;
    //MD5sum of encryption key
    char *x_qs_encryption_customer_key_md5;
    //Object parts

    qs_list_t *object_parts;
} qs_complete_multipart_upload_input_t;

// complete_multipart_uploadInput init function.
void init_complete_multipart_upload_input
(qs_complete_multipart_upload_input_t * input);

typedef qs_default_input_s qs_delete_object_input_t;
// delete_objectInput init function.
void init_delete_object_input(qs_delete_object_input_t * input);

// get_objectInput presents input for get_object.
typedef struct
{
    //Specified the Cache-Control response header
    char *response_cache_control;
    //Specified the Content-Disposition response header
    char *response_content_disposition;
    //Specified the Content-Encoding response header
    char *response_content_encoding;
    //Specified the Content-Language response header
    char *response_content_language;
    //Specified the Content-Type response header
    char *response_content_type;
    //Specified the Expires response header
    char *response_expires;
    //Check whether the ETag matches
    char *if_match;
    //Check whether the object has been modified
    char *if_modified_since;
    //Check whether the ETag does not match
    char *if_none_match;
    //Check whether the object has not been modified
    char *if_unmodified_since;
    //Specified range of the object
    char *range;
    //Encryption algorithm of the object
    char *x_qs_encryption_customer_algorithm;
    //Encryption key of the object
    char *x_qs_encryption_customer_key;
    //MD5sum of encryption key
    char *x_qs_encryption_customer_key_md5;
} qs_get_object_input_t;

// get_objectInput init function.
void init_get_object_input(qs_get_object_input_t * input);

// head_objectInput presents input for head_object.
typedef struct
{
    //Check whether the ETag matches
    char *if_match;
    //Check whether the object has been modified
    char *if_modified_since;
    //Check whether the ETag does not match
    char *if_none_match;
    //Check whether the object has not been modified
    char *if_unmodified_since;
    //Encryption algorithm of the object
    char *x_qs_encryption_customer_algorithm;
    //Encryption key of the object
    char *x_qs_encryption_customer_key;
    //MD5sum of encryption key
    char *x_qs_encryption_customer_key_md5;
} qs_head_object_input_t;

// head_objectInput init function.
void init_head_object_input(qs_head_object_input_t * input);

// image_processInput presents input for image_process.
typedef struct
{
    //Image process action
    char *action;			// Required
    //Specified the Cache-Control response header
    char *response_cache_control;
    //Specified the Content-Disposition response header
    char *response_content_disposition;
    //Specified the Content-Encoding response header
    char *response_content_encoding;
    //Specified the Content-Language response header
    char *response_content_language;
    //Specified the Content-Type response header
    char *response_content_type;
    //Specified the Expires response header
    char *response_expires;
    //Check whether the object has been modified
    char *if_modified_since;
} qs_image_process_input_t;

// image_processInput init function.
void init_image_process_input(qs_image_process_input_t * input);

// initiate_multipart_uploadInput presents input for initiate_multipart_upload.
typedef struct
{
    //Object content type
    char *content_type;
    //Encryption algorithm of the object
    char *x_qs_encryption_customer_algorithm;
    //Encryption key of the object
    char *x_qs_encryption_customer_key;
    //MD5sum of encryption key
    char *x_qs_encryption_customer_key_md5;
} qs_initiate_multipart_upload_input_t;

// initiate_multipart_uploadInput init function.
void init_initiate_multipart_upload_input
(qs_initiate_multipart_upload_input_t * input);

// list_multipartInput presents input for list_multipart.
typedef struct
{
    //Limit results count
    int *limit;
    //Object multipart upload part number
    int *part_number_marker;
    //Object multipart upload ID
    char *upload_id;		// Required
} qs_list_multipart_input_t;

// list_multipartInput init function.
void init_list_multipart_input(qs_list_multipart_input_t * input);

// options_objectInput presents input for options_object.
typedef struct
{
    //Request headers
    char *access_control_request_headers;
    //Request method
    char *access_control_request_method;	// Required
    //Request origin
    char *origin;			// Required
} qs_options_object_input_t;

// options_objectInput init function.
void init_options_object_input(qs_options_object_input_t * input);

// put_objectInput presents input for put_object.
typedef struct
{
    //Object content size
    long *content_length;	// Required
    //Object MD5sum
    char *content_md5;
    //Object content type
    char *content_type;
    //Used to indicate that particular server behaviors are required by the client
    char *expect;
    //Copy source, format (/<bucket-name>/<object-key>)
    char *x_qs_copy_source;
    //Encryption algorithm of the object
    char *x_qs_copy_source_encryption_customer_algorithm;
    //Encryption key of the object
    char *x_qs_copy_source_encryption_customer_key;
    //MD5sum of encryption key
    char *x_qs_copy_source_encryption_customer_key_md5;
    //Check whether the copy source matches
    char *x_qs_copy_source_if_match;
    //Check whether the copy source has been modified
    char *x_qs_copy_source_if_modified_since;
    //Check whether the copy source does not match
    char *x_qs_copy_source_if_none_match;
    //Check whether the copy source has not been modified
    char *x_qs_copy_source_if_unmodified_since;
    //Encryption algorithm of the object
    char *x_qs_encryption_customer_algorithm;
    //Encryption key of the object
    char *x_qs_encryption_customer_key;
    //MD5sum of encryption key
    char *x_qs_encryption_customer_key_md5;
    //Check whether fetch target object has not been modified
    char *x_qs_fetch_if_unmodified_since;
    //Fetch source, should be a valid url
    char *x_qs_fetch_source;
    //Move source, format (/<bucket-name>/<object-key>)
    char *x_qs_move_source;
    int64_t *bufLength;

    void *bodybuf;

} qs_put_object_input_t;

// put_objectInput init function.
void init_put_object_input(qs_put_object_input_t * input);

// upload_multipartInput presents input for upload_multipart.
typedef struct
{
    //Object multipart upload part number
    int *part_number;		// Required
    //Object multipart upload ID
    char *upload_id;		// Required
    //Object multipart content length
    long *content_length;
    //Object multipart content MD5sum
    char *content_md5;
    //Specify range of the source object
    char *x_qs_copy_range;
    //Copy source, format (/<bucket-name>/<object-key>)
    char *x_qs_copy_source;
    //Encryption algorithm of the object
    char *x_qs_copy_source_encryption_customer_algorithm;
    //Encryption key of the object
    char *x_qs_copy_source_encryption_customer_key;
    //MD5sum of encryption key
    char *x_qs_copy_source_encryption_customer_key_md5;
    //Check whether the Etag of copy source matches the specified value
    char *x_qs_copy_source_if_match;
    //Check whether the copy source has been modified since the specified date
    char *x_qs_copy_source_if_modified_since;
    //Check whether the Etag of copy source does not matches the specified value
    char *x_qs_copy_source_if_none_match;
    //Check whether the copy source has not been unmodified since the specified date
    char *x_qs_copy_source_if_unmodified_since;
    //Encryption algorithm of the object
    char *x_qs_encryption_customer_algorithm;
    //Encryption key of the object
    char *x_qs_encryption_customer_key;
    //MD5sum of encryption key
    char *x_qs_encryption_customer_key_md5;
    int64_t *bufLength;

    void *bodybuf;

} qs_upload_multipart_input_t;

// upload_multipartInput init function.
void init_upload_multipart_input(qs_upload_multipart_input_t * input);

typedef struct
{
    //Buckets information

    qs_list_t *buckets;
    //Bucket count
    int *count;

    int response_code;

    qs_error_info_t error_info;

} qs_list_buckets_output_t;

// list_bucketsInput init function.
void release_list_buckets_output(qs_list_buckets_output_t * output);

typedef qs_default_output_s qs_delete_bucket_output_t;

// delete_bucketInput init function.
void release_delete_bucket_output(qs_delete_bucket_output_t * output);

typedef qs_default_output_s qs_delete_bucket_cors_output_t;

// delete_bucket_corsInput init function.
void release_delete_bucket_cors_output(qs_delete_bucket_cors_output_t *
                                       output);

typedef qs_default_output_s qs_delete_bucket_external_mirror_output_t;

// delete_bucket_external_mirrorInput init function.
void release_delete_bucket_external_mirror_output
(qs_delete_bucket_external_mirror_output_t * output);

typedef qs_default_output_s qs_delete_bucket_policy_output_t;

// delete_bucket_policyInput init function.
void release_delete_bucket_policy_output(qs_delete_bucket_policy_output_t *
        output);

typedef struct
{
    //List of deleted objects

    qs_list_t *deleted;
    //Error messages

    qs_list_t *errors;

    int response_code;

    qs_error_info_t error_info;

} qs_delete_multiple_objects_output_t;

// delete_multiple_objectsInput init function.
void release_delete_multiple_objects_output
(qs_delete_multiple_objects_output_t * output);

typedef struct
{
    //Bucket ACL rules

    qs_list_t *acl;
    //Bucket owner

    qs_owner_t *owner;

    int response_code;

    qs_error_info_t error_info;

} qs_get_bucket_acl_output_t;

// get_bucket_aclInput init function.
void release_get_bucket_acl_output(qs_get_bucket_acl_output_t * output);

typedef struct
{
    //Bucket CORS rules

    qs_list_t *cors_rules;

    int response_code;

    qs_error_info_t error_info;

} qs_get_bucket_cors_output_t;

// get_bucket_corsInput init function.
void release_get_bucket_cors_output(qs_get_bucket_cors_output_t * output);

typedef struct
{
    //Source site url
    char *source_site;

    int response_code;

    qs_error_info_t error_info;

} qs_get_bucket_external_mirror_output_t;

// get_bucket_external_mirrorInput init function.
void release_get_bucket_external_mirror_output
(qs_get_bucket_external_mirror_output_t * output);

typedef struct
{
    //Bucket policy statement

    qs_list_t *statement;

    int response_code;

    qs_error_info_t error_info;

} qs_get_bucket_policy_output_t;

// get_bucket_policyInput init function.
void release_get_bucket_policy_output(qs_get_bucket_policy_output_t *
                                      output);

typedef struct
{
    //Objects count in the bucket
    long *count;
    //Bucket created time
    char *created;
    //QingCloud Zone ID
    char *location;
    //Bucket name
    char *name;
    //Bucket storage size
    long *size;
    //Bucket status//status's available values: active, suspended
    char *status;
    //URL to access the bucket
    char *url;

    int response_code;

    qs_error_info_t error_info;

} qs_get_bucket_statistics_output_t;

// get_bucket_statisticsInput init function.
void release_get_bucket_statistics_output(qs_get_bucket_statistics_output_t
        * output);

typedef qs_default_output_s qs_head_bucket_output_t;

// head_bucketInput init function.
void release_head_bucket_output(qs_head_bucket_output_t * output);

typedef struct
{
    //Other object keys that share common prefixes

    qs_list_t *common_prefixes;
    //Delimiter that specified in request parameters
    char *delimiter;
    //Limit that specified in request parameters
    int *limit;
    //Marker that specified in request parameters
    char *marker;
    //Bucket name
    char *name;
    //The last key in uploads list
    char *next_key_marker;
    //The last upload_id in uploads list
    char *next_upload_id_marker;
    //Prefix that specified in request parameters
    char *prefix;
    //Multipart uploads

    qs_list_t *uploads;

    int response_code;

    qs_error_info_t error_info;

} qs_list_multipart_uploads_output_t;

// list_multipart_uploadsInput init function.
void release_list_multipart_uploads_output
(qs_list_multipart_uploads_output_t * output);

typedef struct
{
    //Other object keys that share common prefixes

    qs_list_t *common_prefixes;
    //Delimiter that specified in request parameters
    char *delimiter;
    //Object keys

    qs_list_t *keys;
    //Limit that specified in request parameters
    int *limit;
    //Marker that specified in request parameters
    char *marker;
    //Bucket name
    char *name;
    //The last key in keys list
    char *next_marker;
    //Bucket owner

    qs_owner_t *owner;
    //Prefix that specified in request parameters
    char *prefix;

    int response_code;

    qs_error_info_t error_info;

} qs_list_objects_output_t;

// list_objectsInput init function.
void release_list_objects_output(qs_list_objects_output_t * output);

typedef qs_default_output_s qs_put_bucket_output_t;

// put_bucketInput init function.
void release_put_bucket_output(qs_put_bucket_output_t * output);

typedef qs_default_output_s qs_put_bucket_acl_output_t;

// put_bucket_aclInput init function.
void release_put_bucket_acl_output(qs_put_bucket_acl_output_t * output);

typedef qs_default_output_s qs_put_bucket_cors_output_t;

// put_bucket_corsInput init function.
void release_put_bucket_cors_output(qs_put_bucket_cors_output_t * output);

typedef qs_default_output_s qs_put_bucket_external_mirror_output_t;

// put_bucket_external_mirrorInput init function.
void release_put_bucket_external_mirror_output
(qs_put_bucket_external_mirror_output_t * output);

typedef qs_default_output_s qs_put_bucket_policy_output_t;

// put_bucket_policyInput init function.
void release_put_bucket_policy_output(qs_put_bucket_policy_output_t *
                                      output);

typedef qs_default_output_s qs_abort_multipart_upload_output_t;

// abort_multipart_uploadInput init function.
void release_abort_multipart_upload_output
(qs_abort_multipart_upload_output_t * output);

typedef struct
{
    //Encryption algorithm of the object
    char *x_qs_encryption_customer_algorithm;

    int response_code;

    qs_error_info_t error_info;

} qs_complete_multipart_upload_output_t;

// complete_multipart_uploadInput init function.
void release_complete_multipart_upload_output
(qs_complete_multipart_upload_output_t * output);

typedef qs_default_output_s qs_delete_object_output_t;

// delete_objectInput init function.
void release_delete_object_output(qs_delete_object_output_t * output);

typedef struct
{
    //The Cache-Control general-header field is used to specify directives for caching mechanisms in both requests and responses.
    char *cache_control;
    //In a multipart/form-data body, the HTTP Content-Disposition general header is a header that can be used on the subpart of a multipart body to give information about the field it applies to.
    char *content_disposition;
    //The Content-Encoding entity header is used to compress the media-type.
    char *content_encoding;
    //The Content-Language entity header is used to describe the language(s) intended for the audience.
    char *content_language;
    //Object content length
    long *content_length;
    //Range of response data content
    char *content_range;
    //The Content-Type entity header is used to indicate the media type of the resource.
    char *content_type;
    //MD5sum of the object
    char *etag;
    //The Expires header contains the date/time after which the response is considered stale.
    char *expires;
    char *last_modified;
    //Encryption algorithm of the object
    char *x_qs_encryption_customer_algorithm;	// The response body

    int64_t *bufLength;

    void *bodybuf;

    int response_code;

    qs_error_info_t error_info;

} qs_get_object_output_t;

// get_objectInput init function.
void release_get_object_output(qs_get_object_output_t * output);

typedef struct
{
    //Object content length
    long *content_length;
    //Object content type
    char *content_type;
    //MD5sum of the object
    char *etag;
    char *last_modified;
    //Encryption algorithm of the object
    char *x_qs_encryption_customer_algorithm;

    int response_code;

    qs_error_info_t error_info;

} qs_head_object_output_t;

// head_objectInput init function.
void release_head_object_output(qs_head_object_output_t * output);

typedef struct
{
    //Object content length
    long *content_length;	// The response body

    int64_t *bufLength;

    void *bodybuf;

    int response_code;

    qs_error_info_t error_info;

} qs_image_process_output_t;

// image_processInput init function.
void release_image_process_output(qs_image_process_output_t * output);

typedef struct
{
    //Encryption algorithm of the object
    char *x_qs_encryption_customer_algorithm;
    //Bucket name
    char *bucket;
    //Object key
    char *key;
    //Object multipart upload ID
    char *upload_id;

    int response_code;

    qs_error_info_t error_info;

} qs_initiate_multipart_upload_output_t;

// initiate_multipart_uploadInput init function.
void release_initiate_multipart_upload_output
(qs_initiate_multipart_upload_output_t * output);

typedef struct
{
    //Object multipart count
    int *count;
    //Object parts

    qs_list_t *object_parts;

    int response_code;

    qs_error_info_t error_info;

} qs_list_multipart_output_t;

// list_multipartInput init function.
void release_list_multipart_output(qs_list_multipart_output_t * output);

typedef struct
{
    //Allowed headers
    char *access_control_allow_headers;
    //Allowed methods
    char *access_control_allow_methods;
    //Allowed origin
    char *access_control_allow_origin;
    //Expose headers
    char *access_control_expose_headers;
    //Max age
    char *access_control_max_age;

    int response_code;

    qs_error_info_t error_info;

} qs_options_object_output_t;

// options_objectInput init function.
void release_options_object_output(qs_options_object_output_t * output);

typedef struct
{
    //MD5sum of the object
    char *etag;
    //Encryption algorithm of the object
    char *x_qs_encryption_customer_algorithm;

    int response_code;

    qs_error_info_t error_info;

} qs_put_object_output_t;

// put_objectInput init function.
void release_put_object_output(qs_put_object_output_t * output);

typedef struct
{
    //MD5sum of the object
    char *etag;
    //Range of response data content
    char *x_qs_content_copy_range;
    //Encryption algorithm of the object
    char *x_qs_encryption_customer_algorithm;

    int response_code;

    qs_error_info_t error_info;

} qs_upload_multipart_output_t;

// upload_multipartInput init function.
void release_upload_multipart_output(qs_upload_multipart_output_t * output);	// list_buckets does Retrieve the bucket list.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/service/get.html
QsError QS_SDK_API qs_list_buckets(qs_list_buckets_input_t * input,
                                   qs_list_buckets_output_t * output,
                                   qs_context_handle context_hdl);

// delete_bucket does Delete a bucket.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/delete.html
QsError QS_SDK_API qs_delete_bucket(qs_delete_bucket_input_t * input,
                                    qs_delete_bucket_output_t * output,
                                    qs_context_handle context_hdl);

// delete_bucket_cors does Delete CORS information of the bucket.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/cors/delete_cors.html
QsError QS_SDK_API qs_delete_bucket_cors(qs_delete_bucket_cors_input_t *
        input,
        qs_delete_bucket_cors_output_t *
        output,
        qs_context_handle context_hdl);

// delete_bucket_external_mirror does Delete external mirror of the bucket.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/external_mirror/delete_external_mirror.html
QsError QS_SDK_API
qs_delete_bucket_external_mirror
(qs_delete_bucket_external_mirror_input_t * input,
 qs_delete_bucket_external_mirror_output_t * output,
 qs_context_handle context_hdl);

// delete_bucket_policy does Delete policy information of the bucket.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/policy/delete_policy.html
QsError QS_SDK_API qs_delete_bucket_policy(qs_delete_bucket_policy_input_t *
        input,
        qs_delete_bucket_policy_output_t
        * output,
        qs_context_handle context_hdl);

// delete_multiple_objects does Delete multiple objects from the bucket.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/delete_multiple.html
QsError QS_SDK_API
qs_delete_multiple_objects(qs_delete_multiple_objects_input_t * input,
                           qs_delete_multiple_objects_output_t * output,
                           qs_context_handle context_hdl);

// get_bucket_acl does Get ACL information of the bucket.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/get_acl.html
QsError QS_SDK_API qs_get_bucket_acl(qs_get_bucket_acl_input_t * input,
                                     qs_get_bucket_acl_output_t * output,
                                     qs_context_handle context_hdl);

// get_bucket_cors does Get CORS information of the bucket.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/cors/get_cors.html
QsError QS_SDK_API qs_get_bucket_cors(qs_get_bucket_cors_input_t * input,
                                      qs_get_bucket_cors_output_t * output,
                                      qs_context_handle context_hdl);

// get_bucket_external_mirror does Get external mirror of the bucket.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/external_mirror/get_external_mirror.html
QsError QS_SDK_API
qs_get_bucket_external_mirror(qs_get_bucket_external_mirror_input_t *
                              input,
                              qs_get_bucket_external_mirror_output_t *
                              output, qs_context_handle context_hdl);

// get_bucket_policy does Get policy information of the bucket.
// Documentation URL: https://https://docs.qingcloud.com/qingstor/api/bucket/policy/get_policy.html
QsError QS_SDK_API qs_get_bucket_policy(qs_get_bucket_policy_input_t *
                                        input,
                                        qs_get_bucket_policy_output_t *
                                        output,
                                        qs_context_handle context_hdl);

// get_bucket_statistics does Get statistics information of the bucket.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/get_stats.html
QsError QS_SDK_API qs_get_bucket_statistics(qs_get_bucket_statistics_input_t
        * input,
        qs_get_bucket_statistics_output_t
        * output,
        qs_context_handle context_hdl);

// head_bucket does Check whether the bucket exists and available.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/head.html
QsError QS_SDK_API qs_head_bucket(qs_head_bucket_input_t * input,
                                  qs_head_bucket_output_t * output,
                                  qs_context_handle context_hdl);

// list_multipart_uploads does List multipart uploads in the bucket.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/list_multipart_uploads.html
QsError QS_SDK_API
qs_list_multipart_uploads(qs_list_multipart_uploads_input_t * input,
                          qs_list_multipart_uploads_output_t * output,
                          qs_context_handle context_hdl);

// list_objects does Retrieve the object list in a bucket.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/get.html
QsError QS_SDK_API qs_list_objects(qs_list_objects_input_t * input,
                                   qs_list_objects_output_t * output,
                                   qs_context_handle context_hdl);

// put_bucket does Create a new bucket.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/put.html
QsError QS_SDK_API qs_put_bucket(qs_put_bucket_input_t * input,
                                 qs_put_bucket_output_t * output,
                                 qs_context_handle context_hdl);

// put_bucket_acl does Set ACL information of the bucket.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/put_acl.html
QsError QS_SDK_API qs_put_bucket_acl(qs_put_bucket_acl_input_t * input,
                                     qs_put_bucket_acl_output_t * output,
                                     qs_context_handle context_hdl);

// put_bucket_cors does Set CORS information of the bucket.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/cors/put_cors.html
QsError QS_SDK_API qs_put_bucket_cors(qs_put_bucket_cors_input_t * input,
                                      qs_put_bucket_cors_output_t * output,
                                      qs_context_handle context_hdl);

// put_bucket_external_mirror does Set external mirror of the bucket.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/external_mirror/put_external_mirror.html
QsError QS_SDK_API
qs_put_bucket_external_mirror(qs_put_bucket_external_mirror_input_t *
                              input,
                              qs_put_bucket_external_mirror_output_t *
                              output, qs_context_handle context_hdl);

// put_bucket_policy does Set policy information of the bucket.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/policy/put_policy.html
QsError QS_SDK_API qs_put_bucket_policy(qs_put_bucket_policy_input_t *
                                        input,
                                        qs_put_bucket_policy_output_t *
                                        output,
                                        qs_context_handle context_hdl);

// abort_multipart_upload does Abort multipart upload.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/object/abort_multipart_upload.html
QsError QS_SDK_API qs_abort_multipart_upload(char *objectKey,
        qs_abort_multipart_upload_input_t
        * input,
        qs_abort_multipart_upload_output_t
        * output,
        qs_context_handle context_hdl);

// complete_multipart_upload does Complete multipart upload.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/object/complete_multipart_upload.html
QsError QS_SDK_API qs_complete_multipart_upload(char *objectKey,
        qs_complete_multipart_upload_input_t
        * input,
        qs_complete_multipart_upload_output_t
        * output,
        qs_context_handle
        context_hdl);

// delete_object does Delete the object.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/object/delete.html
QsError QS_SDK_API qs_delete_object(char *objectKey,
                                    qs_delete_object_input_t * input,
                                    qs_delete_object_output_t * output,
                                    qs_context_handle context_hdl);

// get_object does Retrieve the object.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/object/get.html
QsError QS_SDK_API qs_get_object(char *objectKey,
                                 qs_get_object_input_t * input,
                                 qs_get_object_output_t * output,
                                 qs_context_handle context_hdl);

// head_object does Check whether the object exists and available.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/object/head.html
QsError QS_SDK_API qs_head_object(char *objectKey,
                                  qs_head_object_input_t * input,
                                  qs_head_object_output_t * output,
                                  qs_context_handle context_hdl);

// image_process does Image process with the action on the object
// Documentation URL: https://docs.qingcloud.com/qingstor/data_process/image_process/index.html
QsError QS_SDK_API qs_image_process(char *objectKey,
                                    qs_image_process_input_t * input,
                                    qs_image_process_output_t * output,
                                    qs_context_handle context_hdl);

// initiate_multipart_upload does Initial multipart upload on the object.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/object/initiate_multipart_upload.html
QsError QS_SDK_API qs_initiate_multipart_upload(char *objectKey,
        qs_initiate_multipart_upload_input_t
        * input,
        qs_initiate_multipart_upload_output_t
        * output,
        qs_context_handle
        context_hdl);

// list_multipart does List object parts.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/object/list_multipart.html
QsError QS_SDK_API qs_list_multipart(char *objectKey,
                                     qs_list_multipart_input_t * input,
                                     qs_list_multipart_output_t * output,
                                     qs_context_handle context_hdl);

// options_object does Check whether the object accepts a origin with method and header.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/object/options.html
QsError QS_SDK_API qs_options_object(char *objectKey,
                                     qs_options_object_input_t * input,
                                     qs_options_object_output_t * output,
                                     qs_context_handle context_hdl);

// put_object does Upload the object.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/object/put.html
QsError QS_SDK_API qs_put_object(char *objectKey,
                                 qs_put_object_input_t * input,
                                 qs_put_object_output_t * output,
                                 qs_context_handle context_hdl);

// upload_multipart does Upload object multipart.
// Documentation URL: https://docs.qingcloud.com/qingstor/api/object/multipart/upload_multipart.html
QsError QS_SDK_API qs_upload_multipart(char *objectKey,
                                       qs_upload_multipart_input_t * input,
                                       qs_upload_multipart_output_t *
                                       output,
                                       qs_context_handle context_hdl);

#ifdef  __cplusplus
}
#endif
