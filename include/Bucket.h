// +-------------------------------------------------------------------------
// | Copyright (C) 2017 Yunify, Inc.
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

#include <iostream>
#include <sstream>
#include <memory.h>
#include "QsSdkOption.h"
#include "Types.h"
#include "QsErrors.h"
#include "QsConfig.h"

#ifdef BUILD_C_STYLE_INTERFACE
#include "service_with_c_style/QingStorCStyle.h"
#endif							// BUILD_C_STYLE_INTERFACE

#define BASIC_FLAG 0x0
// Limits results to buckets that in the location'flag
#define SETTING_INPUT_LIST_BUCKETS_LOCATION_FLAG 0x1

// Buckets information'flag
#define SETTING_OUTPUT_LIST_BUCKETS_BUCKETS_FLAG 0x1

// Bucket count'flag
#define SETTING_OUTPUT_LIST_BUCKETS_COUNT_FLAG 0x2

// Object MD5sum'flag
#define SETTING_INPUT_DELETE_MULTIPLE_OBJECTS_CONTENT_MD5_FLAG 0x1

// A list of keys to delete'flag
#define SETTING_INPUT_DELETE_MULTIPLE_OBJECTS_OBJECTS_FLAG 0x2

// Whether to return the list of deleted objects'flag
#define SETTING_INPUT_DELETE_MULTIPLE_OBJECTS_QUIET_FLAG 0x4

// Error messages'flag
#define SETTING_OUTPUT_DELETE_MULTIPLE_OBJECTS_ERRORS_FLAG 0x1

// List of deleted objects'flag
#define SETTING_OUTPUT_DELETE_MULTIPLE_OBJECTS_DELETED_FLAG 0x2

// Bucket ACL rules'flag
#define SETTING_OUTPUT_GET_BUCKET_ACL_ACL_FLAG 0x1

// Bucket owner'flag
#define SETTING_OUTPUT_GET_BUCKET_ACL_OWNER_FLAG 0x2

// Bucket CORS rules'flag
#define SETTING_OUTPUT_GET_BUCKET_CORS_CORS_RULES_FLAG 0x1

// Source site url'flag
#define SETTING_OUTPUT_GET_BUCKET_EXTERNAL_MIRROR_SOURCE_SITE_FLAG 0x1

// Bucket policy statement'flag
#define SETTING_OUTPUT_GET_BUCKET_POLICY_STATEMENT_FLAG 0x1

// QingCloud Zone ID'flag
#define SETTING_OUTPUT_GET_BUCKET_STATISTICS_LOCATION_FLAG 0x1

// Bucket name'flag
#define SETTING_OUTPUT_GET_BUCKET_STATISTICS_NAME_FLAG 0x2

// Bucket storage size'flag
#define SETTING_OUTPUT_GET_BUCKET_STATISTICS_SIZE_FLAG 0x4

// Bucket status'flag
// Status's available values: active, suspended
#define SETTING_OUTPUT_GET_BUCKET_STATISTICS_STATUS_FLAG 0x8

// URL to access the bucket'flag
#define SETTING_OUTPUT_GET_BUCKET_STATISTICS_URL_FLAG 0x10

// Objects count in the bucket'flag
#define SETTING_OUTPUT_GET_BUCKET_STATISTICS_COUNT_FLAG 0x20

// Bucket created time'flag
#define SETTING_OUTPUT_GET_BUCKET_STATISTICS_CREATED_FLAG 0x40

// Limit results returned from the first key after key_marker sorted by alphabetical order'flag
#define SETTING_INPUT_LIST_MULTIPART_UPLOADS_KEY_MARKER_FLAG 0x1

// Limit results returned from the first uploading segment after upload_id_marker sorted by the time of upload_id'flag
#define SETTING_INPUT_LIST_MULTIPART_UPLOADS_UPLOAD_ID_MARKER_FLAG 0x2

// Results count limit'flag
#define SETTING_INPUT_LIST_MULTIPART_UPLOADS_LIMIT_FLAG 0x4

// Limits results to keys that begin with the prefix'flag
#define SETTING_INPUT_LIST_MULTIPART_UPLOADS_PREFIX_FLAG 0x8

// Put all keys that share a common prefix into a list'flag
#define SETTING_INPUT_LIST_MULTIPART_UPLOADS_DELIMITER_FLAG 0x10

// The last key in uploads list'flag
#define SETTING_OUTPUT_LIST_MULTIPART_UPLOADS_NEXT_KEY_MARKER_FLAG 0x1

// Delimiter that specified in request parameters'flag
#define SETTING_OUTPUT_LIST_MULTIPART_UPLOADS_DELIMITER_FLAG 0x2

// The last upload_id in uploads list'flag
#define SETTING_OUTPUT_LIST_MULTIPART_UPLOADS_NEXT_UPLOAD_ID_MARKER_FLAG 0x4

// Prefix that specified in request parameters'flag
#define SETTING_OUTPUT_LIST_MULTIPART_UPLOADS_PREFIX_FLAG 0x8

// Bucket name'flag
#define SETTING_OUTPUT_LIST_MULTIPART_UPLOADS_NAME_FLAG 0x10

// Multipart uploads'flag
#define SETTING_OUTPUT_LIST_MULTIPART_UPLOADS_UPLOADS_FLAG 0x20

// Limit that specified in request parameters'flag
#define SETTING_OUTPUT_LIST_MULTIPART_UPLOADS_LIMIT_FLAG 0x40

// Other object keys that share common prefixes'flag
#define SETTING_OUTPUT_LIST_MULTIPART_UPLOADS_COMMON_PREFIXES_FLAG 0x80

// Marker that specified in request parameters'flag
#define SETTING_OUTPUT_LIST_MULTIPART_UPLOADS_MARKER_FLAG 0x100

// Limits results to keys that begin with the prefix'flag
#define SETTING_INPUT_LIST_OBJECTS_PREFIX_FLAG 0x1

// Put all keys that share a common prefix into a list'flag
#define SETTING_INPUT_LIST_OBJECTS_DELIMITER_FLAG 0x2

// Limit results to keys that start at this marker'flag
#define SETTING_INPUT_LIST_OBJECTS_MARKER_FLAG 0x4

// Results count limit'flag
#define SETTING_INPUT_LIST_OBJECTS_LIMIT_FLAG 0x8

// The last key in keys list'flag
#define SETTING_OUTPUT_LIST_OBJECTS_NEXT_MARKER_FLAG 0x1

// Prefix that specified in request parameters'flag
#define SETTING_OUTPUT_LIST_OBJECTS_PREFIX_FLAG 0x2

// Bucket name'flag
#define SETTING_OUTPUT_LIST_OBJECTS_NAME_FLAG 0x4

// Bucket owner'flag
#define SETTING_OUTPUT_LIST_OBJECTS_OWNER_FLAG 0x8

// Limit that specified in request parameters'flag
#define SETTING_OUTPUT_LIST_OBJECTS_LIMIT_FLAG 0x10

// Delimiter that specified in request parameters'flag
#define SETTING_OUTPUT_LIST_OBJECTS_DELIMITER_FLAG 0x20

// Object keys'flag
#define SETTING_OUTPUT_LIST_OBJECTS_KEYS_FLAG 0x40

// Other object keys that share common prefixes'flag
#define SETTING_OUTPUT_LIST_OBJECTS_COMMON_PREFIXES_FLAG 0x80

// Marker that specified in request parameters'flag
#define SETTING_OUTPUT_LIST_OBJECTS_MARKER_FLAG 0x100

// Bucket ACL rules'flag
#define SETTING_INPUT_PUT_BUCKET_ACL_ACL_FLAG 0x1

// Bucket CORS rules'flag
#define SETTING_INPUT_PUT_BUCKET_CORS_CORS_RULES_FLAG 0x1

// Source site url'flag
#define SETTING_INPUT_PUT_BUCKET_EXTERNAL_MIRROR_SOURCE_SITE_FLAG 0x1

// Bucket policy statement'flag
#define SETTING_INPUT_PUT_BUCKET_POLICY_STATEMENT_FLAG 0x1

// Object multipart upload ID'flag
#define SETTING_INPUT_ABORT_MULTIPART_UPLOAD_UPLOAD_ID_FLAG 0x1

// Object multipart upload ID'flag
#define SETTING_INPUT_COMPLETE_MULTIPART_UPLOAD_UPLOAD_ID_FLAG 0x1

// Encryption key of the object'flag
#define SETTING_INPUT_COMPLETE_MULTIPART_UPLOAD_X_QS_ENCRYPTION_CUSTOMER_KEY_FLAG 0x2

// MD5sum of encryption key'flag
#define SETTING_INPUT_COMPLETE_MULTIPART_UPLOAD_X_QS_ENCRYPTION_CUSTOMER_KEY_MD5_FLAG 0x4

// MD5sum of the object part'flag
#define SETTING_INPUT_COMPLETE_MULTIPART_UPLOAD_ETAG_FLAG 0x8

// Encryption algorithm of the object'flag
#define SETTING_INPUT_COMPLETE_MULTIPART_UPLOAD_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG 0x10

// Object parts'flag
#define SETTING_INPUT_COMPLETE_MULTIPART_UPLOAD_OBJECT_PARTS_FLAG 0x20

// Encryption algorithm of the object'flag
#define SETTING_OUTPUT_COMPLETE_MULTIPART_UPLOAD_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG 0x1

// Specified the Cache-Control response header'flag
#define SETTING_INPUT_GET_OBJECT_RESPONSE_CACHE_CONTROL_FLAG 0x1

// Specified the Content-Type response header'flag
#define SETTING_INPUT_GET_OBJECT_RESPONSE_CONTENT_TYPE_FLAG 0x2

// Specified the Content-Language response header'flag
#define SETTING_INPUT_GET_OBJECT_RESPONSE_CONTENT_LANGUAGE_FLAG 0x4

// Specified the Content-Encoding response header'flag
#define SETTING_INPUT_GET_OBJECT_RESPONSE_CONTENT_ENCODING_FLAG 0x8

// Specified the Content-Disposition response header'flag
#define SETTING_INPUT_GET_OBJECT_RESPONSE_CONTENT_DISPOSITION_FLAG 0x10

// Specified the Expires response header'flag
#define SETTING_INPUT_GET_OBJECT_RESPONSE_EXPIRES_FLAG 0x20

// Encryption algorithm of the object'flag
#define SETTING_INPUT_GET_OBJECT_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG 0x40

// Encryption key of the object'flag
#define SETTING_INPUT_GET_OBJECT_X_QS_ENCRYPTION_CUSTOMER_KEY_FLAG 0x80

// MD5sum of encryption key'flag
#define SETTING_INPUT_GET_OBJECT_X_QS_ENCRYPTION_CUSTOMER_KEY_MD5_FLAG 0x100

// Specified range of the object'flag
#define SETTING_INPUT_GET_OBJECT_RANGE_FLAG 0x200

// Check whether the object has been modified'flag
#define SETTING_INPUT_GET_OBJECT_IF_MODIFIED_SINCE_FLAG 0x400

// Check whether the object has not been modified'flag
#define SETTING_INPUT_GET_OBJECT_IF_UNMODIFIED_SINCE_FLAG 0x800

// Check whether the ETag matches'flag
#define SETTING_INPUT_GET_OBJECT_IF_MATCH_FLAG 0x1000

// Check whether the ETag does not match'flag
#define SETTING_INPUT_GET_OBJECT_IF_NONE_MATCH_FLAG 0x2000

// The Content-Language entity header is used to describe the language(s) intended for the audience.'flag
#define SETTING_OUTPUT_GET_OBJECT_CONTENT_LANGUAGE_FLAG 0x1

// The Content-Type entity header is used to indicate the media type of the resource.'flag
#define SETTING_OUTPUT_GET_OBJECT_CONTENT_TYPE_FLAG 0x2

// The Cache-Control general-header field is used to specify directives for caching mechanisms in both requests and responses.'flag
#define SETTING_OUTPUT_GET_OBJECT_CACHE_CONTROL_FLAG 0x4

// Object content length'flag
#define SETTING_OUTPUT_GET_OBJECT_CONTENT_LENGTH_FLAG 0x8

// MD5sum of the object'flag
#define SETTING_OUTPUT_GET_OBJECT_ETAG_FLAG 0x10

// In a multipart/form-data body, the HTTP Content-Disposition general header is a header that can be used on the subpart of a multipart body to give information about the field it applies to.'flag
#define SETTING_OUTPUT_GET_OBJECT_CONTENT_DISPOSITION_FLAG 0x20

// Range of response data content'flag
#define SETTING_OUTPUT_GET_OBJECT_CONTENT_RANGE_FLAG 0x40

// The Expires header contains the date/time after which the response is considered stale.'flag
#define SETTING_OUTPUT_GET_OBJECT_EXPIRES_FLAG 0x80

// Encryption algorithm of the object'flag
#define SETTING_OUTPUT_GET_OBJECT_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG 0x100

// The Content-Encoding entity header is used to compress the media-type.'flag
#define SETTING_OUTPUT_GET_OBJECT_CONTENT_ENCODING_FLAG 0x200

#define SETTING_OUTPUT_GET_OBJECT_LAST_MODIFIED_FLAG 0x400

// Check whether the object has been modified'flag
#define SETTING_INPUT_HEAD_OBJECT_IF_MODIFIED_SINCE_FLAG 0x1

// Check whether the object has not been modified'flag
#define SETTING_INPUT_HEAD_OBJECT_IF_UNMODIFIED_SINCE_FLAG 0x2

// Check whether the ETag matches'flag
#define SETTING_INPUT_HEAD_OBJECT_IF_MATCH_FLAG 0x4

// Check whether the ETag does not match'flag
#define SETTING_INPUT_HEAD_OBJECT_IF_NONE_MATCH_FLAG 0x8

// Encryption algorithm of the object'flag
#define SETTING_INPUT_HEAD_OBJECT_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG 0x10

// Encryption key of the object'flag
#define SETTING_INPUT_HEAD_OBJECT_X_QS_ENCRYPTION_CUSTOMER_KEY_FLAG 0x20

// MD5sum of encryption key'flag
#define SETTING_INPUT_HEAD_OBJECT_X_QS_ENCRYPTION_CUSTOMER_KEY_MD5_FLAG 0x40

// MD5sum of the object'flag
#define SETTING_OUTPUT_HEAD_OBJECT_ETAG_FLAG 0x1

#define SETTING_OUTPUT_HEAD_OBJECT_LAST_MODIFIED_FLAG 0x2

// Encryption algorithm of the object'flag
#define SETTING_OUTPUT_HEAD_OBJECT_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG 0x4

// Object content length'flag
#define SETTING_OUTPUT_HEAD_OBJECT_CONTENT_LENGTH_FLAG 0x8

// Object content type'flag
#define SETTING_OUTPUT_HEAD_OBJECT_CONTENT_TYPE_FLAG 0x10

// Specified the Content-Language response header'flag
#define SETTING_INPUT_IMAGE_PROCESS_RESPONSE_CONTENT_LANGUAGE_FLAG 0x1

// Specified the Content-Encoding response header'flag
#define SETTING_INPUT_IMAGE_PROCESS_RESPONSE_CONTENT_ENCODING_FLAG 0x2

// Specified the Content-Disposition response header'flag
#define SETTING_INPUT_IMAGE_PROCESS_RESPONSE_CONTENT_DISPOSITION_FLAG 0x4

// Image process action'flag
#define SETTING_INPUT_IMAGE_PROCESS_ACTION_FLAG 0x8

// Specified the Expires response header'flag
#define SETTING_INPUT_IMAGE_PROCESS_RESPONSE_EXPIRES_FLAG 0x10

// Specified the Cache-Control response header'flag
#define SETTING_INPUT_IMAGE_PROCESS_RESPONSE_CACHE_CONTROL_FLAG 0x20

// Specified the Content-Type response header'flag
#define SETTING_INPUT_IMAGE_PROCESS_RESPONSE_CONTENT_TYPE_FLAG 0x40

// Check whether the object has been modified'flag
#define SETTING_INPUT_IMAGE_PROCESS_IF_MODIFIED_SINCE_FLAG 0x80

// Object content length'flag
#define SETTING_OUTPUT_IMAGE_PROCESS_CONTENT_LENGTH_FLAG 0x1

// Object content type'flag
#define SETTING_INPUT_INITIATE_MULTIPART_UPLOAD_CONTENT_TYPE_FLAG 0x1

// Encryption algorithm of the object'flag
#define SETTING_INPUT_INITIATE_MULTIPART_UPLOAD_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG 0x2

// Encryption key of the object'flag
#define SETTING_INPUT_INITIATE_MULTIPART_UPLOAD_X_QS_ENCRYPTION_CUSTOMER_KEY_FLAG 0x4

// MD5sum of encryption key'flag
#define SETTING_INPUT_INITIATE_MULTIPART_UPLOAD_X_QS_ENCRYPTION_CUSTOMER_KEY_MD5_FLAG 0x8

// Encryption algorithm of the object'flag
#define SETTING_OUTPUT_INITIATE_MULTIPART_UPLOAD_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG 0x1

// Bucket name'flag
#define SETTING_OUTPUT_INITIATE_MULTIPART_UPLOAD_BUCKET_FLAG 0x2

// Object key'flag
#define SETTING_OUTPUT_INITIATE_MULTIPART_UPLOAD_KEY_FLAG 0x4

// Object multipart upload ID'flag
#define SETTING_OUTPUT_INITIATE_MULTIPART_UPLOAD_UPLOAD_ID_FLAG 0x8

// Object multipart upload ID'flag
#define SETTING_INPUT_LIST_MULTIPART_UPLOAD_ID_FLAG 0x1

// Object multipart upload part number'flag
#define SETTING_INPUT_LIST_MULTIPART_PART_NUMBER_MARKER_FLAG 0x2

// Limit results count'flag
#define SETTING_INPUT_LIST_MULTIPART_LIMIT_FLAG 0x4

// Object multipart count'flag
#define SETTING_OUTPUT_LIST_MULTIPART_COUNT_FLAG 0x1

// Object parts'flag
#define SETTING_OUTPUT_LIST_MULTIPART_OBJECT_PARTS_FLAG 0x2

// Request origin'flag
#define SETTING_INPUT_OPTIONS_OBJECT_ORIGIN_FLAG 0x1

// Request method'flag
#define SETTING_INPUT_OPTIONS_OBJECT_ACCESS_CONTROL_REQUEST_METHOD_FLAG 0x2

// Request headers'flag
#define SETTING_INPUT_OPTIONS_OBJECT_ACCESS_CONTROL_REQUEST_HEADERS_FLAG 0x4

// Allowed headers'flag
#define SETTING_OUTPUT_OPTIONS_OBJECT_ACCESS_CONTROL_ALLOW_HEADERS_FLAG 0x1

// Allowed methods'flag
#define SETTING_OUTPUT_OPTIONS_OBJECT_ACCESS_CONTROL_ALLOW_METHODS_FLAG 0x2

// Allowed origin'flag
#define SETTING_OUTPUT_OPTIONS_OBJECT_ACCESS_CONTROL_ALLOW_ORIGIN_FLAG 0x4

// Expose headers'flag
#define SETTING_OUTPUT_OPTIONS_OBJECT_ACCESS_CONTROL_EXPOSE_HEADERS_FLAG 0x8

// Max age'flag
#define SETTING_OUTPUT_OPTIONS_OBJECT_ACCESS_CONTROL_MAX_AGE_FLAG 0x10

// Encryption algorithm of the object'flag
#define SETTING_INPUT_PUT_OBJECT_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG 0x1

// MD5sum of encryption key'flag
#define SETTING_INPUT_PUT_OBJECT_X_QS_ENCRYPTION_CUSTOMER_KEY_MD5_FLAG 0x2

// Copy source, format (/<bucket-name>/<object-key>)'flag
#define SETTING_INPUT_PUT_OBJECT_X_QS_COPY_SOURCE_FLAG 0x4

// Check whether the copy source matches'flag
#define SETTING_INPUT_PUT_OBJECT_X_QS_COPY_SOURCE_IF_MATCH_FLAG 0x8

// Fetch source, should be a valid url'flag
#define SETTING_INPUT_PUT_OBJECT_X_QS_FETCH_SOURCE_FLAG 0x10

// Object content size'flag
#define SETTING_INPUT_PUT_OBJECT_CONTENT_LENGTH_FLAG 0x20

// Object MD5sum'flag
#define SETTING_INPUT_PUT_OBJECT_CONTENT_MD5_FLAG 0x40

// Used to indicate that particular server behaviors are required by the client'flag
#define SETTING_INPUT_PUT_OBJECT_EXPECT_FLAG 0x80

// Check whether the copy source has been modified'flag
#define SETTING_INPUT_PUT_OBJECT_X_QS_COPY_SOURCE_IF_MODIFIED_SINCE_FLAG 0x100

// Check whether the copy source does not match'flag
#define SETTING_INPUT_PUT_OBJECT_X_QS_COPY_SOURCE_IF_NONE_MATCH_FLAG 0x200

// Encryption key of the object'flag
#define SETTING_INPUT_PUT_OBJECT_X_QS_ENCRYPTION_CUSTOMER_KEY_FLAG 0x400

// Encryption algorithm of the object'flag
#define SETTING_INPUT_PUT_OBJECT_X_QS_COPY_SOURCE_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG 0x800

// Move source, format (/<bucket-name>/<object-key>)'flag
#define SETTING_INPUT_PUT_OBJECT_X_QS_MOVE_SOURCE_FLAG 0x1000

// Object content type'flag
#define SETTING_INPUT_PUT_OBJECT_CONTENT_TYPE_FLAG 0x2000

// Check whether the copy source has not been modified'flag
#define SETTING_INPUT_PUT_OBJECT_X_QS_COPY_SOURCE_IF_UNMODIFIED_SINCE_FLAG 0x4000

// Encryption key of the object'flag
#define SETTING_INPUT_PUT_OBJECT_X_QS_COPY_SOURCE_ENCRYPTION_CUSTOMER_KEY_FLAG 0x8000

// MD5sum of encryption key'flag
#define SETTING_INPUT_PUT_OBJECT_X_QS_COPY_SOURCE_ENCRYPTION_CUSTOMER_KEY_MD5_FLAG 0x10000

// Check whether fetch target object has not been modified'flag
#define SETTING_INPUT_PUT_OBJECT_X_QS_FETCH_IF_UNMODIFIED_SINCE_FLAG 0x20000

// Encryption algorithm of the object'flag
#define SETTING_OUTPUT_PUT_OBJECT_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG 0x1

// MD5sum of the object'flag
#define SETTING_OUTPUT_PUT_OBJECT_ETAG_FLAG 0x2

// Object multipart upload ID'flag
#define SETTING_INPUT_UPLOAD_MULTIPART_UPLOAD_ID_FLAG 0x1

// Object multipart upload part number'flag
#define SETTING_INPUT_UPLOAD_MULTIPART_PART_NUMBER_FLAG 0x2

// Copy source, format (/<bucket-name>/<object-key>)'flag
#define SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_SOURCE_FLAG 0x4

// Check whether the copy source has been modified since the specified date'flag
#define SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_SOURCE_IF_MODIFIED_SINCE_FLAG 0x8

// Check whether the Etag of copy source does not matches the specified value'flag
#define SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_SOURCE_IF_NONE_MATCH_FLAG 0x10

// Object multipart content length'flag
#define SETTING_INPUT_UPLOAD_MULTIPART_CONTENT_LENGTH_FLAG 0x20

// Encryption key of the object'flag
#define SETTING_INPUT_UPLOAD_MULTIPART_X_QS_ENCRYPTION_CUSTOMER_KEY_FLAG 0x40

// Specify range of the source object'flag
#define SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_RANGE_FLAG 0x80

// Check whether the Etag of copy source matches the specified value'flag
#define SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_SOURCE_IF_MATCH_FLAG 0x100

// Encryption key of the object'flag
#define SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_SOURCE_ENCRYPTION_CUSTOMER_KEY_FLAG 0x200

// Object multipart content MD5sum'flag
#define SETTING_INPUT_UPLOAD_MULTIPART_CONTENT_MD5_FLAG 0x400

// Encryption algorithm of the object'flag
#define SETTING_INPUT_UPLOAD_MULTIPART_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG 0x800

// Encryption algorithm of the object'flag
#define SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_SOURCE_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG 0x1000

// MD5sum of encryption key'flag
#define SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_SOURCE_ENCRYPTION_CUSTOMER_KEY_MD5_FLAG 0x2000

// MD5sum of encryption key'flag
#define SETTING_INPUT_UPLOAD_MULTIPART_X_QS_ENCRYPTION_CUSTOMER_KEY_MD5_FLAG 0x4000

// Check whether the copy source has not been unmodified since the specified date'flag
#define SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_SOURCE_IF_UNMODIFIED_SINCE_FLAG 0x8000

// Range of response data content'flag
#define SETTING_OUTPUT_UPLOAD_MULTIPART_X_QS_CONTENT_COPY_RANGE_FLAG 0x1

// Encryption algorithm of the object'flag
#define SETTING_OUTPUT_UPLOAD_MULTIPART_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG 0x2

// MD5sum of the object'flag
#define SETTING_OUTPUT_UPLOAD_MULTIPART_ETAG_FLAG 0x4

namespace QingStor
{
// +--------------------------------------------------------------------
// |                     InputClassHeader
// +--------------------------------------------------------------------
// DeleteBucketInput presents input for DeleteBucket.
typedef QsInput DeleteBucketInput;
// DeleteBucketCORSInput presents input for DeleteBucketCORS.
typedef QsInput DeleteBucketCORSInput;
// DeleteBucketExternalMirrorInput presents input for DeleteBucketExternalMirror.
typedef QsInput DeleteBucketExternalMirrorInput;
// DeleteBucketPolicyInput presents input for DeleteBucketPolicy.
typedef QsInput DeleteBucketPolicyInput;
// DeleteMultipleObjectsInput presents input for DeleteMultipleObjects.
class QS_SDK_API DeleteMultipleObjectsInput:public QsInput
{
public:
    DeleteMultipleObjectsInput()
    {
    };

    inline bool CheckIfInputIsVaild()
    {
        int tmpFlag =
            BASIC_FLAG |
            SETTING_INPUT_DELETE_MULTIPLE_OBJECTS_CONTENT_MD5_FLAG |
            SETTING_INPUT_DELETE_MULTIPLE_OBJECTS_OBJECTS_FLAG;
        return (tmpFlag == (tmpFlag & m_settingFlag));
    };
    // Object MD5sum

    inline void SetContentMD5(std::string ContentMD5)
    {
        m_settingFlag |=
            SETTING_INPUT_DELETE_MULTIPLE_OBJECTS_CONTENT_MD5_FLAG;
        m_ContentMD5 = ContentMD5;
    };

    inline std::string GetContentMD5()
    {
        return m_ContentMD5;
    };

    // A list of keys to delete
#ifdef BUILD_C_STYLE_INTERFACE
    inline void SetObjects(qs_list_t * objects)
    {
        qs_key_item_t *item;
        qs_list_for_each_entry(qs_key_item_t, item, objects)
        {
            m_Objects.push_back(*item->content);
        }
    };
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetObjects(std::vector < KeyType > Objects)
    {
        m_settingFlag |= SETTING_INPUT_DELETE_MULTIPLE_OBJECTS_OBJECTS_FLAG;
        m_Objects = Objects;
    };

    inline std::vector < KeyType > GetObjects()
    {
        return m_Objects;
    };
    // Whether to return the list of deleted objects
#ifdef BUILD_C_STYLE_INTERFACE
    inline void SetQuiet(int *quiet)
    {
        m_Quiet = quiet;
    };
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetQuiet(bool Quiet)
    {
        m_settingFlag |= SETTING_INPUT_DELETE_MULTIPLE_OBJECTS_QUIET_FLAG;
        m_Quiet = Quiet;
    };

    inline bool GetQuiet()
    {
        return m_Quiet;
    };

private:
    // Object MD5sum
    std::string m_ContentMD5;	// Required

    // A list of keys to delete

    std::vector < KeyType > m_Objects;	// Required

    // Whether to return the list of deleted objects
    bool m_Quiet;

};
// GetBucketACLInput presents input for GetBucketACL.
typedef QsInput GetBucketACLInput;
// GetBucketCORSInput presents input for GetBucketCORS.
typedef QsInput GetBucketCORSInput;
// GetBucketExternalMirrorInput presents input for GetBucketExternalMirror.
typedef QsInput GetBucketExternalMirrorInput;
// GetBucketPolicyInput presents input for GetBucketPolicy.
typedef QsInput GetBucketPolicyInput;
// GetBucketStatisticsInput presents input for GetBucketStatistics.
typedef QsInput GetBucketStatisticsInput;
// HeadBucketInput presents input for HeadBucket.
typedef QsInput HeadBucketInput;
// ListMultipartUploadsInput presents input for ListMultipartUploads.
class QS_SDK_API ListMultipartUploadsInput:public QsInput
{
public:
    ListMultipartUploadsInput()
    {
    };

    inline bool CheckIfInputIsVaild()
    {
        int tmpFlag = BASIC_FLAG;
        return (tmpFlag == (tmpFlag & m_settingFlag));
    };
    // Put all keys that share a common prefix into a list

    inline void SetDelimiter(std::string Delimiter)
    {
        m_settingFlag |=
            SETTING_INPUT_LIST_MULTIPART_UPLOADS_DELIMITER_FLAG;
        m_Delimiter = Delimiter;
    };

    inline std::string GetDelimiter()
    {
        return m_Delimiter;
    };
    // Limit results returned from the first key after key_marker sorted by alphabetical order

    inline void SetKeyMarker(std::string KeyMarker)
    {
        m_settingFlag |=
            SETTING_INPUT_LIST_MULTIPART_UPLOADS_KEY_MARKER_FLAG;
        m_KeyMarker = KeyMarker;
    };

    inline std::string GetKeyMarker()
    {
        return m_KeyMarker;
    };
    // Results count limit

    inline void SetLimit(int Limit)
    {
        m_settingFlag |= SETTING_INPUT_LIST_MULTIPART_UPLOADS_LIMIT_FLAG;
        m_Limit = Limit;
    };

    inline int GetLimit()
    {
        return m_Limit;
    };
    // Limits results to keys that begin with the prefix

    inline void SetPrefix(std::string Prefix)
    {
        m_settingFlag |= SETTING_INPUT_LIST_MULTIPART_UPLOADS_PREFIX_FLAG;
        m_Prefix = Prefix;
    };

    inline std::string GetPrefix()
    {
        return m_Prefix;
    };
    // Limit results returned from the first uploading segment after upload_id_marker sorted by the time of upload_id

    inline void SetUploadIDMarker(std::string UploadIDMarker)
    {
        m_settingFlag |=
            SETTING_INPUT_LIST_MULTIPART_UPLOADS_UPLOAD_ID_MARKER_FLAG;
        m_UploadIDMarker = UploadIDMarker;
    };

    inline std::string GetUploadIDMarker()
    {
        return m_UploadIDMarker;
    };

private:

    // Put all keys that share a common prefix into a list
    std::string m_Delimiter;

    // Limit results returned from the first key after key_marker sorted by alphabetical order
    std::string m_KeyMarker;

    // Results count limit
    int m_Limit;

    // Limits results to keys that begin with the prefix
    std::string m_Prefix;

    // Limit results returned from the first uploading segment after upload_id_marker sorted by the time of upload_id
    std::string m_UploadIDMarker;

};
// ListObjectsInput presents input for ListObjects.
class QS_SDK_API ListObjectsInput:public QsInput
{
public:
    ListObjectsInput()
    {
    };

    inline bool CheckIfInputIsVaild()
    {
        int tmpFlag = BASIC_FLAG;
        return (tmpFlag == (tmpFlag & m_settingFlag));
    };
    // Put all keys that share a common prefix into a list

    inline void SetDelimiter(std::string Delimiter)
    {
        m_settingFlag |= SETTING_INPUT_LIST_OBJECTS_DELIMITER_FLAG;
        m_Delimiter = Delimiter;
    };

    inline std::string GetDelimiter()
    {
        return m_Delimiter;
    };
    // Results count limit

    inline void SetLimit(int Limit)
    {
        m_settingFlag |= SETTING_INPUT_LIST_OBJECTS_LIMIT_FLAG;
        m_Limit = Limit;
    };

    inline int GetLimit()
    {
        return m_Limit;
    };
    // Limit results to keys that start at this marker

    inline void SetMarker(std::string Marker)
    {
        m_settingFlag |= SETTING_INPUT_LIST_OBJECTS_MARKER_FLAG;
        m_Marker = Marker;
    };

    inline std::string GetMarker()
    {
        return m_Marker;
    };
    // Limits results to keys that begin with the prefix

    inline void SetPrefix(std::string Prefix)
    {
        m_settingFlag |= SETTING_INPUT_LIST_OBJECTS_PREFIX_FLAG;
        m_Prefix = Prefix;
    };

    inline std::string GetPrefix()
    {
        return m_Prefix;
    };

private:

    // Put all keys that share a common prefix into a list
    std::string m_Delimiter;

    // Results count limit
    int m_Limit;

    // Limit results to keys that start at this marker
    std::string m_Marker;

    // Limits results to keys that begin with the prefix
    std::string m_Prefix;

};
// PutBucketInput presents input for PutBucket.
typedef QsInput PutBucketInput;
// PutBucketACLInput presents input for PutBucketACL.
class QS_SDK_API PutBucketACLInput:public QsInput
{
public:
    PutBucketACLInput()
    {
    };

    inline bool CheckIfInputIsVaild()
    {
        int tmpFlag = BASIC_FLAG | SETTING_INPUT_PUT_BUCKET_ACL_ACL_FLAG;
        return (tmpFlag == (tmpFlag & m_settingFlag));
    };
    // Bucket ACL rules
#ifdef BUILD_C_STYLE_INTERFACE
    inline void SetACL(qs_list_t * acl)
    {
        qs_acl_item_t *item;
        qs_list_for_each_entry(qs_acl_item_t, item, acl)
        {
            m_ACL.push_back(*item->content);
        }
    };
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetACL(std::vector < ACLType > ACL)
    {
        m_settingFlag |= SETTING_INPUT_PUT_BUCKET_ACL_ACL_FLAG;
        m_ACL = ACL;
    };

    inline std::vector < ACLType > GetACL()
    {
        return m_ACL;
    };

private:
    // Bucket ACL rules

    std::vector < ACLType > m_ACL;	// Required

};
// PutBucketCORSInput presents input for PutBucketCORS.
class QS_SDK_API PutBucketCORSInput:public QsInput
{
public:
    PutBucketCORSInput()
    {
    };

    inline bool CheckIfInputIsVaild()
    {
        int tmpFlag =
            BASIC_FLAG | SETTING_INPUT_PUT_BUCKET_CORS_CORS_RULES_FLAG;
        return (tmpFlag == (tmpFlag & m_settingFlag));
    };
    // Bucket CORS rules
#ifdef BUILD_C_STYLE_INTERFACE
    inline void SetCORSRules(qs_list_t * cors_rules)
    {
        qs_cors_rule_item_t *item;
        qs_list_for_each_entry(qs_cors_rule_item_t, item, cors_rules)
        {
            m_CORSRules.push_back(*item->content);
        }
    };
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetCORSRules(std::vector < CORSRuleType > CORSRules)
    {
        m_settingFlag |= SETTING_INPUT_PUT_BUCKET_CORS_CORS_RULES_FLAG;
        m_CORSRules = CORSRules;
    };

    inline std::vector < CORSRuleType > GetCORSRules()
    {
        return m_CORSRules;
    };

private:
    // Bucket CORS rules

    std::vector < CORSRuleType > m_CORSRules;	// Required

};
// PutBucketExternalMirrorInput presents input for PutBucketExternalMirror.
class QS_SDK_API PutBucketExternalMirrorInput:public QsInput
{
public:
    PutBucketExternalMirrorInput()
    {
    };

    inline bool CheckIfInputIsVaild()
    {
        int tmpFlag =
            BASIC_FLAG |
            SETTING_INPUT_PUT_BUCKET_EXTERNAL_MIRROR_SOURCE_SITE_FLAG;
        return (tmpFlag == (tmpFlag & m_settingFlag));
    };
    // Source site url

    inline void SetSourceSite(std::string SourceSite)
    {
        m_settingFlag |=
            SETTING_INPUT_PUT_BUCKET_EXTERNAL_MIRROR_SOURCE_SITE_FLAG;
        m_SourceSite = SourceSite;
    };

    inline std::string GetSourceSite()
    {
        return m_SourceSite;
    };

private:
    // Source site url
    std::string m_SourceSite;	// Required

};
// PutBucketPolicyInput presents input for PutBucketPolicy.
class QS_SDK_API PutBucketPolicyInput:public QsInput
{
public:
    PutBucketPolicyInput()
    {
    };

    inline bool CheckIfInputIsVaild()
    {
        int tmpFlag =
            BASIC_FLAG | SETTING_INPUT_PUT_BUCKET_POLICY_STATEMENT_FLAG;
        return (tmpFlag == (tmpFlag & m_settingFlag));
    };
    // Bucket policy statement
#ifdef BUILD_C_STYLE_INTERFACE
    inline void SetStatement(qs_list_t * statement)
    {
        qs_statement_item_t *item;
        qs_list_for_each_entry(qs_statement_item_t, item, statement)
        {
            m_Statement.push_back(*item->content);
        }
    };
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetStatement(std::vector < StatementType > Statement)
    {
        m_settingFlag |= SETTING_INPUT_PUT_BUCKET_POLICY_STATEMENT_FLAG;
        m_Statement = Statement;
    };

    inline std::vector < StatementType > GetStatement()
    {
        return m_Statement;
    };

private:
    // Bucket policy statement

    std::vector < StatementType > m_Statement;	// Required

};
// +--------------------------------------------------------------------
// |                     InputClassHeader
// +--------------------------------------------------------------------
// AbortMultipartUploadInput presents input for AbortMultipartUpload.
class QS_SDK_API AbortMultipartUploadInput:public QsInput
{
public:
    AbortMultipartUploadInput()
    {
    };

    inline bool CheckIfInputIsVaild()
    {
        int tmpFlag =
            BASIC_FLAG |
            SETTING_INPUT_ABORT_MULTIPART_UPLOAD_UPLOAD_ID_FLAG;
        return (tmpFlag == (tmpFlag & m_settingFlag));
    };
    // Object multipart upload ID

    inline void SetUploadID(std::string UploadID)
    {
        m_settingFlag |=
            SETTING_INPUT_ABORT_MULTIPART_UPLOAD_UPLOAD_ID_FLAG;
        m_UploadID = UploadID;
    };

    inline std::string GetUploadID()
    {
        return m_UploadID;
    };

private:

    // Object multipart upload ID
    std::string m_UploadID;	// Required

};
// CompleteMultipartUploadInput presents input for CompleteMultipartUpload.
class QS_SDK_API CompleteMultipartUploadInput:public QsInput
{
public:
    CompleteMultipartUploadInput()
    {
    };

    inline bool CheckIfInputIsVaild()
    {
        int tmpFlag =
            BASIC_FLAG |
            SETTING_INPUT_COMPLETE_MULTIPART_UPLOAD_UPLOAD_ID_FLAG;
        return (tmpFlag == (tmpFlag & m_settingFlag));
    };
    // Object multipart upload ID

    inline void SetUploadID(std::string UploadID)
    {
        m_settingFlag |=
            SETTING_INPUT_COMPLETE_MULTIPART_UPLOAD_UPLOAD_ID_FLAG;
        m_UploadID = UploadID;
    };

    inline std::string GetUploadID()
    {
        return m_UploadID;
    };

    // MD5sum of the object part

    inline void SetETag(std::string ETag)
    {
        m_settingFlag |= SETTING_INPUT_COMPLETE_MULTIPART_UPLOAD_ETAG_FLAG;
        m_ETag = ETag;
    };

    inline std::string GetETag()
    {
        return m_ETag;
    };
    // Encryption algorithm of the object

    inline void SetXQSEncryptionCustomerAlgorithm(std::
            string
            XQSEncryptionCustomerAlgorithm)
    {
        m_settingFlag |=
            SETTING_INPUT_COMPLETE_MULTIPART_UPLOAD_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG;
        m_XQSEncryptionCustomerAlgorithm = XQSEncryptionCustomerAlgorithm;
    };

    inline std::string GetXQSEncryptionCustomerAlgorithm()
    {
        return m_XQSEncryptionCustomerAlgorithm;
    };
    // Encryption key of the object

    inline void SetXQSEncryptionCustomerKey(std::
                                            string XQSEncryptionCustomerKey)
    {
        m_settingFlag |=
            SETTING_INPUT_COMPLETE_MULTIPART_UPLOAD_X_QS_ENCRYPTION_CUSTOMER_KEY_FLAG;
        m_XQSEncryptionCustomerKey = XQSEncryptionCustomerKey;
    };

    inline std::string GetXQSEncryptionCustomerKey()
    {
        return m_XQSEncryptionCustomerKey;
    };
    // MD5sum of encryption key

    inline void SetXQSEncryptionCustomerKeyMD5(std::
            string
            XQSEncryptionCustomerKeyMD5)
    {
        m_settingFlag |=
            SETTING_INPUT_COMPLETE_MULTIPART_UPLOAD_X_QS_ENCRYPTION_CUSTOMER_KEY_MD5_FLAG;
        m_XQSEncryptionCustomerKeyMD5 = XQSEncryptionCustomerKeyMD5;
    };

    inline std::string GetXQSEncryptionCustomerKeyMD5()
    {
        return m_XQSEncryptionCustomerKeyMD5;
    };

    // Object parts
#ifdef BUILD_C_STYLE_INTERFACE
    inline void SetObjectParts(qs_list_t * object_parts)
    {
        qs_object_part_item_t *item;
        qs_list_for_each_entry(qs_object_part_item_t, item, object_parts)
        {
            m_ObjectParts.push_back(*item->content);
        }
    };
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetObjectParts(std::vector < ObjectPartType > ObjectParts)
    {
        m_settingFlag |=
            SETTING_INPUT_COMPLETE_MULTIPART_UPLOAD_OBJECT_PARTS_FLAG;
        m_ObjectParts = ObjectParts;
    };

    inline std::vector < ObjectPartType > GetObjectParts()
    {
        return m_ObjectParts;
    };

private:

    // Object multipart upload ID
    std::string m_UploadID;	// Required

    // MD5sum of the object part
    std::string m_ETag;

    // Encryption algorithm of the object
    std::string m_XQSEncryptionCustomerAlgorithm;

    // Encryption key of the object
    std::string m_XQSEncryptionCustomerKey;

    // MD5sum of encryption key
    std::string m_XQSEncryptionCustomerKeyMD5;

    // Object parts

    std::vector < ObjectPartType > m_ObjectParts;

};
// DeleteObjectInput presents input for DeleteObject.
typedef QsInput DeleteObjectInput;
// GetObjectInput presents input for GetObject.
class QS_SDK_API GetObjectInput:public QsInput
{
public:
    GetObjectInput()
    {
    };

    inline bool CheckIfInputIsVaild()
    {
        int tmpFlag = BASIC_FLAG;
        return (tmpFlag == (tmpFlag & m_settingFlag));
    };
    // Specified the Cache-Control response header

    inline void SetResponseCacheControl(std::string ResponseCacheControl)
    {
        m_settingFlag |=
            SETTING_INPUT_GET_OBJECT_RESPONSE_CACHE_CONTROL_FLAG;
        m_ResponseCacheControl = ResponseCacheControl;
    };

    inline std::string GetResponseCacheControl()
    {
        return m_ResponseCacheControl;
    };
    // Specified the Content-Disposition response header

    inline void SetResponseContentDisposition(std::
            string
            ResponseContentDisposition)
    {
        m_settingFlag |=
            SETTING_INPUT_GET_OBJECT_RESPONSE_CONTENT_DISPOSITION_FLAG;
        m_ResponseContentDisposition = ResponseContentDisposition;
    };

    inline std::string GetResponseContentDisposition()
    {
        return m_ResponseContentDisposition;
    };
    // Specified the Content-Encoding response header

    inline void SetResponseContentEncoding(std::
                                           string ResponseContentEncoding)
    {
        m_settingFlag |=
            SETTING_INPUT_GET_OBJECT_RESPONSE_CONTENT_ENCODING_FLAG;
        m_ResponseContentEncoding = ResponseContentEncoding;
    };

    inline std::string GetResponseContentEncoding()
    {
        return m_ResponseContentEncoding;
    };
    // Specified the Content-Language response header

    inline void SetResponseContentLanguage(std::
                                           string ResponseContentLanguage)
    {
        m_settingFlag |=
            SETTING_INPUT_GET_OBJECT_RESPONSE_CONTENT_LANGUAGE_FLAG;
        m_ResponseContentLanguage = ResponseContentLanguage;
    };

    inline std::string GetResponseContentLanguage()
    {
        return m_ResponseContentLanguage;
    };
    // Specified the Content-Type response header

    inline void SetResponseContentType(std::string ResponseContentType)
    {
        m_settingFlag |=
            SETTING_INPUT_GET_OBJECT_RESPONSE_CONTENT_TYPE_FLAG;
        m_ResponseContentType = ResponseContentType;
    };

    inline std::string GetResponseContentType()
    {
        return m_ResponseContentType;
    };
    // Specified the Expires response header

    inline void SetResponseExpires(std::string ResponseExpires)
    {
        m_settingFlag |= SETTING_INPUT_GET_OBJECT_RESPONSE_EXPIRES_FLAG;
        m_ResponseExpires = ResponseExpires;
    };

    inline std::string GetResponseExpires()
    {
        return m_ResponseExpires;
    };

    // Check whether the ETag matches

    inline void SetIfMatch(std::string IfMatch)
    {
        m_settingFlag |= SETTING_INPUT_GET_OBJECT_IF_MATCH_FLAG;
        m_IfMatch = IfMatch;
    };

    inline std::string GetIfMatch()
    {
        return m_IfMatch;
    };
    // Check whether the object has been modified
#ifdef BUILD_C_STYLE_INTERFACE
    inline void SetIfModifiedSince(char *if_modified_since)
    {
        m_IfModifiedSince = if_modified_since;
    };
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetIfModifiedSince(std::string IfModifiedSince)
    {
        m_settingFlag |= SETTING_INPUT_GET_OBJECT_IF_MODIFIED_SINCE_FLAG;
        m_IfModifiedSince = IfModifiedSince;
    };

    inline std::string GetIfModifiedSince()
    {
        return m_IfModifiedSince;
    };
    // Check whether the ETag does not match

    inline void SetIfNoneMatch(std::string IfNoneMatch)
    {
        m_settingFlag |= SETTING_INPUT_GET_OBJECT_IF_NONE_MATCH_FLAG;
        m_IfNoneMatch = IfNoneMatch;
    };

    inline std::string GetIfNoneMatch()
    {
        return m_IfNoneMatch;
    };
    // Check whether the object has not been modified
#ifdef BUILD_C_STYLE_INTERFACE
    inline void SetIfUnmodifiedSince(char *if_unmodified_since)
    {
        m_IfUnmodifiedSince = if_unmodified_since;
    };
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetIfUnmodifiedSince(std::string IfUnmodifiedSince)
    {
        m_settingFlag |= SETTING_INPUT_GET_OBJECT_IF_UNMODIFIED_SINCE_FLAG;
        m_IfUnmodifiedSince = IfUnmodifiedSince;
    };

    inline std::string GetIfUnmodifiedSince()
    {
        return m_IfUnmodifiedSince;
    };
    // Specified range of the object

    inline void SetRange(std::string Range)
    {
        m_settingFlag |= SETTING_INPUT_GET_OBJECT_RANGE_FLAG;
        m_Range = Range;
    };

    inline std::string GetRange()
    {
        return m_Range;
    };
    // Encryption algorithm of the object

    inline void SetXQSEncryptionCustomerAlgorithm(std::
            string
            XQSEncryptionCustomerAlgorithm)
    {
        m_settingFlag |=
            SETTING_INPUT_GET_OBJECT_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG;
        m_XQSEncryptionCustomerAlgorithm = XQSEncryptionCustomerAlgorithm;
    };

    inline std::string GetXQSEncryptionCustomerAlgorithm()
    {
        return m_XQSEncryptionCustomerAlgorithm;
    };
    // Encryption key of the object

    inline void SetXQSEncryptionCustomerKey(std::
                                            string XQSEncryptionCustomerKey)
    {
        m_settingFlag |=
            SETTING_INPUT_GET_OBJECT_X_QS_ENCRYPTION_CUSTOMER_KEY_FLAG;
        m_XQSEncryptionCustomerKey = XQSEncryptionCustomerKey;
    };

    inline std::string GetXQSEncryptionCustomerKey()
    {
        return m_XQSEncryptionCustomerKey;
    };
    // MD5sum of encryption key

    inline void SetXQSEncryptionCustomerKeyMD5(std::
            string
            XQSEncryptionCustomerKeyMD5)
    {
        m_settingFlag |=
            SETTING_INPUT_GET_OBJECT_X_QS_ENCRYPTION_CUSTOMER_KEY_MD5_FLAG;
        m_XQSEncryptionCustomerKeyMD5 = XQSEncryptionCustomerKeyMD5;
    };

    inline std::string GetXQSEncryptionCustomerKeyMD5()
    {
        return m_XQSEncryptionCustomerKeyMD5;
    };

private:

    // Specified the Cache-Control response header
    std::string m_ResponseCacheControl;

    // Specified the Content-Disposition response header
    std::string m_ResponseContentDisposition;

    // Specified the Content-Encoding response header
    std::string m_ResponseContentEncoding;

    // Specified the Content-Language response header
    std::string m_ResponseContentLanguage;

    // Specified the Content-Type response header
    std::string m_ResponseContentType;

    // Specified the Expires response header
    std::string m_ResponseExpires;

    // Check whether the ETag matches
    std::string m_IfMatch;

    // Check whether the object has been modified
    std::string m_IfModifiedSince;

    // Check whether the ETag does not match
    std::string m_IfNoneMatch;

    // Check whether the object has not been modified
    std::string m_IfUnmodifiedSince;

    // Specified range of the object
    std::string m_Range;

    // Encryption algorithm of the object
    std::string m_XQSEncryptionCustomerAlgorithm;

    // Encryption key of the object
    std::string m_XQSEncryptionCustomerKey;

    // MD5sum of encryption key
    std::string m_XQSEncryptionCustomerKeyMD5;

};
// HeadObjectInput presents input for HeadObject.
class QS_SDK_API HeadObjectInput:public QsInput
{
public:
    HeadObjectInput()
    {
    };

    inline bool CheckIfInputIsVaild()
    {
        int tmpFlag = BASIC_FLAG;
        return (tmpFlag == (tmpFlag & m_settingFlag));
    };
    // Check whether the ETag matches

    inline void SetIfMatch(std::string IfMatch)
    {
        m_settingFlag |= SETTING_INPUT_HEAD_OBJECT_IF_MATCH_FLAG;
        m_IfMatch = IfMatch;
    };

    inline std::string GetIfMatch()
    {
        return m_IfMatch;
    };
    // Check whether the object has been modified
#ifdef BUILD_C_STYLE_INTERFACE
    inline void SetIfModifiedSince(char *if_modified_since)
    {
        m_IfModifiedSince = if_modified_since;
    };
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetIfModifiedSince(std::string IfModifiedSince)
    {
        m_settingFlag |= SETTING_INPUT_HEAD_OBJECT_IF_MODIFIED_SINCE_FLAG;
        m_IfModifiedSince = IfModifiedSince;
    };

    inline std::string GetIfModifiedSince()
    {
        return m_IfModifiedSince;
    };
    // Check whether the ETag does not match

    inline void SetIfNoneMatch(std::string IfNoneMatch)
    {
        m_settingFlag |= SETTING_INPUT_HEAD_OBJECT_IF_NONE_MATCH_FLAG;
        m_IfNoneMatch = IfNoneMatch;
    };

    inline std::string GetIfNoneMatch()
    {
        return m_IfNoneMatch;
    };
    // Check whether the object has not been modified
#ifdef BUILD_C_STYLE_INTERFACE
    inline void SetIfUnmodifiedSince(char *if_unmodified_since)
    {
        m_IfUnmodifiedSince = if_unmodified_since;
    };
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetIfUnmodifiedSince(std::string IfUnmodifiedSince)
    {
        m_settingFlag |= SETTING_INPUT_HEAD_OBJECT_IF_UNMODIFIED_SINCE_FLAG;
        m_IfUnmodifiedSince = IfUnmodifiedSince;
    };

    inline std::string GetIfUnmodifiedSince()
    {
        return m_IfUnmodifiedSince;
    };
    // Encryption algorithm of the object

    inline void SetXQSEncryptionCustomerAlgorithm(std::
            string
            XQSEncryptionCustomerAlgorithm)
    {
        m_settingFlag |=
            SETTING_INPUT_HEAD_OBJECT_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG;
        m_XQSEncryptionCustomerAlgorithm = XQSEncryptionCustomerAlgorithm;
    };

    inline std::string GetXQSEncryptionCustomerAlgorithm()
    {
        return m_XQSEncryptionCustomerAlgorithm;
    };
    // Encryption key of the object

    inline void SetXQSEncryptionCustomerKey(std::
                                            string XQSEncryptionCustomerKey)
    {
        m_settingFlag |=
            SETTING_INPUT_HEAD_OBJECT_X_QS_ENCRYPTION_CUSTOMER_KEY_FLAG;
        m_XQSEncryptionCustomerKey = XQSEncryptionCustomerKey;
    };

    inline std::string GetXQSEncryptionCustomerKey()
    {
        return m_XQSEncryptionCustomerKey;
    };
    // MD5sum of encryption key

    inline void SetXQSEncryptionCustomerKeyMD5(std::
            string
            XQSEncryptionCustomerKeyMD5)
    {
        m_settingFlag |=
            SETTING_INPUT_HEAD_OBJECT_X_QS_ENCRYPTION_CUSTOMER_KEY_MD5_FLAG;
        m_XQSEncryptionCustomerKeyMD5 = XQSEncryptionCustomerKeyMD5;
    };

    inline std::string GetXQSEncryptionCustomerKeyMD5()
    {
        return m_XQSEncryptionCustomerKeyMD5;
    };

private:
    // Check whether the ETag matches
    std::string m_IfMatch;

    // Check whether the object has been modified
    std::string m_IfModifiedSince;

    // Check whether the ETag does not match
    std::string m_IfNoneMatch;

    // Check whether the object has not been modified
    std::string m_IfUnmodifiedSince;

    // Encryption algorithm of the object
    std::string m_XQSEncryptionCustomerAlgorithm;

    // Encryption key of the object
    std::string m_XQSEncryptionCustomerKey;

    // MD5sum of encryption key
    std::string m_XQSEncryptionCustomerKeyMD5;

};
// ImageProcessInput presents input for ImageProcess.
class QS_SDK_API ImageProcessInput:public QsInput
{
public:
    ImageProcessInput()
    {
    };

    inline bool CheckIfInputIsVaild()
    {
        int tmpFlag = BASIC_FLAG | SETTING_INPUT_IMAGE_PROCESS_ACTION_FLAG;
        return (tmpFlag == (tmpFlag & m_settingFlag));
    };
    // Image process action

    inline void SetAction(std::string Action)
    {
        m_settingFlag |= SETTING_INPUT_IMAGE_PROCESS_ACTION_FLAG;
        m_Action = Action;
    };

    inline std::string GetAction()
    {
        return m_Action;
    };
    // Specified the Cache-Control response header

    inline void SetResponseCacheControl(std::string ResponseCacheControl)
    {
        m_settingFlag |=
            SETTING_INPUT_IMAGE_PROCESS_RESPONSE_CACHE_CONTROL_FLAG;
        m_ResponseCacheControl = ResponseCacheControl;
    };

    inline std::string GetResponseCacheControl()
    {
        return m_ResponseCacheControl;
    };
    // Specified the Content-Disposition response header

    inline void SetResponseContentDisposition(std::
            string
            ResponseContentDisposition)
    {
        m_settingFlag |=
            SETTING_INPUT_IMAGE_PROCESS_RESPONSE_CONTENT_DISPOSITION_FLAG;
        m_ResponseContentDisposition = ResponseContentDisposition;
    };

    inline std::string GetResponseContentDisposition()
    {
        return m_ResponseContentDisposition;
    };
    // Specified the Content-Encoding response header

    inline void SetResponseContentEncoding(std::
                                           string ResponseContentEncoding)
    {
        m_settingFlag |=
            SETTING_INPUT_IMAGE_PROCESS_RESPONSE_CONTENT_ENCODING_FLAG;
        m_ResponseContentEncoding = ResponseContentEncoding;
    };

    inline std::string GetResponseContentEncoding()
    {
        return m_ResponseContentEncoding;
    };
    // Specified the Content-Language response header

    inline void SetResponseContentLanguage(std::
                                           string ResponseContentLanguage)
    {
        m_settingFlag |=
            SETTING_INPUT_IMAGE_PROCESS_RESPONSE_CONTENT_LANGUAGE_FLAG;
        m_ResponseContentLanguage = ResponseContentLanguage;
    };

    inline std::string GetResponseContentLanguage()
    {
        return m_ResponseContentLanguage;
    };
    // Specified the Content-Type response header

    inline void SetResponseContentType(std::string ResponseContentType)
    {
        m_settingFlag |=
            SETTING_INPUT_IMAGE_PROCESS_RESPONSE_CONTENT_TYPE_FLAG;
        m_ResponseContentType = ResponseContentType;
    };

    inline std::string GetResponseContentType()
    {
        return m_ResponseContentType;
    };
    // Specified the Expires response header

    inline void SetResponseExpires(std::string ResponseExpires)
    {
        m_settingFlag |= SETTING_INPUT_IMAGE_PROCESS_RESPONSE_EXPIRES_FLAG;
        m_ResponseExpires = ResponseExpires;
    };

    inline std::string GetResponseExpires()
    {
        return m_ResponseExpires;
    };

    // Check whether the object has been modified
#ifdef BUILD_C_STYLE_INTERFACE
    inline void SetIfModifiedSince(char *if_modified_since)
    {
        m_IfModifiedSince = if_modified_since;
    };
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetIfModifiedSince(std::string IfModifiedSince)
    {
        m_settingFlag |= SETTING_INPUT_IMAGE_PROCESS_IF_MODIFIED_SINCE_FLAG;
        m_IfModifiedSince = IfModifiedSince;
    };

    inline std::string GetIfModifiedSince()
    {
        return m_IfModifiedSince;
    };

private:

    // Image process action
    std::string m_Action;	// Required

    // Specified the Cache-Control response header
    std::string m_ResponseCacheControl;

    // Specified the Content-Disposition response header
    std::string m_ResponseContentDisposition;

    // Specified the Content-Encoding response header
    std::string m_ResponseContentEncoding;

    // Specified the Content-Language response header
    std::string m_ResponseContentLanguage;

    // Specified the Content-Type response header
    std::string m_ResponseContentType;

    // Specified the Expires response header
    std::string m_ResponseExpires;

    // Check whether the object has been modified
    std::string m_IfModifiedSince;

};
// InitiateMultipartUploadInput presents input for InitiateMultipartUpload.
class QS_SDK_API InitiateMultipartUploadInput:public QsInput
{
public:
    InitiateMultipartUploadInput()
    {
    };

    inline bool CheckIfInputIsVaild()
    {
        int tmpFlag = BASIC_FLAG;
        return (tmpFlag == (tmpFlag & m_settingFlag));
    };
    // Object content type

    inline void SetContentType(std::string ContentType)
    {
        m_settingFlag |=
            SETTING_INPUT_INITIATE_MULTIPART_UPLOAD_CONTENT_TYPE_FLAG;
        m_ContentType = ContentType;
    };

    inline std::string GetContentType()
    {
        return m_ContentType;
    };
    // Encryption algorithm of the object

    inline void SetXQSEncryptionCustomerAlgorithm(std::
            string
            XQSEncryptionCustomerAlgorithm)
    {
        m_settingFlag |=
            SETTING_INPUT_INITIATE_MULTIPART_UPLOAD_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG;
        m_XQSEncryptionCustomerAlgorithm = XQSEncryptionCustomerAlgorithm;
    };

    inline std::string GetXQSEncryptionCustomerAlgorithm()
    {
        return m_XQSEncryptionCustomerAlgorithm;
    };
    // Encryption key of the object

    inline void SetXQSEncryptionCustomerKey(std::
                                            string XQSEncryptionCustomerKey)
    {
        m_settingFlag |=
            SETTING_INPUT_INITIATE_MULTIPART_UPLOAD_X_QS_ENCRYPTION_CUSTOMER_KEY_FLAG;
        m_XQSEncryptionCustomerKey = XQSEncryptionCustomerKey;
    };

    inline std::string GetXQSEncryptionCustomerKey()
    {
        return m_XQSEncryptionCustomerKey;
    };
    // MD5sum of encryption key

    inline void SetXQSEncryptionCustomerKeyMD5(std::
            string
            XQSEncryptionCustomerKeyMD5)
    {
        m_settingFlag |=
            SETTING_INPUT_INITIATE_MULTIPART_UPLOAD_X_QS_ENCRYPTION_CUSTOMER_KEY_MD5_FLAG;
        m_XQSEncryptionCustomerKeyMD5 = XQSEncryptionCustomerKeyMD5;
    };

    inline std::string GetXQSEncryptionCustomerKeyMD5()
    {
        return m_XQSEncryptionCustomerKeyMD5;
    };

private:
    // Object content type
    std::string m_ContentType;

    // Encryption algorithm of the object
    std::string m_XQSEncryptionCustomerAlgorithm;

    // Encryption key of the object
    std::string m_XQSEncryptionCustomerKey;

    // MD5sum of encryption key
    std::string m_XQSEncryptionCustomerKeyMD5;

};
// ListMultipartInput presents input for ListMultipart.
class QS_SDK_API ListMultipartInput:public QsInput
{
public:
    ListMultipartInput()
    {
    };

    inline bool CheckIfInputIsVaild()
    {
        int tmpFlag =
            BASIC_FLAG | SETTING_INPUT_LIST_MULTIPART_UPLOAD_ID_FLAG;
        return (tmpFlag == (tmpFlag & m_settingFlag));
    };
    // Limit results count

    inline void SetLimit(int Limit)
    {
        m_settingFlag |= SETTING_INPUT_LIST_MULTIPART_LIMIT_FLAG;
        m_Limit = Limit;
    };

    inline int GetLimit()
    {
        return m_Limit;
    };
    // Object multipart upload part number

    inline void SetPartNumberMarker(int PartNumberMarker)
    {
        m_settingFlag |=
            SETTING_INPUT_LIST_MULTIPART_PART_NUMBER_MARKER_FLAG;
        m_PartNumberMarker = PartNumberMarker;
    };

    inline int GetPartNumberMarker()
    {
        return m_PartNumberMarker;
    };
    // Object multipart upload ID

    inline void SetUploadID(std::string UploadID)
    {
        m_settingFlag |= SETTING_INPUT_LIST_MULTIPART_UPLOAD_ID_FLAG;
        m_UploadID = UploadID;
    };

    inline std::string GetUploadID()
    {
        return m_UploadID;
    };

private:

    // Limit results count
    int m_Limit;

    // Object multipart upload part number
    int m_PartNumberMarker;

    // Object multipart upload ID
    std::string m_UploadID;	// Required

};
// OptionsObjectInput presents input for OptionsObject.
class QS_SDK_API OptionsObjectInput:public QsInput
{
public:
    OptionsObjectInput()
    {
    };

    inline bool CheckIfInputIsVaild()
    {
        int tmpFlag =
            BASIC_FLAG |
            SETTING_INPUT_OPTIONS_OBJECT_ACCESS_CONTROL_REQUEST_METHOD_FLAG
            | SETTING_INPUT_OPTIONS_OBJECT_ORIGIN_FLAG;
        return (tmpFlag == (tmpFlag & m_settingFlag));
    };
    // Request headers

    inline void SetAccessControlRequestHeaders(std::
            string
            AccessControlRequestHeaders)
    {
        m_settingFlag |=
            SETTING_INPUT_OPTIONS_OBJECT_ACCESS_CONTROL_REQUEST_HEADERS_FLAG;
        m_AccessControlRequestHeaders = AccessControlRequestHeaders;
    };

    inline std::string GetAccessControlRequestHeaders()
    {
        return m_AccessControlRequestHeaders;
    };
    // Request method

    inline void SetAccessControlRequestMethod(std::
            string
            AccessControlRequestMethod)
    {
        m_settingFlag |=
            SETTING_INPUT_OPTIONS_OBJECT_ACCESS_CONTROL_REQUEST_METHOD_FLAG;
        m_AccessControlRequestMethod = AccessControlRequestMethod;
    };

    inline std::string GetAccessControlRequestMethod()
    {
        return m_AccessControlRequestMethod;
    };
    // Request origin

    inline void SetOrigin(std::string Origin)
    {
        m_settingFlag |= SETTING_INPUT_OPTIONS_OBJECT_ORIGIN_FLAG;
        m_Origin = Origin;
    };

    inline std::string GetOrigin()
    {
        return m_Origin;
    };

private:
    // Request headers
    std::string m_AccessControlRequestHeaders;

    // Request method
    std::string m_AccessControlRequestMethod;	// Required

    // Request origin
    std::string m_Origin;	// Required

};
// PutObjectInput presents input for PutObject.
class QS_SDK_API PutObjectInput:public QsInput
{
public:
    PutObjectInput():m_streambody(NULL)
    {
    };

    inline bool CheckIfInputIsVaild()
    {
        int tmpFlag =
            BASIC_FLAG | SETTING_INPUT_PUT_OBJECT_CONTENT_LENGTH_FLAG;
        return (tmpFlag == (tmpFlag & m_settingFlag));
    };
    // Object content size

    inline void SetContentLength(int64_t ContentLength)
    {
        m_settingFlag |= SETTING_INPUT_PUT_OBJECT_CONTENT_LENGTH_FLAG;
        m_ContentLength = ContentLength;
    };

    inline int64_t GetContentLength()
    {
        return m_ContentLength;
    };
    // Object MD5sum

    inline void SetContentMD5(std::string ContentMD5)
    {
        m_settingFlag |= SETTING_INPUT_PUT_OBJECT_CONTENT_MD5_FLAG;
        m_ContentMD5 = ContentMD5;
    };

    inline std::string GetContentMD5()
    {
        return m_ContentMD5;
    };
    // Object content type

    inline void SetContentType(std::string ContentType)
    {
        m_settingFlag |= SETTING_INPUT_PUT_OBJECT_CONTENT_TYPE_FLAG;
        m_ContentType = ContentType;
    };

    inline std::string GetContentType()
    {
        return m_ContentType;
    };
    // Used to indicate that particular server behaviors are required by the client

    inline void SetExpect(std::string Expect)
    {
        m_settingFlag |= SETTING_INPUT_PUT_OBJECT_EXPECT_FLAG;
        m_Expect = Expect;
    };

    inline std::string GetExpect()
    {
        return m_Expect;
    };
    // Copy source, format (/<bucket-name>/<object-key>)

    inline void SetXQSCopySource(std::string XQSCopySource)
    {
        m_settingFlag |= SETTING_INPUT_PUT_OBJECT_X_QS_COPY_SOURCE_FLAG;
        m_XQSCopySource = XQSCopySource;
    };

    inline std::string GetXQSCopySource()
    {
        return m_XQSCopySource;
    };
    // Encryption algorithm of the object

    inline void SetXQSCopySourceEncryptionCustomerAlgorithm(std::
            string
            XQSCopySourceEncryptionCustomerAlgorithm)
    {
        m_settingFlag |=
            SETTING_INPUT_PUT_OBJECT_X_QS_COPY_SOURCE_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG;
        m_XQSCopySourceEncryptionCustomerAlgorithm =
            XQSCopySourceEncryptionCustomerAlgorithm;
    };

    inline std::string GetXQSCopySourceEncryptionCustomerAlgorithm()
    {
        return m_XQSCopySourceEncryptionCustomerAlgorithm;
    };
    // Encryption key of the object

    inline void SetXQSCopySourceEncryptionCustomerKey(std::
            string
            XQSCopySourceEncryptionCustomerKey)
    {
        m_settingFlag |=
            SETTING_INPUT_PUT_OBJECT_X_QS_COPY_SOURCE_ENCRYPTION_CUSTOMER_KEY_FLAG;
        m_XQSCopySourceEncryptionCustomerKey =
            XQSCopySourceEncryptionCustomerKey;
    };

    inline std::string GetXQSCopySourceEncryptionCustomerKey()
    {
        return m_XQSCopySourceEncryptionCustomerKey;
    };
    // MD5sum of encryption key

    inline void SetXQSCopySourceEncryptionCustomerKeyMD5(std::
            string
            XQSCopySourceEncryptionCustomerKeyMD5)
    {
        m_settingFlag |=
            SETTING_INPUT_PUT_OBJECT_X_QS_COPY_SOURCE_ENCRYPTION_CUSTOMER_KEY_MD5_FLAG;
        m_XQSCopySourceEncryptionCustomerKeyMD5 =
            XQSCopySourceEncryptionCustomerKeyMD5;
    };

    inline std::string GetXQSCopySourceEncryptionCustomerKeyMD5()
    {
        return m_XQSCopySourceEncryptionCustomerKeyMD5;
    };
    // Check whether the copy source matches

    inline void SetXQSCopySourceIfMatch(std::string XQSCopySourceIfMatch)
    {
        m_settingFlag |=
            SETTING_INPUT_PUT_OBJECT_X_QS_COPY_SOURCE_IF_MATCH_FLAG;
        m_XQSCopySourceIfMatch = XQSCopySourceIfMatch;
    };

    inline std::string GetXQSCopySourceIfMatch()
    {
        return m_XQSCopySourceIfMatch;
    };
    // Check whether the copy source has been modified
#ifdef BUILD_C_STYLE_INTERFACE
    inline void SetXQSCopySourceIfModifiedSince(char
            *x_qs_copy_source_if_modified_since)
    {
        m_XQSCopySourceIfModifiedSince = x_qs_copy_source_if_modified_since;
    };
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetXQSCopySourceIfModifiedSince(std::
            string
            XQSCopySourceIfModifiedSince)
    {
        m_settingFlag |=
            SETTING_INPUT_PUT_OBJECT_X_QS_COPY_SOURCE_IF_MODIFIED_SINCE_FLAG;
        m_XQSCopySourceIfModifiedSince = XQSCopySourceIfModifiedSince;
    };

    inline std::string GetXQSCopySourceIfModifiedSince()
    {
        return m_XQSCopySourceIfModifiedSince;
    };
    // Check whether the copy source does not match

    inline void SetXQSCopySourceIfNoneMatch(std::
                                            string XQSCopySourceIfNoneMatch)
    {
        m_settingFlag |=
            SETTING_INPUT_PUT_OBJECT_X_QS_COPY_SOURCE_IF_NONE_MATCH_FLAG;
        m_XQSCopySourceIfNoneMatch = XQSCopySourceIfNoneMatch;
    };

    inline std::string GetXQSCopySourceIfNoneMatch()
    {
        return m_XQSCopySourceIfNoneMatch;
    };
    // Check whether the copy source has not been modified
#ifdef BUILD_C_STYLE_INTERFACE
    inline void SetXQSCopySourceIfUnmodifiedSince(char
            *x_qs_copy_source_if_unmodified_since)
    {
        m_XQSCopySourceIfUnmodifiedSince =
            x_qs_copy_source_if_unmodified_since;
    };
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetXQSCopySourceIfUnmodifiedSince(std::
            string
            XQSCopySourceIfUnmodifiedSince)
    {
        m_settingFlag |=
            SETTING_INPUT_PUT_OBJECT_X_QS_COPY_SOURCE_IF_UNMODIFIED_SINCE_FLAG;
        m_XQSCopySourceIfUnmodifiedSince = XQSCopySourceIfUnmodifiedSince;
    };

    inline std::string GetXQSCopySourceIfUnmodifiedSince()
    {
        return m_XQSCopySourceIfUnmodifiedSince;
    };
    // Encryption algorithm of the object

    inline void SetXQSEncryptionCustomerAlgorithm(std::
            string
            XQSEncryptionCustomerAlgorithm)
    {
        m_settingFlag |=
            SETTING_INPUT_PUT_OBJECT_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG;
        m_XQSEncryptionCustomerAlgorithm = XQSEncryptionCustomerAlgorithm;
    };

    inline std::string GetXQSEncryptionCustomerAlgorithm()
    {
        return m_XQSEncryptionCustomerAlgorithm;
    };
    // Encryption key of the object

    inline void SetXQSEncryptionCustomerKey(std::
                                            string XQSEncryptionCustomerKey)
    {
        m_settingFlag |=
            SETTING_INPUT_PUT_OBJECT_X_QS_ENCRYPTION_CUSTOMER_KEY_FLAG;
        m_XQSEncryptionCustomerKey = XQSEncryptionCustomerKey;
    };

    inline std::string GetXQSEncryptionCustomerKey()
    {
        return m_XQSEncryptionCustomerKey;
    };
    // MD5sum of encryption key

    inline void SetXQSEncryptionCustomerKeyMD5(std::
            string
            XQSEncryptionCustomerKeyMD5)
    {
        m_settingFlag |=
            SETTING_INPUT_PUT_OBJECT_X_QS_ENCRYPTION_CUSTOMER_KEY_MD5_FLAG;
        m_XQSEncryptionCustomerKeyMD5 = XQSEncryptionCustomerKeyMD5;
    };

    inline std::string GetXQSEncryptionCustomerKeyMD5()
    {
        return m_XQSEncryptionCustomerKeyMD5;
    };
    // Check whether fetch target object has not been modified
#ifdef BUILD_C_STYLE_INTERFACE
    inline void SetXQSFetchIfUnmodifiedSince(char
            *x_qs_fetch_if_unmodified_since)
    {
        m_XQSFetchIfUnmodifiedSince = x_qs_fetch_if_unmodified_since;
    };
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetXQSFetchIfUnmodifiedSince(std::
            string
            XQSFetchIfUnmodifiedSince)
    {
        m_settingFlag |=
            SETTING_INPUT_PUT_OBJECT_X_QS_FETCH_IF_UNMODIFIED_SINCE_FLAG;
        m_XQSFetchIfUnmodifiedSince = XQSFetchIfUnmodifiedSince;
    };

    inline std::string GetXQSFetchIfUnmodifiedSince()
    {
        return m_XQSFetchIfUnmodifiedSince;
    };
    // Fetch source, should be a valid url

    inline void SetXQSFetchSource(std::string XQSFetchSource)
    {
        m_settingFlag |= SETTING_INPUT_PUT_OBJECT_X_QS_FETCH_SOURCE_FLAG;
        m_XQSFetchSource = XQSFetchSource;
    };

    inline std::string GetXQSFetchSource()
    {
        return m_XQSFetchSource;
    };
    // Move source, format (/<bucket-name>/<object-key>)

    inline void SetXQSMoveSource(std::string XQSMoveSource)
    {
        m_settingFlag |= SETTING_INPUT_PUT_OBJECT_X_QS_MOVE_SOURCE_FLAG;
        m_XQSMoveSource = XQSMoveSource;
    };

    inline std::string GetXQSMoveSource()
    {
        return m_XQSMoveSource;
    };

    std::iostream * GetBody()
    {
        return m_streambody;
    };
    void SetBody(std::iostream * streambody)
    {
        m_streambody = streambody;
    };
private:
    // Object content size
    int64_t m_ContentLength;	// Required

    // Object MD5sum
    std::string m_ContentMD5;

    // Object content type
    std::string m_ContentType;

    // Used to indicate that particular server behaviors are required by the client
    std::string m_Expect;

    // Copy source, format (/<bucket-name>/<object-key>)
    std::string m_XQSCopySource;

    // Encryption algorithm of the object
    std::string m_XQSCopySourceEncryptionCustomerAlgorithm;

    // Encryption key of the object
    std::string m_XQSCopySourceEncryptionCustomerKey;

    // MD5sum of encryption key
    std::string m_XQSCopySourceEncryptionCustomerKeyMD5;

    // Check whether the copy source matches
    std::string m_XQSCopySourceIfMatch;

    // Check whether the copy source has been modified
    std::string m_XQSCopySourceIfModifiedSince;

    // Check whether the copy source does not match
    std::string m_XQSCopySourceIfNoneMatch;

    // Check whether the copy source has not been modified
    std::string m_XQSCopySourceIfUnmodifiedSince;

    // Encryption algorithm of the object
    std::string m_XQSEncryptionCustomerAlgorithm;

    // Encryption key of the object
    std::string m_XQSEncryptionCustomerKey;

    // MD5sum of encryption key
    std::string m_XQSEncryptionCustomerKeyMD5;

    // Check whether fetch target object has not been modified
    std::string m_XQSFetchIfUnmodifiedSince;

    // Fetch source, should be a valid url
    std::string m_XQSFetchSource;

    // Move source, format (/<bucket-name>/<object-key>)
    std::string m_XQSMoveSource;

    std::iostream * m_streambody;
};
// UploadMultipartInput presents input for UploadMultipart.
class QS_SDK_API UploadMultipartInput:public QsInput
{
public:
    UploadMultipartInput():m_streambody(NULL)
    {
    };

    inline bool CheckIfInputIsVaild()
    {
        int tmpFlag =
            BASIC_FLAG | SETTING_INPUT_UPLOAD_MULTIPART_PART_NUMBER_FLAG |
            SETTING_INPUT_UPLOAD_MULTIPART_UPLOAD_ID_FLAG;
        return (tmpFlag == (tmpFlag & m_settingFlag));
    };
    // Object multipart upload part number

    inline void SetPartNumber(int PartNumber)
    {
        m_settingFlag |= SETTING_INPUT_UPLOAD_MULTIPART_PART_NUMBER_FLAG;
        m_PartNumber = PartNumber;
    };

    inline int GetPartNumber()
    {
        return m_PartNumber;
    };
    // Object multipart upload ID

    inline void SetUploadID(std::string UploadID)
    {
        m_settingFlag |= SETTING_INPUT_UPLOAD_MULTIPART_UPLOAD_ID_FLAG;
        m_UploadID = UploadID;
    };

    inline std::string GetUploadID()
    {
        return m_UploadID;
    };

    // Object multipart content length

    inline void SetContentLength(int64_t ContentLength)
    {
        m_settingFlag |= SETTING_INPUT_UPLOAD_MULTIPART_CONTENT_LENGTH_FLAG;
        m_ContentLength = ContentLength;
    };

    inline int64_t GetContentLength()
    {
        return m_ContentLength;
    };
    // Object multipart content MD5sum

    inline void SetContentMD5(std::string ContentMD5)
    {
        m_settingFlag |= SETTING_INPUT_UPLOAD_MULTIPART_CONTENT_MD5_FLAG;
        m_ContentMD5 = ContentMD5;
    };

    inline std::string GetContentMD5()
    {
        return m_ContentMD5;
    };
    // Specify range of the source object

    inline void SetXQSCopyRange(std::string XQSCopyRange)
    {
        m_settingFlag |=
            SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_RANGE_FLAG;
        m_XQSCopyRange = XQSCopyRange;
    };

    inline std::string GetXQSCopyRange()
    {
        return m_XQSCopyRange;
    };
    // Copy source, format (/<bucket-name>/<object-key>)

    inline void SetXQSCopySource(std::string XQSCopySource)
    {
        m_settingFlag |=
            SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_SOURCE_FLAG;
        m_XQSCopySource = XQSCopySource;
    };

    inline std::string GetXQSCopySource()
    {
        return m_XQSCopySource;
    };
    // Encryption algorithm of the object

    inline void SetXQSCopySourceEncryptionCustomerAlgorithm(std::
            string
            XQSCopySourceEncryptionCustomerAlgorithm)
    {
        m_settingFlag |=
            SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_SOURCE_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG;
        m_XQSCopySourceEncryptionCustomerAlgorithm =
            XQSCopySourceEncryptionCustomerAlgorithm;
    };

    inline std::string GetXQSCopySourceEncryptionCustomerAlgorithm()
    {
        return m_XQSCopySourceEncryptionCustomerAlgorithm;
    };
    // Encryption key of the object

    inline void SetXQSCopySourceEncryptionCustomerKey(std::
            string
            XQSCopySourceEncryptionCustomerKey)
    {
        m_settingFlag |=
            SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_SOURCE_ENCRYPTION_CUSTOMER_KEY_FLAG;
        m_XQSCopySourceEncryptionCustomerKey =
            XQSCopySourceEncryptionCustomerKey;
    };

    inline std::string GetXQSCopySourceEncryptionCustomerKey()
    {
        return m_XQSCopySourceEncryptionCustomerKey;
    };
    // MD5sum of encryption key

    inline void SetXQSCopySourceEncryptionCustomerKeyMD5(std::
            string
            XQSCopySourceEncryptionCustomerKeyMD5)
    {
        m_settingFlag |=
            SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_SOURCE_ENCRYPTION_CUSTOMER_KEY_MD5_FLAG;
        m_XQSCopySourceEncryptionCustomerKeyMD5 =
            XQSCopySourceEncryptionCustomerKeyMD5;
    };

    inline std::string GetXQSCopySourceEncryptionCustomerKeyMD5()
    {
        return m_XQSCopySourceEncryptionCustomerKeyMD5;
    };
    // Check whether the Etag of copy source matches the specified value

    inline void SetXQSCopySourceIfMatch(std::string XQSCopySourceIfMatch)
    {
        m_settingFlag |=
            SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_SOURCE_IF_MATCH_FLAG;
        m_XQSCopySourceIfMatch = XQSCopySourceIfMatch;
    };

    inline std::string GetXQSCopySourceIfMatch()
    {
        return m_XQSCopySourceIfMatch;
    };
    // Check whether the copy source has been modified since the specified date
#ifdef BUILD_C_STYLE_INTERFACE
    inline void SetXQSCopySourceIfModifiedSince(char
            *x_qs_copy_source_if_modified_since)
    {
        m_XQSCopySourceIfModifiedSince = x_qs_copy_source_if_modified_since;
    };
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetXQSCopySourceIfModifiedSince(std::
            string
            XQSCopySourceIfModifiedSince)
    {
        m_settingFlag |=
            SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_SOURCE_IF_MODIFIED_SINCE_FLAG;
        m_XQSCopySourceIfModifiedSince = XQSCopySourceIfModifiedSince;
    };

    inline std::string GetXQSCopySourceIfModifiedSince()
    {
        return m_XQSCopySourceIfModifiedSince;
    };
    // Check whether the Etag of copy source does not matches the specified value

    inline void SetXQSCopySourceIfNoneMatch(std::
                                            string XQSCopySourceIfNoneMatch)
    {
        m_settingFlag |=
            SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_SOURCE_IF_NONE_MATCH_FLAG;
        m_XQSCopySourceIfNoneMatch = XQSCopySourceIfNoneMatch;
    };

    inline std::string GetXQSCopySourceIfNoneMatch()
    {
        return m_XQSCopySourceIfNoneMatch;
    };
    // Check whether the copy source has not been unmodified since the specified date
#ifdef BUILD_C_STYLE_INTERFACE
    inline void SetXQSCopySourceIfUnmodifiedSince(char
            *x_qs_copy_source_if_unmodified_since)
    {
        m_XQSCopySourceIfUnmodifiedSince =
            x_qs_copy_source_if_unmodified_since;
    };
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetXQSCopySourceIfUnmodifiedSince(std::
            string
            XQSCopySourceIfUnmodifiedSince)
    {
        m_settingFlag |=
            SETTING_INPUT_UPLOAD_MULTIPART_X_QS_COPY_SOURCE_IF_UNMODIFIED_SINCE_FLAG;
        m_XQSCopySourceIfUnmodifiedSince = XQSCopySourceIfUnmodifiedSince;
    };

    inline std::string GetXQSCopySourceIfUnmodifiedSince()
    {
        return m_XQSCopySourceIfUnmodifiedSince;
    };
    // Encryption algorithm of the object

    inline void SetXQSEncryptionCustomerAlgorithm(std::
            string
            XQSEncryptionCustomerAlgorithm)
    {
        m_settingFlag |=
            SETTING_INPUT_UPLOAD_MULTIPART_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG;
        m_XQSEncryptionCustomerAlgorithm = XQSEncryptionCustomerAlgorithm;
    };

    inline std::string GetXQSEncryptionCustomerAlgorithm()
    {
        return m_XQSEncryptionCustomerAlgorithm;
    };
    // Encryption key of the object

    inline void SetXQSEncryptionCustomerKey(std::
                                            string XQSEncryptionCustomerKey)
    {
        m_settingFlag |=
            SETTING_INPUT_UPLOAD_MULTIPART_X_QS_ENCRYPTION_CUSTOMER_KEY_FLAG;
        m_XQSEncryptionCustomerKey = XQSEncryptionCustomerKey;
    };

    inline std::string GetXQSEncryptionCustomerKey()
    {
        return m_XQSEncryptionCustomerKey;
    };
    // MD5sum of encryption key

    inline void SetXQSEncryptionCustomerKeyMD5(std::
            string
            XQSEncryptionCustomerKeyMD5)
    {
        m_settingFlag |=
            SETTING_INPUT_UPLOAD_MULTIPART_X_QS_ENCRYPTION_CUSTOMER_KEY_MD5_FLAG;
        m_XQSEncryptionCustomerKeyMD5 = XQSEncryptionCustomerKeyMD5;
    };

    inline std::string GetXQSEncryptionCustomerKeyMD5()
    {
        return m_XQSEncryptionCustomerKeyMD5;
    };

    std::iostream * GetBody()
    {
        return m_streambody;
    };
    void SetBody(std::iostream * streambody)
    {
        m_streambody = streambody;
    };
private:

    // Object multipart upload part number
    int m_PartNumber;		// Required

    // Object multipart upload ID
    std::string m_UploadID;	// Required

    // Object multipart content length
    int64_t m_ContentLength;

    // Object multipart content MD5sum
    std::string m_ContentMD5;

    // Specify range of the source object
    std::string m_XQSCopyRange;

    // Copy source, format (/<bucket-name>/<object-key>)
    std::string m_XQSCopySource;

    // Encryption algorithm of the object
    std::string m_XQSCopySourceEncryptionCustomerAlgorithm;

    // Encryption key of the object
    std::string m_XQSCopySourceEncryptionCustomerKey;

    // MD5sum of encryption key
    std::string m_XQSCopySourceEncryptionCustomerKeyMD5;

    // Check whether the Etag of copy source matches the specified value
    std::string m_XQSCopySourceIfMatch;

    // Check whether the copy source has been modified since the specified date
    std::string m_XQSCopySourceIfModifiedSince;

    // Check whether the Etag of copy source does not matches the specified value
    std::string m_XQSCopySourceIfNoneMatch;

    // Check whether the copy source has not been unmodified since the specified date
    std::string m_XQSCopySourceIfUnmodifiedSince;

    // Encryption algorithm of the object
    std::string m_XQSEncryptionCustomerAlgorithm;

    // Encryption key of the object
    std::string m_XQSEncryptionCustomerKey;

    // MD5sum of encryption key
    std::string m_XQSEncryptionCustomerKeyMD5;

    std::iostream * m_streambody;
};
// +--------------------------------------------------------------------
// |                     OutputClassHeader
// +--------------------------------------------------------------------

typedef QsOutput DeleteBucketOutput;

typedef QsOutput DeleteBucketCORSOutput;

typedef QsOutput DeleteBucketExternalMirrorOutput;

typedef QsOutput DeleteBucketPolicyOutput;

// DeleteMultipleObjectsOutput presents input for DeleteMultipleObjects.
class QS_SDK_API DeleteMultipleObjectsOutput:public QsOutput
{

public:
    DeleteMultipleObjectsOutput(QsError err,
                                Http::
                                HttpResponseCode responseCode):QsOutput(err,
                                            responseCode)
    {
    };
    DeleteMultipleObjectsOutput()
    {
    };

    // List of deleted objects
    inline void SetDeleted(std::vector < KeyType > Deleted)
    {
        m_settingFlag |=
            SETTING_OUTPUT_DELETE_MULTIPLE_OBJECTS_DELETED_FLAG;
        m_Deleted = Deleted;
    };

    inline std::vector < KeyType > GetDeleted()
    {
        return m_Deleted;
    };

    // Error messages
    inline void SetErrors(std::vector < KeyDeleteErrorType > Errors)
    {
        m_settingFlag |= SETTING_OUTPUT_DELETE_MULTIPLE_OBJECTS_ERRORS_FLAG;
        m_Errors = Errors;
    };

    inline std::vector < KeyDeleteErrorType > GetErrors()
    {
        return m_Errors;
    };

private:
    // List of deleted objects

    std::vector < KeyType > m_Deleted;

    // Error messages

    std::vector < KeyDeleteErrorType > m_Errors;

};

// GetBucketACLOutput presents input for GetBucketACL.
class QS_SDK_API GetBucketACLOutput:public QsOutput
{

public:
    GetBucketACLOutput(QsError err,
                       Http::HttpResponseCode responseCode):QsOutput(err,
                                   responseCode)
    {
    };
    GetBucketACLOutput()
    {
    };

    // Bucket ACL rules
    inline void SetACL(std::vector < ACLType > ACL)
    {
        m_settingFlag |= SETTING_OUTPUT_GET_BUCKET_ACL_ACL_FLAG;
        m_ACL = ACL;
    };

    inline std::vector < ACLType > GetACL()
    {
        return m_ACL;
    };

    // Bucket owner
    inline void SetOwner(OwnerType Owner)
    {
        m_settingFlag |= SETTING_OUTPUT_GET_BUCKET_ACL_OWNER_FLAG;
        m_Owner = Owner;
    };

    inline OwnerType GetOwner()
    {
        return m_Owner;
    };

private:
    // Bucket ACL rules

    std::vector < ACLType > m_ACL;

    // Bucket owner

    OwnerType m_Owner;

};

// GetBucketCORSOutput presents input for GetBucketCORS.
class QS_SDK_API GetBucketCORSOutput:public QsOutput
{

public:
    GetBucketCORSOutput(QsError err,
                        Http::HttpResponseCode responseCode):QsOutput(err,
                                    responseCode)
    {
    };
    GetBucketCORSOutput()
    {
    };

    // Bucket CORS rules
    inline void SetCORSRules(std::vector < CORSRuleType > CORSRules)
    {
        m_settingFlag |= SETTING_OUTPUT_GET_BUCKET_CORS_CORS_RULES_FLAG;
        m_CORSRules = CORSRules;
    };

    inline std::vector < CORSRuleType > GetCORSRules()
    {
        return m_CORSRules;
    };

private:
    // Bucket CORS rules

    std::vector < CORSRuleType > m_CORSRules;

};

// GetBucketExternalMirrorOutput presents input for GetBucketExternalMirror.
class QS_SDK_API GetBucketExternalMirrorOutput:public QsOutput
{

public:
    GetBucketExternalMirrorOutput(QsError err,
                                  Http::
                                  HttpResponseCode
                                  responseCode):QsOutput(err,
                                              responseCode)
    {
    };
    GetBucketExternalMirrorOutput()
    {
    };

    // Source site url
    inline void SetSourceSite(std::string SourceSite)
    {
        m_settingFlag |=
            SETTING_OUTPUT_GET_BUCKET_EXTERNAL_MIRROR_SOURCE_SITE_FLAG;
        m_SourceSite = SourceSite;
    };

    inline std::string GetSourceSite()
    {
        return m_SourceSite;
    };

private:
    // Source site url
    std::string m_SourceSite;

};

// GetBucketPolicyOutput presents input for GetBucketPolicy.
class QS_SDK_API GetBucketPolicyOutput:public QsOutput
{

public:
    GetBucketPolicyOutput(QsError err,
                          Http::HttpResponseCode responseCode):QsOutput(err,
                                      responseCode)
    {
    };
    GetBucketPolicyOutput()
    {
    };

    // Bucket policy statement
    inline void SetStatement(std::vector < StatementType > Statement)
    {
        m_settingFlag |= SETTING_OUTPUT_GET_BUCKET_POLICY_STATEMENT_FLAG;
        m_Statement = Statement;
    };

    inline std::vector < StatementType > GetStatement()
    {
        return m_Statement;
    };

private:
    // Bucket policy statement

    std::vector < StatementType > m_Statement;

};

// GetBucketStatisticsOutput presents input for GetBucketStatistics.
class QS_SDK_API GetBucketStatisticsOutput:public QsOutput
{

public:
    GetBucketStatisticsOutput(QsError err,
                              Http::
                              HttpResponseCode responseCode):QsOutput(err,
                                          responseCode)
    {
    };
    GetBucketStatisticsOutput()
    {
    };

    // Objects count in the bucket
    inline void SetCount(int64_t Count)
    {
        m_settingFlag |= SETTING_OUTPUT_GET_BUCKET_STATISTICS_COUNT_FLAG;
        m_Count = Count;
    };

    inline int64_t GetCount()
    {
        return m_Count;
    };

    // Bucket created time
    inline void SetCreated(std::string Created)
    {
        m_settingFlag |= SETTING_OUTPUT_GET_BUCKET_STATISTICS_CREATED_FLAG;
        m_Created = Created;
    };

    inline std::string GetCreated()
    {
        return m_Created;
    };

    // QingCloud Zone ID
    inline void SetLocation(std::string Location)
    {
        m_settingFlag |= SETTING_OUTPUT_GET_BUCKET_STATISTICS_LOCATION_FLAG;
        m_Location = Location;
    };

    inline std::string GetLocation()
    {
        return m_Location;
    };

    // Bucket name
    inline void SetName(std::string Name)
    {
        m_settingFlag |= SETTING_OUTPUT_GET_BUCKET_STATISTICS_NAME_FLAG;
        m_Name = Name;
    };

    inline std::string GetName()
    {
        return m_Name;
    };

    // Bucket storage size
    inline void SetSize(int64_t Size)
    {
        m_settingFlag |= SETTING_OUTPUT_GET_BUCKET_STATISTICS_SIZE_FLAG;
        m_Size = Size;
    };

    inline int64_t GetSize()
    {
        return m_Size;
    };

    // Bucket status// Status's available values: active, suspended
    inline void SetStatus(std::string Status)
    {
        m_settingFlag |= SETTING_OUTPUT_GET_BUCKET_STATISTICS_STATUS_FLAG;
        m_Status = Status;
    };

    inline std::string GetStatus()
    {
        return m_Status;
    };

    // URL to access the bucket
    inline void SetURL(std::string URL)
    {
        m_settingFlag |= SETTING_OUTPUT_GET_BUCKET_STATISTICS_URL_FLAG;
        m_URL = URL;
    };

    inline std::string GetURL()
    {
        return m_URL;
    };

private:
    // Objects count in the bucket
    int64_t m_Count;

    // Bucket created time
    std::string m_Created;

    // QingCloud Zone ID
    std::string m_Location;

    // Bucket name
    std::string m_Name;

    // Bucket storage size
    int64_t m_Size;

    // Bucket status
    // Status's available values: active, suspended
    std::string m_Status;

    // URL to access the bucket
    std::string m_URL;

};

typedef QsOutput HeadBucketOutput;

// ListMultipartUploadsOutput presents input for ListMultipartUploads.
class QS_SDK_API ListMultipartUploadsOutput:public QsOutput
{

public:
    ListMultipartUploadsOutput(QsError err,
                               Http::
                               HttpResponseCode responseCode):QsOutput(err,
                                           responseCode)
    {
    };
    ListMultipartUploadsOutput()
    {
    };

    // Other object keys that share common prefixes
    inline void SetCommonPrefixes(std::vector < std::string >
                                  CommonPrefixes)
    {
        m_settingFlag |=
            SETTING_OUTPUT_LIST_MULTIPART_UPLOADS_COMMON_PREFIXES_FLAG;
        m_CommonPrefixes = CommonPrefixes;
    };

    inline std::vector < std::string > GetCommonPrefixes()
    {
        return m_CommonPrefixes;
    };

    // Delimiter that specified in request parameters
    inline void SetDelimiter(std::string Delimiter)
    {
        m_settingFlag |=
            SETTING_OUTPUT_LIST_MULTIPART_UPLOADS_DELIMITER_FLAG;
        m_Delimiter = Delimiter;
    };

    inline std::string GetDelimiter()
    {
        return m_Delimiter;
    };

    // Limit that specified in request parameters
    inline void SetLimit(int Limit)
    {
        m_settingFlag |= SETTING_OUTPUT_LIST_MULTIPART_UPLOADS_LIMIT_FLAG;
        m_Limit = Limit;
    };

    inline int GetLimit()
    {
        return m_Limit;
    };

    // Marker that specified in request parameters
    inline void SetMarker(std::string Marker)
    {
        m_settingFlag |= SETTING_OUTPUT_LIST_MULTIPART_UPLOADS_MARKER_FLAG;
        m_Marker = Marker;
    };

    inline std::string GetMarker()
    {
        return m_Marker;
    };

    // Bucket name
    inline void SetName(std::string Name)
    {
        m_settingFlag |= SETTING_OUTPUT_LIST_MULTIPART_UPLOADS_NAME_FLAG;
        m_Name = Name;
    };

    inline std::string GetName()
    {
        return m_Name;
    };

    // The last key in uploads list
    inline void SetNextKeyMarker(std::string NextKeyMarker)
    {
        m_settingFlag |=
            SETTING_OUTPUT_LIST_MULTIPART_UPLOADS_NEXT_KEY_MARKER_FLAG;
        m_NextKeyMarker = NextKeyMarker;
    };

    inline std::string GetNextKeyMarker()
    {
        return m_NextKeyMarker;
    };

    // The last upload_id in uploads list
    inline void SetNextUploadIDMarker(std::string NextUploadIDMarker)
    {
        m_settingFlag |=
            SETTING_OUTPUT_LIST_MULTIPART_UPLOADS_NEXT_UPLOAD_ID_MARKER_FLAG;
        m_NextUploadIDMarker = NextUploadIDMarker;
    };

    inline std::string GetNextUploadIDMarker()
    {
        return m_NextUploadIDMarker;
    };

    // Prefix that specified in request parameters
    inline void SetPrefix(std::string Prefix)
    {
        m_settingFlag |= SETTING_OUTPUT_LIST_MULTIPART_UPLOADS_PREFIX_FLAG;
        m_Prefix = Prefix;
    };

    inline std::string GetPrefix()
    {
        return m_Prefix;
    };

    // Multipart uploads
    inline void SetUploads(std::vector < UploadsType > Uploads)
    {
        m_settingFlag |= SETTING_OUTPUT_LIST_MULTIPART_UPLOADS_UPLOADS_FLAG;
        m_Uploads = Uploads;
    };

    inline std::vector < UploadsType > GetUploads()
    {
        return m_Uploads;
    };

private:
    // Other object keys that share common prefixes

    std::vector < std::string > m_CommonPrefixes;

    // Delimiter that specified in request parameters
    std::string m_Delimiter;

    // Limit that specified in request parameters
    int m_Limit;

    // Marker that specified in request parameters
    std::string m_Marker;

    // Bucket name
    std::string m_Name;

    // The last key in uploads list
    std::string m_NextKeyMarker;

    // The last upload_id in uploads list
    std::string m_NextUploadIDMarker;

    // Prefix that specified in request parameters
    std::string m_Prefix;

    // Multipart uploads

    std::vector < UploadsType > m_Uploads;

};

// ListObjectsOutput presents input for ListObjects.
class QS_SDK_API ListObjectsOutput:public QsOutput
{

public:
    ListObjectsOutput(QsError err,
                      Http::HttpResponseCode responseCode):QsOutput(err,
                                  responseCode)
    {
    };
    ListObjectsOutput()
    {
    };

    // Other object keys that share common prefixes
    inline void SetCommonPrefixes(std::vector < std::string >
                                  CommonPrefixes)
    {
        m_settingFlag |= SETTING_OUTPUT_LIST_OBJECTS_COMMON_PREFIXES_FLAG;
        m_CommonPrefixes = CommonPrefixes;
    };

    inline std::vector < std::string > GetCommonPrefixes()
    {
        return m_CommonPrefixes;
    };

    // Delimiter that specified in request parameters
    inline void SetDelimiter(std::string Delimiter)
    {
        m_settingFlag |= SETTING_OUTPUT_LIST_OBJECTS_DELIMITER_FLAG;
        m_Delimiter = Delimiter;
    };

    inline std::string GetDelimiter()
    {
        return m_Delimiter;
    };

    // Object keys
    inline void SetKeys(std::vector < KeyType > Keys)
    {
        m_settingFlag |= SETTING_OUTPUT_LIST_OBJECTS_KEYS_FLAG;
        m_Keys = Keys;
    };

    inline std::vector < KeyType > GetKeys()
    {
        return m_Keys;
    };

    // Limit that specified in request parameters
    inline void SetLimit(int Limit)
    {
        m_settingFlag |= SETTING_OUTPUT_LIST_OBJECTS_LIMIT_FLAG;
        m_Limit = Limit;
    };

    inline int GetLimit()
    {
        return m_Limit;
    };

    // Marker that specified in request parameters
    inline void SetMarker(std::string Marker)
    {
        m_settingFlag |= SETTING_OUTPUT_LIST_OBJECTS_MARKER_FLAG;
        m_Marker = Marker;
    };

    inline std::string GetMarker()
    {
        return m_Marker;
    };

    // Bucket name
    inline void SetName(std::string Name)
    {
        m_settingFlag |= SETTING_OUTPUT_LIST_OBJECTS_NAME_FLAG;
        m_Name = Name;
    };

    inline std::string GetName()
    {
        return m_Name;
    };

    // The last key in keys list
    inline void SetNextMarker(std::string NextMarker)
    {
        m_settingFlag |= SETTING_OUTPUT_LIST_OBJECTS_NEXT_MARKER_FLAG;
        m_NextMarker = NextMarker;
    };

    inline std::string GetNextMarker()
    {
        return m_NextMarker;
    };

    // Bucket owner
    inline void SetOwner(OwnerType Owner)
    {
        m_settingFlag |= SETTING_OUTPUT_LIST_OBJECTS_OWNER_FLAG;
        m_Owner = Owner;
    };

    inline OwnerType GetOwner()
    {
        return m_Owner;
    };

    // Prefix that specified in request parameters
    inline void SetPrefix(std::string Prefix)
    {
        m_settingFlag |= SETTING_OUTPUT_LIST_OBJECTS_PREFIX_FLAG;
        m_Prefix = Prefix;
    };

    inline std::string GetPrefix()
    {
        return m_Prefix;
    };

private:
    // Other object keys that share common prefixes

    std::vector < std::string > m_CommonPrefixes;

    // Delimiter that specified in request parameters
    std::string m_Delimiter;

    // Object keys

    std::vector < KeyType > m_Keys;

    // Limit that specified in request parameters
    int m_Limit;

    // Marker that specified in request parameters
    std::string m_Marker;

    // Bucket name
    std::string m_Name;

    // The last key in keys list
    std::string m_NextMarker;

    // Bucket owner

    OwnerType m_Owner;

    // Prefix that specified in request parameters
    std::string m_Prefix;

};

typedef QsOutput PutBucketOutput;

typedef QsOutput PutBucketACLOutput;

typedef QsOutput PutBucketCORSOutput;

typedef QsOutput PutBucketExternalMirrorOutput;

typedef QsOutput PutBucketPolicyOutput;
// +--------------------------------------------------------------------
// |                     OutputClassHeader
// +--------------------------------------------------------------------

typedef QsOutput AbortMultipartUploadOutput;

// CompleteMultipartUploadOutput presents input for CompleteMultipartUpload.
class QS_SDK_API CompleteMultipartUploadOutput:public QsOutput
{

public:
    CompleteMultipartUploadOutput(QsError err,
                                  Http::
                                  HttpResponseCode
                                  responseCode):QsOutput(err,
                                              responseCode)
    {
    };
    CompleteMultipartUploadOutput()
    {
    };

    // Encryption algorithm of the object
    inline void SetXQSEncryptionCustomerAlgorithm(std::
            string
            XQSEncryptionCustomerAlgorithm)
    {
        m_settingFlag |=
            SETTING_OUTPUT_COMPLETE_MULTIPART_UPLOAD_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG;
        m_XQSEncryptionCustomerAlgorithm = XQSEncryptionCustomerAlgorithm;
    };

    inline std::string GetXQSEncryptionCustomerAlgorithm()
    {
        return m_XQSEncryptionCustomerAlgorithm;
    };

private:
    // Encryption algorithm of the object
    std::string m_XQSEncryptionCustomerAlgorithm;

};

typedef QsOutput DeleteObjectOutput;

// GetObjectOutput presents input for GetObject.
class QS_SDK_API GetObjectOutput:public QsOutput
{

public:
    GetObjectOutput(QsError err,
                    Http::HttpResponseCode responseCode):QsOutput(err,
                                responseCode)
    {
    };
    GetObjectOutput()
    {
    };

    // The Cache-Control general-header field is used to specify directives for caching mechanisms in both requests and responses.
    inline void SetCacheControl(std::string CacheControl)
    {
        m_settingFlag |= SETTING_OUTPUT_GET_OBJECT_CACHE_CONTROL_FLAG;
        m_CacheControl = CacheControl;
    };

    inline std::string GetCacheControl()
    {
        return m_CacheControl;
    };

    // In a multipart/form-data body, the HTTP Content-Disposition general header is a header that can be used on the subpart of a multipart body to give information about the field it applies to.
    inline void SetContentDisposition(std::string ContentDisposition)
    {
        m_settingFlag |= SETTING_OUTPUT_GET_OBJECT_CONTENT_DISPOSITION_FLAG;
        m_ContentDisposition = ContentDisposition;
    };

    inline std::string GetContentDisposition()
    {
        return m_ContentDisposition;
    };

    // The Content-Encoding entity header is used to compress the media-type.
    inline void SetContentEncoding(std::string ContentEncoding)
    {
        m_settingFlag |= SETTING_OUTPUT_GET_OBJECT_CONTENT_ENCODING_FLAG;
        m_ContentEncoding = ContentEncoding;
    };

    inline std::string GetContentEncoding()
    {
        return m_ContentEncoding;
    };

    // The Content-Language entity header is used to describe the language(s) intended for the audience.
    inline void SetContentLanguage(std::string ContentLanguage)
    {
        m_settingFlag |= SETTING_OUTPUT_GET_OBJECT_CONTENT_LANGUAGE_FLAG;
        m_ContentLanguage = ContentLanguage;
    };

    inline std::string GetContentLanguage()
    {
        return m_ContentLanguage;
    };

    // Object content length
    inline void SetContentLength(int64_t ContentLength)
    {
        m_settingFlag |= SETTING_OUTPUT_GET_OBJECT_CONTENT_LENGTH_FLAG;
        m_ContentLength = ContentLength;
    };

    inline int64_t GetContentLength()
    {
        return m_ContentLength;
    };

    // Range of response data content
    inline void SetContentRange(std::string ContentRange)
    {
        m_settingFlag |= SETTING_OUTPUT_GET_OBJECT_CONTENT_RANGE_FLAG;
        m_ContentRange = ContentRange;
    };

    inline std::string GetContentRange()
    {
        return m_ContentRange;
    };

    // The Content-Type entity header is used to indicate the media type of the resource.
    inline void SetContentType(std::string ContentType)
    {
        m_settingFlag |= SETTING_OUTPUT_GET_OBJECT_CONTENT_TYPE_FLAG;
        m_ContentType = ContentType;
    };

    inline std::string GetContentType()
    {
        return m_ContentType;
    };

    // MD5sum of the object
    inline void SetETag(std::string ETag)
    {
        m_settingFlag |= SETTING_OUTPUT_GET_OBJECT_ETAG_FLAG;
        m_ETag = ETag;
    };

    inline std::string GetETag()
    {
        return m_ETag;
    };

    // The Expires header contains the date/time after which the response is considered stale.
    inline void SetExpires(std::string Expires)
    {
        m_settingFlag |= SETTING_OUTPUT_GET_OBJECT_EXPIRES_FLAG;
        m_Expires = Expires;
    };

    inline std::string GetExpires()
    {
        return m_Expires;
    };

    inline void SetLastModified(std::string LastModified)
    {
        m_settingFlag |= SETTING_OUTPUT_GET_OBJECT_LAST_MODIFIED_FLAG;
        m_LastModified = LastModified;
    };

    inline std::string GetLastModified()
    {
        return m_LastModified;
    };

    // Encryption algorithm of the object
    inline void SetXQSEncryptionCustomerAlgorithm(std::
            string
            XQSEncryptionCustomerAlgorithm)
    {
        m_settingFlag |=
            SETTING_OUTPUT_GET_OBJECT_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG;
        m_XQSEncryptionCustomerAlgorithm = XQSEncryptionCustomerAlgorithm;
    };

    inline std::string GetXQSEncryptionCustomerAlgorithm()
    {
        return m_XQSEncryptionCustomerAlgorithm;
    };

    std::iostream * GetBody()
    {
        return m_streambody;
    };
    void SetBody(std::iostream * streambody)
    {
        m_streambody = streambody;
    };

private:
    // The Cache-Control general-header field is used to specify directives for caching mechanisms in both requests and responses.
    std::string m_CacheControl;

    // In a multipart/form-data body, the HTTP Content-Disposition general header is a header that can be used on the subpart of a multipart body to give information about the field it applies to.
    std::string m_ContentDisposition;

    // The Content-Encoding entity header is used to compress the media-type.
    std::string m_ContentEncoding;

    // The Content-Language entity header is used to describe the language(s) intended for the audience.
    std::string m_ContentLanguage;

    // Object content length
    int64_t m_ContentLength;

    // Range of response data content
    std::string m_ContentRange;

    // The Content-Type entity header is used to indicate the media type of the resource.
    std::string m_ContentType;

    // MD5sum of the object
    std::string m_ETag;

    // The Expires header contains the date/time after which the response is considered stale.
    std::string m_Expires;

    std::string m_LastModified;

    // Encryption algorithm of the object
    std::string m_XQSEncryptionCustomerAlgorithm;

    std::iostream * m_streambody;

};

// HeadObjectOutput presents input for HeadObject.
class QS_SDK_API HeadObjectOutput:public QsOutput
{

public:
    HeadObjectOutput(QsError err,
                     Http::HttpResponseCode responseCode):QsOutput(err,
                                 responseCode)
    {
    };
    HeadObjectOutput()
    {
    };

    // Object content length
    inline void SetContentLength(int64_t ContentLength)
    {
        m_settingFlag |= SETTING_OUTPUT_HEAD_OBJECT_CONTENT_LENGTH_FLAG;
        m_ContentLength = ContentLength;
    };

    inline int64_t GetContentLength()
    {
        return m_ContentLength;
    };

    // Object content type
    inline void SetContentType(std::string ContentType)
    {
        m_settingFlag |= SETTING_OUTPUT_HEAD_OBJECT_CONTENT_TYPE_FLAG;
        m_ContentType = ContentType;
    };

    inline std::string GetContentType()
    {
        return m_ContentType;
    };

    // MD5sum of the object
    inline void SetETag(std::string ETag)
    {
        m_settingFlag |= SETTING_OUTPUT_HEAD_OBJECT_ETAG_FLAG;
        m_ETag = ETag;
    };

    inline std::string GetETag()
    {
        return m_ETag;
    };

    inline void SetLastModified(std::string LastModified)
    {
        m_settingFlag |= SETTING_OUTPUT_HEAD_OBJECT_LAST_MODIFIED_FLAG;
        m_LastModified = LastModified;
    };

    inline std::string GetLastModified()
    {
        return m_LastModified;
    };

    // Encryption algorithm of the object
    inline void SetXQSEncryptionCustomerAlgorithm(std::
            string
            XQSEncryptionCustomerAlgorithm)
    {
        m_settingFlag |=
            SETTING_OUTPUT_HEAD_OBJECT_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG;
        m_XQSEncryptionCustomerAlgorithm = XQSEncryptionCustomerAlgorithm;
    };

    inline std::string GetXQSEncryptionCustomerAlgorithm()
    {
        return m_XQSEncryptionCustomerAlgorithm;
    };

private:
    // Object content length
    int64_t m_ContentLength;

    // Object content type
    std::string m_ContentType;

    // MD5sum of the object
    std::string m_ETag;

    std::string m_LastModified;

    // Encryption algorithm of the object
    std::string m_XQSEncryptionCustomerAlgorithm;

};

// ImageProcessOutput presents input for ImageProcess.
class QS_SDK_API ImageProcessOutput:public QsOutput
{

public:
    ImageProcessOutput(QsError err,
                       Http::HttpResponseCode responseCode):QsOutput(err,
                                   responseCode)
    {
    };
    ImageProcessOutput()
    {
    };

    // Object content length
    inline void SetContentLength(int64_t ContentLength)
    {
        m_settingFlag |= SETTING_OUTPUT_IMAGE_PROCESS_CONTENT_LENGTH_FLAG;
        m_ContentLength = ContentLength;
    };

    inline int64_t GetContentLength()
    {
        return m_ContentLength;
    };

    std::iostream * GetBody()
    {
        return m_streambody;
    };
    void SetBody(std::iostream * streambody)
    {
        m_streambody = streambody;
    };

private:
    // Object content length
    int64_t m_ContentLength;

    std::iostream * m_streambody;

};

// InitiateMultipartUploadOutput presents input for InitiateMultipartUpload.
class QS_SDK_API InitiateMultipartUploadOutput:public QsOutput
{

public:
    InitiateMultipartUploadOutput(QsError err,
                                  Http::
                                  HttpResponseCode
                                  responseCode):QsOutput(err,
                                              responseCode)
    {
    };
    InitiateMultipartUploadOutput()
    {
    };

    // Encryption algorithm of the object
    inline void SetXQSEncryptionCustomerAlgorithm(std::
            string
            XQSEncryptionCustomerAlgorithm)
    {
        m_settingFlag |=
            SETTING_OUTPUT_INITIATE_MULTIPART_UPLOAD_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG;
        m_XQSEncryptionCustomerAlgorithm = XQSEncryptionCustomerAlgorithm;
    };

    inline std::string GetXQSEncryptionCustomerAlgorithm()
    {
        return m_XQSEncryptionCustomerAlgorithm;
    };

    // Bucket name
    inline void SetBucket(std::string Bucket)
    {
        m_settingFlag |=
            SETTING_OUTPUT_INITIATE_MULTIPART_UPLOAD_BUCKET_FLAG;
        m_Bucket = Bucket;
    };

    inline std::string GetBucket()
    {
        return m_Bucket;
    };

    // Object key
    inline void SetKey(std::string Key)
    {
        m_settingFlag |= SETTING_OUTPUT_INITIATE_MULTIPART_UPLOAD_KEY_FLAG;
        m_Key = Key;
    };

    inline std::string GetKey()
    {
        return m_Key;
    };

    // Object multipart upload ID
    inline void SetUploadID(std::string UploadID)
    {
        m_settingFlag |=
            SETTING_OUTPUT_INITIATE_MULTIPART_UPLOAD_UPLOAD_ID_FLAG;
        m_UploadID = UploadID;
    };

    inline std::string GetUploadID()
    {
        return m_UploadID;
    };

private:
    // Encryption algorithm of the object
    std::string m_XQSEncryptionCustomerAlgorithm;

    // Bucket name
    std::string m_Bucket;

    // Object key
    std::string m_Key;

    // Object multipart upload ID
    std::string m_UploadID;

};

// ListMultipartOutput presents input for ListMultipart.
class QS_SDK_API ListMultipartOutput:public QsOutput
{

public:
    ListMultipartOutput(QsError err,
                        Http::HttpResponseCode responseCode):QsOutput(err,
                                    responseCode)
    {
    };
    ListMultipartOutput()
    {
    };

    // Object multipart count
    inline void SetCount(int Count)
    {
        m_settingFlag |= SETTING_OUTPUT_LIST_MULTIPART_COUNT_FLAG;
        m_Count = Count;
    };

    inline int GetCount()
    {
        return m_Count;
    };

    // Object parts
    inline void SetObjectParts(std::vector < ObjectPartType > ObjectParts)
    {
        m_settingFlag |= SETTING_OUTPUT_LIST_MULTIPART_OBJECT_PARTS_FLAG;
        m_ObjectParts = ObjectParts;
    };

    inline std::vector < ObjectPartType > GetObjectParts()
    {
        return m_ObjectParts;
    };

private:
    // Object multipart count
    int m_Count;

    // Object parts

    std::vector < ObjectPartType > m_ObjectParts;

};

// OptionsObjectOutput presents input for OptionsObject.
class QS_SDK_API OptionsObjectOutput:public QsOutput
{

public:
    OptionsObjectOutput(QsError err,
                        Http::HttpResponseCode responseCode):QsOutput(err,
                                    responseCode)
    {
    };
    OptionsObjectOutput()
    {
    };

    // Allowed headers
    inline void SetAccessControlAllowHeaders(std::
            string
            AccessControlAllowHeaders)
    {
        m_settingFlag |=
            SETTING_OUTPUT_OPTIONS_OBJECT_ACCESS_CONTROL_ALLOW_HEADERS_FLAG;
        m_AccessControlAllowHeaders = AccessControlAllowHeaders;
    };

    inline std::string GetAccessControlAllowHeaders()
    {
        return m_AccessControlAllowHeaders;
    };

    // Allowed methods
    inline void SetAccessControlAllowMethods(std::
            string
            AccessControlAllowMethods)
    {
        m_settingFlag |=
            SETTING_OUTPUT_OPTIONS_OBJECT_ACCESS_CONTROL_ALLOW_METHODS_FLAG;
        m_AccessControlAllowMethods = AccessControlAllowMethods;
    };

    inline std::string GetAccessControlAllowMethods()
    {
        return m_AccessControlAllowMethods;
    };

    // Allowed origin
    inline void SetAccessControlAllowOrigin(std::
                                            string AccessControlAllowOrigin)
    {
        m_settingFlag |=
            SETTING_OUTPUT_OPTIONS_OBJECT_ACCESS_CONTROL_ALLOW_ORIGIN_FLAG;
        m_AccessControlAllowOrigin = AccessControlAllowOrigin;
    };

    inline std::string GetAccessControlAllowOrigin()
    {
        return m_AccessControlAllowOrigin;
    };

    // Expose headers
    inline void SetAccessControlExposeHeaders(std::
            string
            AccessControlExposeHeaders)
    {
        m_settingFlag |=
            SETTING_OUTPUT_OPTIONS_OBJECT_ACCESS_CONTROL_EXPOSE_HEADERS_FLAG;
        m_AccessControlExposeHeaders = AccessControlExposeHeaders;
    };

    inline std::string GetAccessControlExposeHeaders()
    {
        return m_AccessControlExposeHeaders;
    };

    // Max age
    inline void SetAccessControlMaxAge(std::string AccessControlMaxAge)
    {
        m_settingFlag |=
            SETTING_OUTPUT_OPTIONS_OBJECT_ACCESS_CONTROL_MAX_AGE_FLAG;
        m_AccessControlMaxAge = AccessControlMaxAge;
    };

    inline std::string GetAccessControlMaxAge()
    {
        return m_AccessControlMaxAge;
    };

private:
    // Allowed headers
    std::string m_AccessControlAllowHeaders;

    // Allowed methods
    std::string m_AccessControlAllowMethods;

    // Allowed origin
    std::string m_AccessControlAllowOrigin;

    // Expose headers
    std::string m_AccessControlExposeHeaders;

    // Max age
    std::string m_AccessControlMaxAge;

};

// PutObjectOutput presents input for PutObject.
class QS_SDK_API PutObjectOutput:public QsOutput
{

public:
    PutObjectOutput(QsError err,
                    Http::HttpResponseCode responseCode):QsOutput(err,
                                responseCode)
    {
    };
    PutObjectOutput()
    {
    };

    // MD5sum of the object
    inline void SetETag(std::string ETag)
    {
        m_settingFlag |= SETTING_OUTPUT_PUT_OBJECT_ETAG_FLAG;
        m_ETag = ETag;
    };

    inline std::string GetETag()
    {
        return m_ETag;
    };

    // Encryption algorithm of the object
    inline void SetXQSEncryptionCustomerAlgorithm(std::
            string
            XQSEncryptionCustomerAlgorithm)
    {
        m_settingFlag |=
            SETTING_OUTPUT_PUT_OBJECT_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG;
        m_XQSEncryptionCustomerAlgorithm = XQSEncryptionCustomerAlgorithm;
    };

    inline std::string GetXQSEncryptionCustomerAlgorithm()
    {
        return m_XQSEncryptionCustomerAlgorithm;
    };

private:
    // MD5sum of the object
    std::string m_ETag;

    // Encryption algorithm of the object
    std::string m_XQSEncryptionCustomerAlgorithm;

};

// UploadMultipartOutput presents input for UploadMultipart.
class QS_SDK_API UploadMultipartOutput:public QsOutput
{

public:
    UploadMultipartOutput(QsError err,
                          Http::HttpResponseCode responseCode):QsOutput(err,
                                      responseCode)
    {
    };
    UploadMultipartOutput()
    {
    };

    // MD5sum of the object
    inline void SetETag(std::string ETag)
    {
        m_settingFlag |= SETTING_OUTPUT_UPLOAD_MULTIPART_ETAG_FLAG;
        m_ETag = ETag;
    };

    inline std::string GetETag()
    {
        return m_ETag;
    };

    // Range of response data content
    inline void SetXQSContentCopyRange(std::string XQSContentCopyRange)
    {
        m_settingFlag |=
            SETTING_OUTPUT_UPLOAD_MULTIPART_X_QS_CONTENT_COPY_RANGE_FLAG;
        m_XQSContentCopyRange = XQSContentCopyRange;
    };

    inline std::string GetXQSContentCopyRange()
    {
        return m_XQSContentCopyRange;
    };

    // Encryption algorithm of the object
    inline void SetXQSEncryptionCustomerAlgorithm(std::
            string
            XQSEncryptionCustomerAlgorithm)
    {
        m_settingFlag |=
            SETTING_OUTPUT_UPLOAD_MULTIPART_X_QS_ENCRYPTION_CUSTOMER_ALGORITHM_FLAG;
        m_XQSEncryptionCustomerAlgorithm = XQSEncryptionCustomerAlgorithm;
    };

    inline std::string GetXQSEncryptionCustomerAlgorithm()
    {
        return m_XQSEncryptionCustomerAlgorithm;
    };

private:
    // MD5sum of the object
    std::string m_ETag;

    // Range of response data content
    std::string m_XQSContentCopyRange;

    // Encryption algorithm of the object
    std::string m_XQSEncryptionCustomerAlgorithm;

};

// +--------------------------------------------------------------------
// |                           Bucket
// +--------------------------------------------------------------------
class QS_SDK_API Bucket
{
public:
    Bucket(const QsConfig & qsConfig, const std::string & strBucketName,
           const std::string & strZone);

    virtual ~ Bucket()
    {
    };

    // Delete does Delete a bucket.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/delete.html
    QsError DeleteBucket(DeleteBucketInput & input,
                         DeleteBucketOutput & output);

    // DeleteCORS does Delete CORS information of the bucket.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/cors/delete_cors.html
    QsError DeleteBucketCORS(DeleteBucketCORSInput & input,
                             DeleteBucketCORSOutput & output);

    // DeleteExternalMirror does Delete external mirror of the bucket.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/external_mirror/delete_external_mirror.html
    QsError DeleteBucketExternalMirror(DeleteBucketExternalMirrorInput &
                                       input,
                                       DeleteBucketExternalMirrorOutput &
                                       output);

    // DeletePolicy does Delete policy information of the bucket.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/policy/delete_policy.html
    QsError DeleteBucketPolicy(DeleteBucketPolicyInput & input,
                               DeleteBucketPolicyOutput & output);

    // DeleteMultipleObjects does Delete multiple objects from the bucket.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/delete_multiple.html
    QsError DeleteMultipleObjects(DeleteMultipleObjectsInput & input,
                                  DeleteMultipleObjectsOutput & output);

    // GetACL does Get ACL information of the bucket.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/get_acl.html
    QsError GetBucketACL(GetBucketACLInput & input,
                         GetBucketACLOutput & output);

    // GetCORS does Get CORS information of the bucket.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/cors/get_cors.html
    QsError GetBucketCORS(GetBucketCORSInput & input,
                          GetBucketCORSOutput & output);

    // GetExternalMirror does Get external mirror of the bucket.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/external_mirror/get_external_mirror.html
    QsError GetBucketExternalMirror(GetBucketExternalMirrorInput & input,
                                    GetBucketExternalMirrorOutput & output);

    // GetPolicy does Get policy information of the bucket.
    // Documentation URL: https://https://docs.qingcloud.com/qingstor/api/bucket/policy/get_policy.html
    QsError GetBucketPolicy(GetBucketPolicyInput & input,
                            GetBucketPolicyOutput & output);

    // GetStatistics does Get statistics information of the bucket.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/get_stats.html
    QsError GetBucketStatistics(GetBucketStatisticsInput & input,
                                GetBucketStatisticsOutput & output);

    // Head does Check whether the bucket exists and available.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/head.html
    QsError HeadBucket(HeadBucketInput & input, HeadBucketOutput & output);

    // ListMultipartUploads does List multipart uploads in the bucket.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/list_multipart_uploads.html
    QsError ListMultipartUploads(ListMultipartUploadsInput & input,
                                 ListMultipartUploadsOutput & output);

    // ListObjects does Retrieve the object list in a bucket.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/get.html
    QsError ListObjects(ListObjectsInput & input,
                        ListObjectsOutput & output);

    // Put does Create a new bucket.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/put.html
    QsError PutBucket(PutBucketInput & input, PutBucketOutput & output);

    // PutACL does Set ACL information of the bucket.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/put_acl.html
    QsError PutBucketACL(PutBucketACLInput & input,
                         PutBucketACLOutput & output);

    // PutCORS does Set CORS information of the bucket.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/cors/put_cors.html
    QsError PutBucketCORS(PutBucketCORSInput & input,
                          PutBucketCORSOutput & output);

    // PutExternalMirror does Set external mirror of the bucket.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/external_mirror/put_external_mirror.html
    QsError PutBucketExternalMirror(PutBucketExternalMirrorInput & input,
                                    PutBucketExternalMirrorOutput & output);

    // PutPolicy does Set policy information of the bucket.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/bucket/policy/put_policy.html
    QsError PutBucketPolicy(PutBucketPolicyInput & input,
                            PutBucketPolicyOutput & output);

    // AbortMultipartUpload does Abort multipart upload.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/object/abort_multipart_upload.html
    QsError AbortMultipartUpload(std::string objectKey,
                                 AbortMultipartUploadInput & input,
                                 AbortMultipartUploadOutput & output);

    // CompleteMultipartUpload does Complete multipart upload.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/object/complete_multipart_upload.html
    QsError CompleteMultipartUpload(std::string objectKey,
                                    CompleteMultipartUploadInput & input,
                                    CompleteMultipartUploadOutput & output);

    // DeleteObject does Delete the object.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/object/delete.html
    QsError DeleteObject(std::string objectKey, DeleteObjectInput & input,
                         DeleteObjectOutput & output);

    // GetObject does Retrieve the object.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/object/get.html
    QsError GetObject(std::string objectKey, GetObjectInput & input,
                      GetObjectOutput & output);

    // HeadObject does Check whether the object exists and available.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/object/head.html
    QsError HeadObject(std::string objectKey, HeadObjectInput & input,
                       HeadObjectOutput & output);

    // ImageProcess does Image process with the action on the object
    // Documentation URL: https://docs.qingcloud.com/qingstor/data_process/image_process/index.html
    QsError ImageProcess(std::string objectKey, ImageProcessInput & input,
                         ImageProcessOutput & output);

    // InitiateMultipartUpload does Initial multipart upload on the object.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/object/initiate_multipart_upload.html
    QsError InitiateMultipartUpload(std::string objectKey,
                                    InitiateMultipartUploadInput & input,
                                    InitiateMultipartUploadOutput & output);

    // ListMultipart does List object parts.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/object/list_multipart.html
    QsError ListMultipart(std::string objectKey, ListMultipartInput & input,
                          ListMultipartOutput & output);

    // OptionsObject does Check whether the object accepts a origin with method and header.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/object/options.html
    QsError OptionsObject(std::string objectKey, OptionsObjectInput & input,
                          OptionsObjectOutput & output);

    // PutObject does Upload the object.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/object/put.html
    QsError PutObject(std::string objectKey, PutObjectInput & input,
                      PutObjectOutput & output);

    // UploadMultipart does Upload object multipart.
    // Documentation URL: https://docs.qingcloud.com/qingstor/api/object/multipart/upload_multipart.html
    QsError UploadMultipart(std::string objectKey,
                            UploadMultipartInput & input,
                            UploadMultipartOutput & output);

private:
    QsConfig m_qsConfig;
    Properties m_properties;

};

}								// namespace QingStor
