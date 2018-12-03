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

// Headers of CustomizedType.
#include "Types.h"
#include "external/json/json.h"
#include <algorithm>
#include <time.h>
#include <string>
#include <string.h>
#include <memory>

#ifdef BUILD_C_STYLE_INTERFACE
AbortIncompleteMultipartUploadType::
AbortIncompleteMultipartUploadType(qs_abort_incomplete_multipart_upload_t
                                   abort_incomplete_multipart_upload)
{
    if (abort_incomplete_multipart_upload.days_after_initiation)
        SetDaysAfterInitiation(*abort_incomplete_multipart_upload.
                               days_after_initiation);
}

qs_abort_incomplete_multipart_upload_t *AbortIncompleteMultipartUploadType::
toCStyleObj()
{
    qs_abort_incomplete_multipart_upload_t *abort_incomplete_multipart_upload =
        (qs_abort_incomplete_multipart_upload_t *)
        malloc(sizeof(qs_abort_incomplete_multipart_upload_t));
    abort_incomplete_multipart_upload->days_after_initiation =
        (int *) malloc(sizeof(int));
    *abort_incomplete_multipart_upload->days_after_initiation =
        GetDaysAfterInitiation();
    return abort_incomplete_multipart_upload;
}

#endif							// BUILD_C_STYLE_INTERFACE

AbortIncompleteMultipartUploadType::AbortIncompleteMultipartUploadType(std::
        string
        serializedString)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(serializedString, jsonContent);
    if (jsonContent.isMember("days_after_initiation"))
    {
        SetDaysAfterInitiation(jsonContent["days_after_initiation"].asInt());
    }
}

std::string AbortIncompleteMultipartUploadType::Serialize()
{
    Json::Value jsonContent;
    Json::FastWriter jsonWriter;
    if (m_settingFlag &
            SETTING_ABORT_INCOMPLETE_MULTIPART_UPLOAD_DAYS_AFTER_INITIATION_FLAG)
    {
        jsonContent["days_after_initiation"] = m_DaysAfterInitiation;
    }
    return jsonWriter.write(jsonContent);
}

#ifdef BUILD_C_STYLE_INTERFACE
ACLType::ACLType(qs_acl_t acl)
{
    if (acl.grantee)
        SetGrantee(*acl.grantee);
    if (acl.permission)
        SetPermission(acl.permission);
}

qs_acl_t *ACLType::toCStyleObj()
{
    qs_acl_t *acl = (qs_acl_t *) malloc(sizeof(qs_acl_t));
    acl->grantee = GetGrantee().toCStyleObj();
    int permissionLength = 0;
    permissionLength = GetPermission().length();
    if (permissionLength > 0)
    {
        acl->permission = (char *) malloc(permissionLength + 1);
        memset(acl->permission, 0, permissionLength + 1);
        strncpy(acl->permission, GetPermission().c_str(), permissionLength);
    }
    else
    {
        acl->permission = NULL;
    }
    return acl;
}

#endif							// BUILD_C_STYLE_INTERFACE

ACLType::ACLType(std::string serializedString)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(serializedString, jsonContent);
    if (jsonContent.isMember("grantee"))
    {
        SetGrantee(jsonContent["grantee"].toStyledString());
    }
    if (jsonContent.isMember("permission"))
    {
        SetPermission(jsonContent["permission"].asString());
    }
}

std::string ACLType::Serialize()
{
    Json::Value jsonContent;
    Json::FastWriter jsonWriter;
    if (m_settingFlag & SETTING_ACL_GRANTEE_FLAG)
    {
        Json::Reader jsonReader;
        Json::Value itemJsonValue;
        jsonReader.parse(m_Grantee.Serialize(), itemJsonValue);
        jsonContent["grantee"] = itemJsonValue;
    }
    if (m_settingFlag & SETTING_ACL_PERMISSION_FLAG)
    {
        jsonContent["permission"] = m_Permission;
    }
    return jsonWriter.write(jsonContent);
}

#ifdef BUILD_C_STYLE_INTERFACE
BucketType::BucketType(qs_bucket_t bucket)
{
    if (bucket.created)
        SetCreated(bucket.created);
    if (bucket.location)
        SetLocation(bucket.location);
    if (bucket.name)
        SetName(bucket.name);
    if (bucket.url)
        SetURL(bucket.url);
}

qs_bucket_t *BucketType::toCStyleObj()
{
    qs_bucket_t *bucket = (qs_bucket_t *) malloc(sizeof(qs_bucket_t));
    int createdLength = 0;
    createdLength = GetCreated().length();
    if (createdLength > 0)
    {
        bucket->created = (char *) malloc(createdLength + 1);
        memset(bucket->created, 0, createdLength + 1);
        strncpy(bucket->created, GetCreated().c_str(), createdLength);
    }
    else
    {
        bucket->created = NULL;
    }
    int locationLength = 0;
    locationLength = GetLocation().length();
    if (locationLength > 0)
    {
        bucket->location = (char *) malloc(locationLength + 1);
        memset(bucket->location, 0, locationLength + 1);
        strncpy(bucket->location, GetLocation().c_str(), locationLength);
    }
    else
    {
        bucket->location = NULL;
    }
    int nameLength = 0;
    nameLength = GetName().length();
    if (nameLength > 0)
    {
        bucket->name = (char *) malloc(nameLength + 1);
        memset(bucket->name, 0, nameLength + 1);
        strncpy(bucket->name, GetName().c_str(), nameLength);
    }
    else
    {
        bucket->name = NULL;
    }
    int urlLength = 0;
    urlLength = GetURL().length();
    if (urlLength > 0)
    {
        bucket->url = (char *) malloc(urlLength + 1);
        memset(bucket->url, 0, urlLength + 1);
        strncpy(bucket->url, GetURL().c_str(), urlLength);
    }
    else
    {
        bucket->url = NULL;
    }
    return bucket;
}

#endif							// BUILD_C_STYLE_INTERFACE

BucketType::BucketType(std::string serializedString)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(serializedString, jsonContent);
    if (jsonContent.isMember("created"))
    {
        SetCreated(jsonContent["created"].asString());
    }
    if (jsonContent.isMember("location"))
    {
        SetLocation(jsonContent["location"].asString());
    }
    if (jsonContent.isMember("name"))
    {
        SetName(jsonContent["name"].asString());
    }
    if (jsonContent.isMember("url"))
    {
        SetURL(jsonContent["url"].asString());
    }
}

std::string BucketType::Serialize()
{
    Json::Value jsonContent;
    Json::FastWriter jsonWriter;
    if (m_settingFlag & SETTING_BUCKET_CREATED_FLAG)
    {
        jsonContent["created"] = m_Created;
    }
    if (m_settingFlag & SETTING_BUCKET_LOCATION_FLAG)
    {
        jsonContent["location"] = m_Location;
    }
    if (m_settingFlag & SETTING_BUCKET_NAME_FLAG)
    {
        jsonContent["name"] = m_Name;
    }
    if (m_settingFlag & SETTING_BUCKET_URL_FLAG)
    {
        jsonContent["url"] = m_URL;
    }
    return jsonWriter.write(jsonContent);
}

#ifdef BUILD_C_STYLE_INTERFACE
CloudfuncArgsType::CloudfuncArgsType(qs_cloudfunc_args_t cloudfunc_args)
{
    if (cloudfunc_args.action)
        SetAction(cloudfunc_args.action);
    if (cloudfunc_args.key_prefix)
        SetKeyPrefix(cloudfunc_args.key_prefix);
    if (cloudfunc_args.key_seprate)
        SetKeySeprate(cloudfunc_args.key_seprate);
    if (cloudfunc_args.save_bucket)
        SetSaveBucket(cloudfunc_args.save_bucket);
}

qs_cloudfunc_args_t *CloudfuncArgsType::toCStyleObj()
{
    qs_cloudfunc_args_t *cloudfunc_args =
        (qs_cloudfunc_args_t *) malloc(sizeof(qs_cloudfunc_args_t));
    int actionLength = 0;
    actionLength = GetAction().length();
    if (actionLength > 0)
    {
        cloudfunc_args->action = (char *) malloc(actionLength + 1);
        memset(cloudfunc_args->action, 0, actionLength + 1);
        strncpy(cloudfunc_args->action, GetAction().c_str(), actionLength);
    }
    else
    {
        cloudfunc_args->action = NULL;
    }
    int keyPrefixLength = 0;
    keyPrefixLength = GetKeyPrefix().length();
    if (keyPrefixLength > 0)
    {
        cloudfunc_args->key_prefix = (char *) malloc(keyPrefixLength + 1);
        memset(cloudfunc_args->key_prefix, 0, keyPrefixLength + 1);
        strncpy(cloudfunc_args->key_prefix, GetKeyPrefix().c_str(),
                keyPrefixLength);
    }
    else
    {
        cloudfunc_args->key_prefix = NULL;
    }
    int keySeprateLength = 0;
    keySeprateLength = GetKeySeprate().length();
    if (keySeprateLength > 0)
    {
        cloudfunc_args->key_seprate = (char *) malloc(keySeprateLength + 1);
        memset(cloudfunc_args->key_seprate, 0, keySeprateLength + 1);
        strncpy(cloudfunc_args->key_seprate, GetKeySeprate().c_str(),
                keySeprateLength);
    }
    else
    {
        cloudfunc_args->key_seprate = NULL;
    }
    int saveBucketLength = 0;
    saveBucketLength = GetSaveBucket().length();
    if (saveBucketLength > 0)
    {
        cloudfunc_args->save_bucket = (char *) malloc(saveBucketLength + 1);
        memset(cloudfunc_args->save_bucket, 0, saveBucketLength + 1);
        strncpy(cloudfunc_args->save_bucket, GetSaveBucket().c_str(),
                saveBucketLength);
    }
    else
    {
        cloudfunc_args->save_bucket = NULL;
    }
    return cloudfunc_args;
}

#endif							// BUILD_C_STYLE_INTERFACE

CloudfuncArgsType::CloudfuncArgsType(std::string serializedString)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(serializedString, jsonContent);
    if (jsonContent.isMember("action"))
    {
        SetAction(jsonContent["action"].asString());
    }
    if (jsonContent.isMember("key_prefix"))
    {
        SetKeyPrefix(jsonContent["key_prefix"].asString());
    }
    if (jsonContent.isMember("key_seprate"))
    {
        SetKeySeprate(jsonContent["key_seprate"].asString());
    }
    if (jsonContent.isMember("save_bucket"))
    {
        SetSaveBucket(jsonContent["save_bucket"].asString());
    }
}

std::string CloudfuncArgsType::Serialize()
{
    Json::Value jsonContent;
    Json::FastWriter jsonWriter;
    if (m_settingFlag & SETTING_CLOUDFUNC_ARGS_ACTION_FLAG)
    {
        jsonContent["action"] = m_Action;
    }
    if (m_settingFlag & SETTING_CLOUDFUNC_ARGS_KEY_PREFIX_FLAG)
    {
        jsonContent["key_prefix"] = m_KeyPrefix;
    }
    if (m_settingFlag & SETTING_CLOUDFUNC_ARGS_KEY_SEPRATE_FLAG)
    {
        jsonContent["key_seprate"] = m_KeySeprate;
    }
    if (m_settingFlag & SETTING_CLOUDFUNC_ARGS_SAVE_BUCKET_FLAG)
    {
        jsonContent["save_bucket"] = m_SaveBucket;
    }
    return jsonWriter.write(jsonContent);
}

#ifdef BUILD_C_STYLE_INTERFACE
ConditionType::ConditionType(qs_condition_t condition)
{
    if (condition.ip_address)
        SetIPAddress(*condition.ip_address);
    if (condition.is_null)
        SetIsNull(*condition.is_null);
    if (condition.not_ip_address)
        SetNotIPAddress(*condition.not_ip_address);
    if (condition.string_like)
        SetStringLike(*condition.string_like);
    if (condition.string_not_like)
        SetStringNotLike(*condition.string_not_like);
}

qs_condition_t *ConditionType::toCStyleObj()
{
    qs_condition_t *condition =
        (qs_condition_t *) malloc(sizeof(qs_condition_t));
    condition->ip_address = GetIPAddress().toCStyleObj();
    condition->is_null = GetIsNull().toCStyleObj();
    condition->not_ip_address = GetNotIPAddress().toCStyleObj();
    condition->string_like = GetStringLike().toCStyleObj();
    condition->string_not_like = GetStringNotLike().toCStyleObj();
    return condition;
}

#endif							// BUILD_C_STYLE_INTERFACE

ConditionType::ConditionType(std::string serializedString)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(serializedString, jsonContent);
    if (jsonContent.isMember("ip_address"))
    {
        SetIPAddress(jsonContent["ip_address"].toStyledString());
    }
    if (jsonContent.isMember("is_null"))
    {
        SetIsNull(jsonContent["is_null"].toStyledString());
    }
    if (jsonContent.isMember("not_ip_address"))
    {
        SetNotIPAddress(jsonContent["not_ip_address"].toStyledString());
    }
    if (jsonContent.isMember("string_like"))
    {
        SetStringLike(jsonContent["string_like"].toStyledString());
    }
    if (jsonContent.isMember("string_not_like"))
    {
        SetStringNotLike(jsonContent["string_not_like"].toStyledString());
    }
}

std::string ConditionType::Serialize()
{
    Json::Value jsonContent;
    Json::FastWriter jsonWriter;
    if (m_settingFlag & SETTING_CONDITION_IP_ADDRESS_FLAG)
    {
        Json::Reader jsonReader;
        Json::Value itemJsonValue;
        jsonReader.parse(m_IPAddress.Serialize(), itemJsonValue);
        jsonContent["ip_address"] = itemJsonValue;
    }
    if (m_settingFlag & SETTING_CONDITION_IS_NULL_FLAG)
    {
        Json::Reader jsonReader;
        Json::Value itemJsonValue;
        jsonReader.parse(m_IsNull.Serialize(), itemJsonValue);
        jsonContent["is_null"] = itemJsonValue;
    }
    if (m_settingFlag & SETTING_CONDITION_NOT_IP_ADDRESS_FLAG)
    {
        Json::Reader jsonReader;
        Json::Value itemJsonValue;
        jsonReader.parse(m_NotIPAddress.Serialize(), itemJsonValue);
        jsonContent["not_ip_address"] = itemJsonValue;
    }
    if (m_settingFlag & SETTING_CONDITION_STRING_LIKE_FLAG)
    {
        Json::Reader jsonReader;
        Json::Value itemJsonValue;
        jsonReader.parse(m_StringLike.Serialize(), itemJsonValue);
        jsonContent["string_like"] = itemJsonValue;
    }
    if (m_settingFlag & SETTING_CONDITION_STRING_NOT_LIKE_FLAG)
    {
        Json::Reader jsonReader;
        Json::Value itemJsonValue;
        jsonReader.parse(m_StringNotLike.Serialize(), itemJsonValue);
        jsonContent["string_not_like"] = itemJsonValue;
    }
    return jsonWriter.write(jsonContent);
}

#ifdef BUILD_C_STYLE_INTERFACE
CORSRuleType::CORSRuleType(qs_cors_rule_t cors_rule)
{
    if (cors_rule.allowed_headers)
        SetAllowedHeaders(cors_rule.allowed_headers);
    if (cors_rule.allowed_methods)
        SetAllowedMethods(cors_rule.allowed_methods);
    if (cors_rule.allowed_origin)
        SetAllowedOrigin(cors_rule.allowed_origin);
    if (cors_rule.expose_headers)
        SetExposeHeaders(cors_rule.expose_headers);
    if (cors_rule.max_age_seconds)
        SetMaxAgeSeconds(*cors_rule.max_age_seconds);
}

qs_cors_rule_t *CORSRuleType::toCStyleObj()
{
    qs_cors_rule_t *cors_rule =
        (qs_cors_rule_t *) malloc(sizeof(qs_cors_rule_t));
    qs_list_t *list_allowed_headers = (qs_list_t *) malloc(sizeof(qs_list_t));
    qs_list_init(list_allowed_headers);
    std::vector < std::string > allowedHeaders = GetAllowedHeaders();
    for (std::vector < std::string >::iterator it = allowedHeaders.begin();
            it != allowedHeaders.end(); it++)
    {
        qs_cors_rule_allowed_headers_item_t *item =
            (qs_cors_rule_allowed_headers_item_t *)
            malloc(sizeof(qs_cors_rule_allowed_headers_item_t));
        int allowedHeadersLength = it->length();
        if (allowedHeadersLength > 0)
        {
            item->content = (char *) malloc(allowedHeadersLength + 1);
            memset(item->content, 0, allowedHeadersLength + 1);
            strncpy(item->content, it->c_str(), allowedHeadersLength);
        }
        else
        {
            item->content = NULL;
        }
        qs_list_append(&item->node, list_allowed_headers);
    }
    cors_rule->allowed_headers = list_allowed_headers;
    qs_list_t *list_allowed_methods = (qs_list_t *) malloc(sizeof(qs_list_t));
    qs_list_init(list_allowed_methods);
    std::vector < std::string > allowedMethods = GetAllowedMethods();
    for (std::vector < std::string >::iterator it = allowedMethods.begin();
            it != allowedMethods.end(); it++)
    {
        qs_cors_rule_allowed_methods_item_t *item =
            (qs_cors_rule_allowed_methods_item_t *)
            malloc(sizeof(qs_cors_rule_allowed_methods_item_t));
        int allowedMethodsLength = it->length();
        if (allowedMethodsLength > 0)
        {
            item->content = (char *) malloc(allowedMethodsLength + 1);
            memset(item->content, 0, allowedMethodsLength + 1);
            strncpy(item->content, it->c_str(), allowedMethodsLength);
        }
        else
        {
            item->content = NULL;
        }
        qs_list_append(&item->node, list_allowed_methods);
    }
    cors_rule->allowed_methods = list_allowed_methods;
    int allowedOriginLength = 0;
    allowedOriginLength = GetAllowedOrigin().length();
    if (allowedOriginLength > 0)
    {
        cors_rule->allowed_origin = (char *) malloc(allowedOriginLength + 1);
        memset(cors_rule->allowed_origin, 0, allowedOriginLength + 1);
        strncpy(cors_rule->allowed_origin, GetAllowedOrigin().c_str(),
                allowedOriginLength);
    }
    else
    {
        cors_rule->allowed_origin = NULL;
    }
    qs_list_t *list_expose_headers = (qs_list_t *) malloc(sizeof(qs_list_t));
    qs_list_init(list_expose_headers);
    std::vector < std::string > exposeHeaders = GetExposeHeaders();
    for (std::vector < std::string >::iterator it = exposeHeaders.begin();
            it != exposeHeaders.end(); it++)
    {
        qs_cors_rule_expose_headers_item_t *item =
            (qs_cors_rule_expose_headers_item_t *)
            malloc(sizeof(qs_cors_rule_expose_headers_item_t));
        int exposeHeadersLength = it->length();
        if (exposeHeadersLength > 0)
        {
            item->content = (char *) malloc(exposeHeadersLength + 1);
            memset(item->content, 0, exposeHeadersLength + 1);
            strncpy(item->content, it->c_str(), exposeHeadersLength);
        }
        else
        {
            item->content = NULL;
        }
        qs_list_append(&item->node, list_expose_headers);
    }
    cors_rule->expose_headers = list_expose_headers;
    cors_rule->max_age_seconds = (int *) malloc(sizeof(int));
    *cors_rule->max_age_seconds = GetMaxAgeSeconds();
    return cors_rule;
}

#endif							// BUILD_C_STYLE_INTERFACE

CORSRuleType::CORSRuleType(std::string serializedString)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(serializedString, jsonContent);
    if (jsonContent.isMember("allowed_headers"))
    {
        std::vector < std::string > vecAllowedHeaders;
        for (unsigned i = 0; i < jsonContent["allowed_headers"].size(); ++i)
        {
            vecAllowedHeaders.push_back(jsonContent["allowed_headers"][i].
                                        asString());
        }
        SetAllowedHeaders(vecAllowedHeaders);
    }
    if (jsonContent.isMember("allowed_methods"))
    {
        std::vector < std::string > vecAllowedMethods;
        for (unsigned i = 0; i < jsonContent["allowed_methods"].size(); ++i)
        {
            vecAllowedMethods.push_back(jsonContent["allowed_methods"][i].
                                        asString());
        }
        SetAllowedMethods(vecAllowedMethods);
    }
    if (jsonContent.isMember("allowed_origin"))
    {
        SetAllowedOrigin(jsonContent["allowed_origin"].asString());
    }
    if (jsonContent.isMember("expose_headers"))
    {
        std::vector < std::string > vecExposeHeaders;
        for (unsigned i = 0; i < jsonContent["expose_headers"].size(); ++i)
        {
            vecExposeHeaders.push_back(jsonContent["expose_headers"][i].
                                       asString());
        }
        SetExposeHeaders(vecExposeHeaders);
    }
    if (jsonContent.isMember("max_age_seconds"))
    {
        SetMaxAgeSeconds(jsonContent["max_age_seconds"].asInt());
    }
}

std::string CORSRuleType::Serialize()
{
    Json::Value jsonContent;
    Json::FastWriter jsonWriter;
    if (m_settingFlag & SETTING_CORS_RULE_ALLOWED_HEADERS_FLAG)
    {
        Json::Value arrayAllowedHeaders;
        std::vector < std::string > allowedHeaders = m_AllowedHeaders;
        for (std::vector < std::string >::iterator it = allowedHeaders.begin();
                it != allowedHeaders.end(); it++)
        {
            arrayAllowedHeaders.append(*it);
        }
        jsonContent["allowed_headers"] = arrayAllowedHeaders;
    }
    if (m_settingFlag & SETTING_CORS_RULE_ALLOWED_METHODS_FLAG)
    {
        Json::Value arrayAllowedMethods;
        std::vector < std::string > allowedMethods = m_AllowedMethods;
        for (std::vector < std::string >::iterator it = allowedMethods.begin();
                it != allowedMethods.end(); it++)
        {
            arrayAllowedMethods.append(*it);
        }
        jsonContent["allowed_methods"] = arrayAllowedMethods;
    }
    if (m_settingFlag & SETTING_CORS_RULE_ALLOWED_ORIGIN_FLAG)
    {
        jsonContent["allowed_origin"] = m_AllowedOrigin;
    }
    if (m_settingFlag & SETTING_CORS_RULE_EXPOSE_HEADERS_FLAG)
    {
        Json::Value arrayExposeHeaders;
        std::vector < std::string > exposeHeaders = m_ExposeHeaders;
        for (std::vector < std::string >::iterator it = exposeHeaders.begin();
                it != exposeHeaders.end(); it++)
        {
            arrayExposeHeaders.append(*it);
        }
        jsonContent["expose_headers"] = arrayExposeHeaders;
    }
    if (m_settingFlag & SETTING_CORS_RULE_MAX_AGE_SECONDS_FLAG)
    {
        jsonContent["max_age_seconds"] = m_MaxAgeSeconds;
    }
    return jsonWriter.write(jsonContent);
}

#ifdef BUILD_C_STYLE_INTERFACE
ExpirationType::ExpirationType(qs_expiration_t expiration)
{
    if (expiration.days)
        SetDays(*expiration.days);
}

qs_expiration_t *ExpirationType::toCStyleObj()
{
    qs_expiration_t *expiration =
        (qs_expiration_t *) malloc(sizeof(qs_expiration_t));
    expiration->days = (int *) malloc(sizeof(int));
    *expiration->days = GetDays();
    return expiration;
}

#endif							// BUILD_C_STYLE_INTERFACE

ExpirationType::ExpirationType(std::string serializedString)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(serializedString, jsonContent);
    if (jsonContent.isMember("days"))
    {
        SetDays(jsonContent["days"].asInt());
    }
}

std::string ExpirationType::Serialize()
{
    Json::Value jsonContent;
    Json::FastWriter jsonWriter;
    if (m_settingFlag & SETTING_EXPIRATION_DAYS_FLAG)
    {
        jsonContent["days"] = m_Days;
    }
    return jsonWriter.write(jsonContent);
}

#ifdef BUILD_C_STYLE_INTERFACE
FilterType::FilterType(qs_filter_t filter)
{
    if (filter.prefix)
        SetPrefix(filter.prefix);
}

qs_filter_t *FilterType::toCStyleObj()
{
    qs_filter_t *filter = (qs_filter_t *) malloc(sizeof(qs_filter_t));
    int prefixLength = 0;
    prefixLength = GetPrefix().length();
    if (prefixLength > 0)
    {
        filter->prefix = (char *) malloc(prefixLength + 1);
        memset(filter->prefix, 0, prefixLength + 1);
        strncpy(filter->prefix, GetPrefix().c_str(), prefixLength);
    }
    else
    {
        filter->prefix = NULL;
    }
    return filter;
}

#endif							// BUILD_C_STYLE_INTERFACE

FilterType::FilterType(std::string serializedString)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(serializedString, jsonContent);
    if (jsonContent.isMember("prefix"))
    {
        SetPrefix(jsonContent["prefix"].asString());
    }
}

std::string FilterType::Serialize()
{
    Json::Value jsonContent;
    Json::FastWriter jsonWriter;
    if (m_settingFlag & SETTING_FILTER_PREFIX_FLAG)
    {
        jsonContent["prefix"] = m_Prefix;
    }
    return jsonWriter.write(jsonContent);
}

#ifdef BUILD_C_STYLE_INTERFACE
GranteeType::GranteeType(qs_grantee_t grantee)
{
    if (grantee.id)
        SetID(grantee.id);
    if (grantee.name)
        SetName(grantee.name);
    if (grantee.type)
        SetType(grantee.type);
}

qs_grantee_t *GranteeType::toCStyleObj()
{
    qs_grantee_t *grantee = (qs_grantee_t *) malloc(sizeof(qs_grantee_t));
    int idLength = 0;
    idLength = GetID().length();
    if (idLength > 0)
    {
        grantee->id = (char *) malloc(idLength + 1);
        memset(grantee->id, 0, idLength + 1);
        strncpy(grantee->id, GetID().c_str(), idLength);
    }
    else
    {
        grantee->id = NULL;
    }
    int nameLength = 0;
    nameLength = GetName().length();
    if (nameLength > 0)
    {
        grantee->name = (char *) malloc(nameLength + 1);
        memset(grantee->name, 0, nameLength + 1);
        strncpy(grantee->name, GetName().c_str(), nameLength);
    }
    else
    {
        grantee->name = NULL;
    }
    int typeLength = 0;
    typeLength = GetType().length();
    if (typeLength > 0)
    {
        grantee->type = (char *) malloc(typeLength + 1);
        memset(grantee->type, 0, typeLength + 1);
        strncpy(grantee->type, GetType().c_str(), typeLength);
    }
    else
    {
        grantee->type = NULL;
    }
    return grantee;
}

#endif							// BUILD_C_STYLE_INTERFACE

GranteeType::GranteeType(std::string serializedString)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(serializedString, jsonContent);
    if (jsonContent.isMember("id"))
    {
        SetID(jsonContent["id"].asString());
    }
    if (jsonContent.isMember("name"))
    {
        SetName(jsonContent["name"].asString());
    }
    if (jsonContent.isMember("type"))
    {
        SetType(jsonContent["type"].asString());
    }
}

std::string GranteeType::Serialize()
{
    Json::Value jsonContent;
    Json::FastWriter jsonWriter;
    if (m_settingFlag & SETTING_GRANTEE_ID_FLAG)
    {
        jsonContent["id"] = m_ID;
    }
    if (m_settingFlag & SETTING_GRANTEE_NAME_FLAG)
    {
        jsonContent["name"] = m_Name;
    }
    if (m_settingFlag & SETTING_GRANTEE_TYPE_FLAG)
    {
        jsonContent["type"] = m_Type;
    }
    return jsonWriter.write(jsonContent);
}

#ifdef BUILD_C_STYLE_INTERFACE
IPAddressType::IPAddressType(qs_ip_address_t ip_address)
{
    if (ip_address.source_ip)
        SetSourceIP(ip_address.source_ip);
}

qs_ip_address_t *IPAddressType::toCStyleObj()
{
    qs_ip_address_t *ip_address =
        (qs_ip_address_t *) malloc(sizeof(qs_ip_address_t));
    qs_list_t *list_source_ip = (qs_list_t *) malloc(sizeof(qs_list_t));
    qs_list_init(list_source_ip);
    std::vector < std::string > sourceIP = GetSourceIP();
    for (std::vector < std::string >::iterator it = sourceIP.begin();
            it != sourceIP.end(); it++)
    {
        qs_ip_address_source_ip_item_t *item =
            (qs_ip_address_source_ip_item_t *)
            malloc(sizeof(qs_ip_address_source_ip_item_t));
        int sourceIPLength = it->length();
        if (sourceIPLength > 0)
        {
            item->content = (char *) malloc(sourceIPLength + 1);
            memset(item->content, 0, sourceIPLength + 1);
            strncpy(item->content, it->c_str(), sourceIPLength);
        }
        else
        {
            item->content = NULL;
        }
        qs_list_append(&item->node, list_source_ip);
    }
    ip_address->source_ip = list_source_ip;
    return ip_address;
}

#endif							// BUILD_C_STYLE_INTERFACE

IPAddressType::IPAddressType(std::string serializedString)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(serializedString, jsonContent);
    if (jsonContent.isMember("source_ip"))
    {
        std::vector < std::string > vecSourceIP;
        for (unsigned i = 0; i < jsonContent["source_ip"].size(); ++i)
        {
            vecSourceIP.push_back(jsonContent["source_ip"][i].asString());
        }
        SetSourceIP(vecSourceIP);
    }
}

std::string IPAddressType::Serialize()
{
    Json::Value jsonContent;
    Json::FastWriter jsonWriter;
    if (m_settingFlag & SETTING_IP_ADDRESS_SOURCE_IP_FLAG)
    {
        Json::Value arraySourceIP;
        std::vector < std::string > sourceIP = m_SourceIP;
        for (std::vector < std::string >::iterator it = sourceIP.begin();
                it != sourceIP.end(); it++)
        {
            arraySourceIP.append(*it);
        }
        jsonContent["source_ip"] = arraySourceIP;
    }
    return jsonWriter.write(jsonContent);
}

#ifdef BUILD_C_STYLE_INTERFACE
IsNullType::IsNullType(qs_is_null_t is_null)
{
    if (is_null.referer)
        SetReferer(*is_null.referer);
}

qs_is_null_t *IsNullType::toCStyleObj()
{
    qs_is_null_t *is_null = (qs_is_null_t *) malloc(sizeof(qs_is_null_t));
    is_null->referer = (bool *) malloc(sizeof(bool));
    *is_null->referer = GetReferer();
    return is_null;
}

#endif							// BUILD_C_STYLE_INTERFACE

IsNullType::IsNullType(std::string serializedString)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(serializedString, jsonContent);
    if (jsonContent.isMember("Referer"))
    {
        SetReferer(jsonContent["Referer"].asBool());
    }
}

std::string IsNullType::Serialize()
{
    Json::Value jsonContent;
    Json::FastWriter jsonWriter;
    if (m_settingFlag & SETTING_IS_NULL_REFERER_FLAG)
    {
        jsonContent["Referer"] = m_Referer;
    }
    return jsonWriter.write(jsonContent);
}

#ifdef BUILD_C_STYLE_INTERFACE
KeyType::KeyType(qs_key_t key)
{
    if (key.created)
        SetCreated(key.created);
    if (key.encrypted)
        SetEncrypted(*key.encrypted);
    if (key.etag)
        SetEtag(key.etag);
    if (key.key)
        SetKey(key.key);
    if (key.mime_type)
        SetMimeType(key.mime_type);
    if (key.modified)
        SetModified(*key.modified);
    if (key.size)
        SetSize(*key.size);
}

qs_key_t *KeyType::toCStyleObj()
{
    qs_key_t *key = (qs_key_t *) malloc(sizeof(qs_key_t));
    int createdLength = 0;
    createdLength = GetCreated().length();
    if (createdLength > 0)
    {
        key->created = (char *) malloc(createdLength + 1);
        memset(key->created, 0, createdLength + 1);
        strncpy(key->created, GetCreated().c_str(), createdLength);
    }
    else
    {
        key->created = NULL;
    }
    key->encrypted = (bool *) malloc(sizeof(bool));
    *key->encrypted = GetEncrypted();
    int etagLength = 0;
    etagLength = GetEtag().length();
    if (etagLength > 0)
    {
        key->etag = (char *) malloc(etagLength + 1);
        memset(key->etag, 0, etagLength + 1);
        strncpy(key->etag, GetEtag().c_str(), etagLength);
    }
    else
    {
        key->etag = NULL;
    }
    int keyLength = 0;
    keyLength = GetKey().length();
    if (keyLength > 0)
    {
        key->key = (char *) malloc(keyLength + 1);
        memset(key->key, 0, keyLength + 1);
        strncpy(key->key, GetKey().c_str(), keyLength);
    }
    else
    {
        key->key = NULL;
    }
    int mimeTypeLength = 0;
    mimeTypeLength = GetMimeType().length();
    if (mimeTypeLength > 0)
    {
        key->mime_type = (char *) malloc(mimeTypeLength + 1);
        memset(key->mime_type, 0, mimeTypeLength + 1);
        strncpy(key->mime_type, GetMimeType().c_str(), mimeTypeLength);
    }
    else
    {
        key->mime_type = NULL;
    }
    key->modified = (int *) malloc(sizeof(int));
    *key->modified = GetModified();
    key->size = (long *) malloc(sizeof(long));
    *key->size = GetSize();
    return key;
}

#endif							// BUILD_C_STYLE_INTERFACE

KeyType::KeyType(std::string serializedString)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(serializedString, jsonContent);
    if (jsonContent.isMember("created"))
    {
        SetCreated(jsonContent["created"].asString());
    }
    if (jsonContent.isMember("encrypted"))
    {
        SetEncrypted(jsonContent["encrypted"].asBool());
    }
    if (jsonContent.isMember("etag"))
    {
        SetEtag(jsonContent["etag"].asString());
    }
    if (jsonContent.isMember("key"))
    {
        SetKey(jsonContent["key"].asString());
    }
    if (jsonContent.isMember("mime_type"))
    {
        SetMimeType(jsonContent["mime_type"].asString());
    }
    if (jsonContent.isMember("modified"))
    {
        SetModified(jsonContent["modified"].asInt());
    }
    if (jsonContent.isMember("size"))
    {
        SetSize(jsonContent["size"].asInt64());
    }
}

std::string KeyType::Serialize()
{
    Json::Value jsonContent;
    Json::FastWriter jsonWriter;
    if (m_settingFlag & SETTING_KEY_CREATED_FLAG)
    {
        jsonContent["created"] = m_Created;
    }
    if (m_settingFlag & SETTING_KEY_ENCRYPTED_FLAG)
    {
        jsonContent["encrypted"] = m_Encrypted;
    }
    if (m_settingFlag & SETTING_KEY_ETAG_FLAG)
    {
        jsonContent["etag"] = m_Etag;
    }
    if (m_settingFlag & SETTING_KEY_KEY_FLAG)
    {
        jsonContent["key"] = m_Key;
    }
    if (m_settingFlag & SETTING_KEY_MIME_TYPE_FLAG)
    {
        jsonContent["mime_type"] = m_MimeType;
    }
    if (m_settingFlag & SETTING_KEY_MODIFIED_FLAG)
    {
        jsonContent["modified"] = m_Modified;
    }
    if (m_settingFlag & SETTING_KEY_SIZE_FLAG)
    {
        jsonContent["size"] = (Json::Int64) m_Size;
    }
    return jsonWriter.write(jsonContent);
}

#ifdef BUILD_C_STYLE_INTERFACE
KeyDeleteErrorType::KeyDeleteErrorType(qs_key_delete_error_t key_delete_error)
{
    if (key_delete_error.code)
        SetCode(key_delete_error.code);
    if (key_delete_error.key)
        SetKey(key_delete_error.key);
    if (key_delete_error.message)
        SetMessage(key_delete_error.message);
}

qs_key_delete_error_t *KeyDeleteErrorType::toCStyleObj()
{
    qs_key_delete_error_t *key_delete_error =
        (qs_key_delete_error_t *) malloc(sizeof(qs_key_delete_error_t));
    int codeLength = 0;
    codeLength = GetCode().length();
    if (codeLength > 0)
    {
        key_delete_error->code = (char *) malloc(codeLength + 1);
        memset(key_delete_error->code, 0, codeLength + 1);
        strncpy(key_delete_error->code, GetCode().c_str(), codeLength);
    }
    else
    {
        key_delete_error->code = NULL;
    }
    int keyLength = 0;
    keyLength = GetKey().length();
    if (keyLength > 0)
    {
        key_delete_error->key = (char *) malloc(keyLength + 1);
        memset(key_delete_error->key, 0, keyLength + 1);
        strncpy(key_delete_error->key, GetKey().c_str(), keyLength);
    }
    else
    {
        key_delete_error->key = NULL;
    }
    int messageLength = 0;
    messageLength = GetMessage().length();
    if (messageLength > 0)
    {
        key_delete_error->message = (char *) malloc(messageLength + 1);
        memset(key_delete_error->message, 0, messageLength + 1);
        strncpy(key_delete_error->message, GetMessage().c_str(), messageLength);
    }
    else
    {
        key_delete_error->message = NULL;
    }
    return key_delete_error;
}

#endif							// BUILD_C_STYLE_INTERFACE

KeyDeleteErrorType::KeyDeleteErrorType(std::string serializedString)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(serializedString, jsonContent);
    if (jsonContent.isMember("code"))
    {
        SetCode(jsonContent["code"].asString());
    }
    if (jsonContent.isMember("key"))
    {
        SetKey(jsonContent["key"].asString());
    }
    if (jsonContent.isMember("message"))
    {
        SetMessage(jsonContent["message"].asString());
    }
}

std::string KeyDeleteErrorType::Serialize()
{
    Json::Value jsonContent;
    Json::FastWriter jsonWriter;
    if (m_settingFlag & SETTING_KEY_DELETE_ERROR_CODE_FLAG)
    {
        jsonContent["code"] = m_Code;
    }
    if (m_settingFlag & SETTING_KEY_DELETE_ERROR_KEY_FLAG)
    {
        jsonContent["key"] = m_Key;
    }
    if (m_settingFlag & SETTING_KEY_DELETE_ERROR_MESSAGE_FLAG)
    {
        jsonContent["message"] = m_Message;
    }
    return jsonWriter.write(jsonContent);
}

#ifdef BUILD_C_STYLE_INTERFACE
NotIPAddressType::NotIPAddressType(qs_not_ip_address_t not_ip_address)
{
    if (not_ip_address.source_ip)
        SetSourceIP(not_ip_address.source_ip);
}

qs_not_ip_address_t *NotIPAddressType::toCStyleObj()
{
    qs_not_ip_address_t *not_ip_address =
        (qs_not_ip_address_t *) malloc(sizeof(qs_not_ip_address_t));
    qs_list_t *list_source_ip = (qs_list_t *) malloc(sizeof(qs_list_t));
    qs_list_init(list_source_ip);
    std::vector < std::string > sourceIP = GetSourceIP();
    for (std::vector < std::string >::iterator it = sourceIP.begin();
            it != sourceIP.end(); it++)
    {
        qs_not_ip_address_source_ip_item_t *item =
            (qs_not_ip_address_source_ip_item_t *)
            malloc(sizeof(qs_not_ip_address_source_ip_item_t));
        int sourceIPLength = it->length();
        if (sourceIPLength > 0)
        {
            item->content = (char *) malloc(sourceIPLength + 1);
            memset(item->content, 0, sourceIPLength + 1);
            strncpy(item->content, it->c_str(), sourceIPLength);
        }
        else
        {
            item->content = NULL;
        }
        qs_list_append(&item->node, list_source_ip);
    }
    not_ip_address->source_ip = list_source_ip;
    return not_ip_address;
}

#endif							// BUILD_C_STYLE_INTERFACE

NotIPAddressType::NotIPAddressType(std::string serializedString)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(serializedString, jsonContent);
    if (jsonContent.isMember("source_ip"))
    {
        std::vector < std::string > vecSourceIP;
        for (unsigned i = 0; i < jsonContent["source_ip"].size(); ++i)
        {
            vecSourceIP.push_back(jsonContent["source_ip"][i].asString());
        }
        SetSourceIP(vecSourceIP);
    }
}

std::string NotIPAddressType::Serialize()
{
    Json::Value jsonContent;
    Json::FastWriter jsonWriter;
    if (m_settingFlag & SETTING_NOT_IP_ADDRESS_SOURCE_IP_FLAG)
    {
        Json::Value arraySourceIP;
        std::vector < std::string > sourceIP = m_SourceIP;
        for (std::vector < std::string >::iterator it = sourceIP.begin();
                it != sourceIP.end(); it++)
        {
            arraySourceIP.append(*it);
        }
        jsonContent["source_ip"] = arraySourceIP;
    }
    return jsonWriter.write(jsonContent);
}

#ifdef BUILD_C_STYLE_INTERFACE
NotificationType::NotificationType(qs_notification_t notification)
{
    if (notification.cloudfunc)
        SetCloudfunc(notification.cloudfunc);
    if (notification.cloudfunc_args)
        SetCloudfuncArgs(*notification.cloudfunc_args);
    if (notification.event_types)
        SetEventTypes(notification.event_types);
    if (notification.id)
        SetID(notification.id);
    if (notification.notify_url)
        SetNotifyURL(notification.notify_url);
    if (notification.object_filters)
        SetObjectFilters(notification.object_filters);
}

qs_notification_t *NotificationType::toCStyleObj()
{
    qs_notification_t *notification =
        (qs_notification_t *) malloc(sizeof(qs_notification_t));
    int cloudfuncLength = 0;
    cloudfuncLength = GetCloudfunc().length();
    if (cloudfuncLength > 0)
    {
        notification->cloudfunc = (char *) malloc(cloudfuncLength + 1);
        memset(notification->cloudfunc, 0, cloudfuncLength + 1);
        strncpy(notification->cloudfunc, GetCloudfunc().c_str(),
                cloudfuncLength);
    }
    else
    {
        notification->cloudfunc = NULL;
    }
    notification->cloudfunc_args = GetCloudfuncArgs().toCStyleObj();
    qs_list_t *list_event_types = (qs_list_t *) malloc(sizeof(qs_list_t));
    qs_list_init(list_event_types);
    std::vector < std::string > eventTypes = GetEventTypes();
    for (std::vector < std::string >::iterator it = eventTypes.begin();
            it != eventTypes.end(); it++)
    {
        qs_notification_event_types_item_t *item =
            (qs_notification_event_types_item_t *)
            malloc(sizeof(qs_notification_event_types_item_t));
        int eventTypesLength = it->length();
        if (eventTypesLength > 0)
        {
            item->content = (char *) malloc(eventTypesLength + 1);
            memset(item->content, 0, eventTypesLength + 1);
            strncpy(item->content, it->c_str(), eventTypesLength);
        }
        else
        {
            item->content = NULL;
        }
        qs_list_append(&item->node, list_event_types);
    }
    notification->event_types = list_event_types;
    int idLength = 0;
    idLength = GetID().length();
    if (idLength > 0)
    {
        notification->id = (char *) malloc(idLength + 1);
        memset(notification->id, 0, idLength + 1);
        strncpy(notification->id, GetID().c_str(), idLength);
    }
    else
    {
        notification->id = NULL;
    }
    int notifyURLLength = 0;
    notifyURLLength = GetNotifyURL().length();
    if (notifyURLLength > 0)
    {
        notification->notify_url = (char *) malloc(notifyURLLength + 1);
        memset(notification->notify_url, 0, notifyURLLength + 1);
        strncpy(notification->notify_url, GetNotifyURL().c_str(),
                notifyURLLength);
    }
    else
    {
        notification->notify_url = NULL;
    }
    qs_list_t *list_object_filters = (qs_list_t *) malloc(sizeof(qs_list_t));
    qs_list_init(list_object_filters);
    std::vector < std::string > objectFilters = GetObjectFilters();
    for (std::vector < std::string >::iterator it = objectFilters.begin();
            it != objectFilters.end(); it++)
    {
        qs_notification_object_filters_item_t *item =
            (qs_notification_object_filters_item_t *)
            malloc(sizeof(qs_notification_object_filters_item_t));
        int objectFiltersLength = it->length();
        if (objectFiltersLength > 0)
        {
            item->content = (char *) malloc(objectFiltersLength + 1);
            memset(item->content, 0, objectFiltersLength + 1);
            strncpy(item->content, it->c_str(), objectFiltersLength);
        }
        else
        {
            item->content = NULL;
        }
        qs_list_append(&item->node, list_object_filters);
    }
    notification->object_filters = list_object_filters;
    return notification;
}

#endif							// BUILD_C_STYLE_INTERFACE

NotificationType::NotificationType(std::string serializedString)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(serializedString, jsonContent);
    if (jsonContent.isMember("cloudfunc"))
    {
        SetCloudfunc(jsonContent["cloudfunc"].asString());
    }
    if (jsonContent.isMember("cloudfunc_args"))
    {
        SetCloudfuncArgs(jsonContent["cloudfunc_args"].toStyledString());
    }
    if (jsonContent.isMember("event_types"))
    {
        std::vector < std::string > vecEventTypes;
        for (unsigned i = 0; i < jsonContent["event_types"].size(); ++i)
        {
            vecEventTypes.push_back(jsonContent["event_types"][i].asString());
        }
        SetEventTypes(vecEventTypes);
    }
    if (jsonContent.isMember("id"))
    {
        SetID(jsonContent["id"].asString());
    }
    if (jsonContent.isMember("notify_url"))
    {
        SetNotifyURL(jsonContent["notify_url"].asString());
    }
    if (jsonContent.isMember("object_filters"))
    {
        std::vector < std::string > vecObjectFilters;
        for (unsigned i = 0; i < jsonContent["object_filters"].size(); ++i)
        {
            vecObjectFilters.push_back(jsonContent["object_filters"][i].
                                       asString());
        }
        SetObjectFilters(vecObjectFilters);
    }
}

std::string NotificationType::Serialize()
{
    Json::Value jsonContent;
    Json::FastWriter jsonWriter;
    if (m_settingFlag & SETTING_NOTIFICATION_CLOUDFUNC_FLAG)
    {
        jsonContent["cloudfunc"] = m_Cloudfunc;
    }
    if (m_settingFlag & SETTING_NOTIFICATION_CLOUDFUNC_ARGS_FLAG)
    {
        Json::Reader jsonReader;
        Json::Value itemJsonValue;
        jsonReader.parse(m_CloudfuncArgs.Serialize(), itemJsonValue);
        jsonContent["cloudfunc_args"] = itemJsonValue;
    }
    if (m_settingFlag & SETTING_NOTIFICATION_EVENT_TYPES_FLAG)
    {
        Json::Value arrayEventTypes;
        std::vector < std::string > eventTypes = m_EventTypes;
        for (std::vector < std::string >::iterator it = eventTypes.begin();
                it != eventTypes.end(); it++)
        {
            arrayEventTypes.append(*it);
        }
        jsonContent["event_types"] = arrayEventTypes;
    }
    if (m_settingFlag & SETTING_NOTIFICATION_ID_FLAG)
    {
        jsonContent["id"] = m_ID;
    }
    if (m_settingFlag & SETTING_NOTIFICATION_NOTIFY_URL_FLAG)
    {
        jsonContent["notify_url"] = m_NotifyURL;
    }
    if (m_settingFlag & SETTING_NOTIFICATION_OBJECT_FILTERS_FLAG)
    {
        Json::Value arrayObjectFilters;
        std::vector < std::string > objectFilters = m_ObjectFilters;
        for (std::vector < std::string >::iterator it = objectFilters.begin();
                it != objectFilters.end(); it++)
        {
            arrayObjectFilters.append(*it);
        }
        jsonContent["object_filters"] = arrayObjectFilters;
    }
    return jsonWriter.write(jsonContent);
}

#ifdef BUILD_C_STYLE_INTERFACE
ObjectPartType::ObjectPartType(qs_object_part_t object_part)
{
    if (object_part.created)
        SetCreated(object_part.created);
    if (object_part.etag)
        SetEtag(object_part.etag);
    if (object_part.part_number)
        SetPartNumber(*object_part.part_number);
    if (object_part.size)
        SetSize(*object_part.size);
}

qs_object_part_t *ObjectPartType::toCStyleObj()
{
    qs_object_part_t *object_part =
        (qs_object_part_t *) malloc(sizeof(qs_object_part_t));
    int createdLength = 0;
    createdLength = GetCreated().length();
    if (createdLength > 0)
    {
        object_part->created = (char *) malloc(createdLength + 1);
        memset(object_part->created, 0, createdLength + 1);
        strncpy(object_part->created, GetCreated().c_str(), createdLength);
    }
    else
    {
        object_part->created = NULL;
    }
    int etagLength = 0;
    etagLength = GetEtag().length();
    if (etagLength > 0)
    {
        object_part->etag = (char *) malloc(etagLength + 1);
        memset(object_part->etag, 0, etagLength + 1);
        strncpy(object_part->etag, GetEtag().c_str(), etagLength);
    }
    else
    {
        object_part->etag = NULL;
    }
    object_part->part_number = (int *) malloc(sizeof(int));
    *object_part->part_number = GetPartNumber();
    object_part->size = (long *) malloc(sizeof(long));
    *object_part->size = GetSize();
    return object_part;
}

#endif							// BUILD_C_STYLE_INTERFACE

ObjectPartType::ObjectPartType(std::string serializedString)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(serializedString, jsonContent);
    if (jsonContent.isMember("created"))
    {
        SetCreated(jsonContent["created"].asString());
    }
    if (jsonContent.isMember("etag"))
    {
        SetEtag(jsonContent["etag"].asString());
    }
    if (jsonContent.isMember("part_number"))
    {
        SetPartNumber(jsonContent["part_number"].asInt());
    }
    if (jsonContent.isMember("size"))
    {
        SetSize(jsonContent["size"].asInt64());
    }
}

std::string ObjectPartType::Serialize()
{
    Json::Value jsonContent;
    Json::FastWriter jsonWriter;
    if (m_settingFlag & SETTING_OBJECT_PART_CREATED_FLAG)
    {
        jsonContent["created"] = m_Created;
    }
    if (m_settingFlag & SETTING_OBJECT_PART_ETAG_FLAG)
    {
        jsonContent["etag"] = m_Etag;
    }
    if (m_settingFlag & SETTING_OBJECT_PART_PART_NUMBER_FLAG)
    {
        jsonContent["part_number"] = m_PartNumber;
    }
    if (m_settingFlag & SETTING_OBJECT_PART_SIZE_FLAG)
    {
        jsonContent["size"] = (Json::Int64) m_Size;
    }
    return jsonWriter.write(jsonContent);
}

#ifdef BUILD_C_STYLE_INTERFACE
OwnerType::OwnerType(qs_owner_t owner)
{
    if (owner.id)
        SetID(owner.id);
    if (owner.name)
        SetName(owner.name);
}

qs_owner_t *OwnerType::toCStyleObj()
{
    qs_owner_t *owner = (qs_owner_t *) malloc(sizeof(qs_owner_t));
    int idLength = 0;
    idLength = GetID().length();
    if (idLength > 0)
    {
        owner->id = (char *) malloc(idLength + 1);
        memset(owner->id, 0, idLength + 1);
        strncpy(owner->id, GetID().c_str(), idLength);
    }
    else
    {
        owner->id = NULL;
    }
    int nameLength = 0;
    nameLength = GetName().length();
    if (nameLength > 0)
    {
        owner->name = (char *) malloc(nameLength + 1);
        memset(owner->name, 0, nameLength + 1);
        strncpy(owner->name, GetName().c_str(), nameLength);
    }
    else
    {
        owner->name = NULL;
    }
    return owner;
}

#endif							// BUILD_C_STYLE_INTERFACE

OwnerType::OwnerType(std::string serializedString)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(serializedString, jsonContent);
    if (jsonContent.isMember("id"))
    {
        SetID(jsonContent["id"].asString());
    }
    if (jsonContent.isMember("name"))
    {
        SetName(jsonContent["name"].asString());
    }
}

std::string OwnerType::Serialize()
{
    Json::Value jsonContent;
    Json::FastWriter jsonWriter;
    if (m_settingFlag & SETTING_OWNER_ID_FLAG)
    {
        jsonContent["id"] = m_ID;
    }
    if (m_settingFlag & SETTING_OWNER_NAME_FLAG)
    {
        jsonContent["name"] = m_Name;
    }
    return jsonWriter.write(jsonContent);
}

#ifdef BUILD_C_STYLE_INTERFACE
RuleType::RuleType(qs_rule_t rule)
{
    if (rule.abort_incomplete_multipart_upload)
        SetAbortIncompleteMultipartUpload(*rule.
                                          abort_incomplete_multipart_upload);
    if (rule.expiration)
        SetExpiration(*rule.expiration);
    if (rule.filter)
        SetFilter(*rule.filter);
    if (rule.id)
        SetID(rule.id);
    if (rule.status)
        SetStatus(rule.status);
    if (rule.transition)
        SetTransition(*rule.transition);
}

qs_rule_t *RuleType::toCStyleObj()
{
    qs_rule_t *rule = (qs_rule_t *) malloc(sizeof(qs_rule_t));
    rule->abort_incomplete_multipart_upload =
        GetAbortIncompleteMultipartUpload().toCStyleObj();
    rule->expiration = GetExpiration().toCStyleObj();
    rule->filter = GetFilter().toCStyleObj();
    int idLength = 0;
    idLength = GetID().length();
    if (idLength > 0)
    {
        rule->id = (char *) malloc(idLength + 1);
        memset(rule->id, 0, idLength + 1);
        strncpy(rule->id, GetID().c_str(), idLength);
    }
    else
    {
        rule->id = NULL;
    }
    int statusLength = 0;
    statusLength = GetStatus().length();
    if (statusLength > 0)
    {
        rule->status = (char *) malloc(statusLength + 1);
        memset(rule->status, 0, statusLength + 1);
        strncpy(rule->status, GetStatus().c_str(), statusLength);
    }
    else
    {
        rule->status = NULL;
    }
    rule->transition = GetTransition().toCStyleObj();
    return rule;
}

#endif							// BUILD_C_STYLE_INTERFACE

RuleType::RuleType(std::string serializedString)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(serializedString, jsonContent);
    if (jsonContent.isMember("abort_incomplete_multipart_upload"))
    {
        SetAbortIncompleteMultipartUpload(jsonContent
                                          ["abort_incomplete_multipart_upload"].
                                          toStyledString());
    }
    if (jsonContent.isMember("expiration"))
    {
        SetExpiration(jsonContent["expiration"].toStyledString());
    }
    if (jsonContent.isMember("filter"))
    {
        SetFilter(jsonContent["filter"].toStyledString());
    }
    if (jsonContent.isMember("id"))
    {
        SetID(jsonContent["id"].asString());
    }
    if (jsonContent.isMember("status"))
    {
        SetStatus(jsonContent["status"].asString());
    }
    if (jsonContent.isMember("transition"))
    {
        SetTransition(jsonContent["transition"].toStyledString());
    }
}

std::string RuleType::Serialize()
{
    Json::Value jsonContent;
    Json::FastWriter jsonWriter;
    if (m_settingFlag & SETTING_RULE_ABORT_INCOMPLETE_MULTIPART_UPLOAD_FLAG)
    {
        Json::Reader jsonReader;
        Json::Value itemJsonValue;
        jsonReader.parse(m_AbortIncompleteMultipartUpload.Serialize(),
                         itemJsonValue);
        jsonContent["abort_incomplete_multipart_upload"] = itemJsonValue;
    }
    if (m_settingFlag & SETTING_RULE_EXPIRATION_FLAG)
    {
        Json::Reader jsonReader;
        Json::Value itemJsonValue;
        jsonReader.parse(m_Expiration.Serialize(), itemJsonValue);
        jsonContent["expiration"] = itemJsonValue;
    }
    if (m_settingFlag & SETTING_RULE_FILTER_FLAG)
    {
        Json::Reader jsonReader;
        Json::Value itemJsonValue;
        jsonReader.parse(m_Filter.Serialize(), itemJsonValue);
        jsonContent["filter"] = itemJsonValue;
    }
    if (m_settingFlag & SETTING_RULE_ID_FLAG)
    {
        jsonContent["id"] = m_ID;
    }
    if (m_settingFlag & SETTING_RULE_STATUS_FLAG)
    {
        jsonContent["status"] = m_Status;
    }
    if (m_settingFlag & SETTING_RULE_TRANSITION_FLAG)
    {
        Json::Reader jsonReader;
        Json::Value itemJsonValue;
        jsonReader.parse(m_Transition.Serialize(), itemJsonValue);
        jsonContent["transition"] = itemJsonValue;
    }
    return jsonWriter.write(jsonContent);
}

#ifdef BUILD_C_STYLE_INTERFACE
StatementType::StatementType(qs_statement_t statement)
{
    if (statement.action)
        SetAction(statement.action);
    if (statement.condition)
        SetCondition(*statement.condition);
    if (statement.effect)
        SetEffect(statement.effect);
    if (statement.id)
        SetID(statement.id);
    if (statement.resource)
        SetResource(statement.resource);
    if (statement.user)
        SetUser(statement.user);
}

qs_statement_t *StatementType::toCStyleObj()
{
    qs_statement_t *statement =
        (qs_statement_t *) malloc(sizeof(qs_statement_t));
    qs_list_t *list_action = (qs_list_t *) malloc(sizeof(qs_list_t));
    qs_list_init(list_action);
    std::vector < std::string > action = GetAction();
    for (std::vector < std::string >::iterator it = action.begin();
            it != action.end(); it++)
    {
        qs_statement_action_item_t *item =
            (qs_statement_action_item_t *)
            malloc(sizeof(qs_statement_action_item_t));
        int actionLength = it->length();
        if (actionLength > 0)
        {
            item->content = (char *) malloc(actionLength + 1);
            memset(item->content, 0, actionLength + 1);
            strncpy(item->content, it->c_str(), actionLength);
        }
        else
        {
            item->content = NULL;
        }
        qs_list_append(&item->node, list_action);
    }
    statement->action = list_action;
    statement->condition = GetCondition().toCStyleObj();
    int effectLength = 0;
    effectLength = GetEffect().length();
    if (effectLength > 0)
    {
        statement->effect = (char *) malloc(effectLength + 1);
        memset(statement->effect, 0, effectLength + 1);
        strncpy(statement->effect, GetEffect().c_str(), effectLength);
    }
    else
    {
        statement->effect = NULL;
    }
    int idLength = 0;
    idLength = GetID().length();
    if (idLength > 0)
    {
        statement->id = (char *) malloc(idLength + 1);
        memset(statement->id, 0, idLength + 1);
        strncpy(statement->id, GetID().c_str(), idLength);
    }
    else
    {
        statement->id = NULL;
    }
    qs_list_t *list_resource = (qs_list_t *) malloc(sizeof(qs_list_t));
    qs_list_init(list_resource);
    std::vector < std::string > resource = GetResource();
    for (std::vector < std::string >::iterator it = resource.begin();
            it != resource.end(); it++)
    {
        qs_statement_resource_item_t *item =
            (qs_statement_resource_item_t *)
            malloc(sizeof(qs_statement_resource_item_t));
        int resourceLength = it->length();
        if (resourceLength > 0)
        {
            item->content = (char *) malloc(resourceLength + 1);
            memset(item->content, 0, resourceLength + 1);
            strncpy(item->content, it->c_str(), resourceLength);
        }
        else
        {
            item->content = NULL;
        }
        qs_list_append(&item->node, list_resource);
    }
    statement->resource = list_resource;
    qs_list_t *list_user = (qs_list_t *) malloc(sizeof(qs_list_t));
    qs_list_init(list_user);
    std::vector < std::string > user = GetUser();
    for (std::vector < std::string >::iterator it = user.begin();
            it != user.end(); it++)
    {
        qs_statement_user_item_t *item =
            (qs_statement_user_item_t *)
            malloc(sizeof(qs_statement_user_item_t));
        int userLength = it->length();
        if (userLength > 0)
        {
            item->content = (char *) malloc(userLength + 1);
            memset(item->content, 0, userLength + 1);
            strncpy(item->content, it->c_str(), userLength);
        }
        else
        {
            item->content = NULL;
        }
        qs_list_append(&item->node, list_user);
    }
    statement->user = list_user;
    return statement;
}

#endif							// BUILD_C_STYLE_INTERFACE

StatementType::StatementType(std::string serializedString)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(serializedString, jsonContent);
    if (jsonContent.isMember("action"))
    {
        std::vector < std::string > vecAction;
        for (unsigned i = 0; i < jsonContent["action"].size(); ++i)
        {
            vecAction.push_back(jsonContent["action"][i].asString());
        }
        SetAction(vecAction);
    }
    if (jsonContent.isMember("condition"))
    {
        SetCondition(jsonContent["condition"].toStyledString());
    }
    if (jsonContent.isMember("effect"))
    {
        SetEffect(jsonContent["effect"].asString());
    }
    if (jsonContent.isMember("id"))
    {
        SetID(jsonContent["id"].asString());
    }
    if (jsonContent.isMember("resource"))
    {
        std::vector < std::string > vecResource;
        for (unsigned i = 0; i < jsonContent["resource"].size(); ++i)
        {
            vecResource.push_back(jsonContent["resource"][i].asString());
        }
        SetResource(vecResource);
    }
    if (jsonContent.isMember("user"))
    {
        std::vector < std::string > vecUser;
        for (unsigned i = 0; i < jsonContent["user"].size(); ++i)
        {
            vecUser.push_back(jsonContent["user"][i].asString());
        }
        SetUser(vecUser);
    }
}

std::string StatementType::Serialize()
{
    Json::Value jsonContent;
    Json::FastWriter jsonWriter;
    if (m_settingFlag & SETTING_STATEMENT_ACTION_FLAG)
    {
        Json::Value arrayAction;
        std::vector < std::string > action = m_Action;
        for (std::vector < std::string >::iterator it = action.begin();
                it != action.end(); it++)
        {
            arrayAction.append(*it);
        }
        jsonContent["action"] = arrayAction;
    }
    if (m_settingFlag & SETTING_STATEMENT_CONDITION_FLAG)
    {
        Json::Reader jsonReader;
        Json::Value itemJsonValue;
        jsonReader.parse(m_Condition.Serialize(), itemJsonValue);
        jsonContent["condition"] = itemJsonValue;
    }
    if (m_settingFlag & SETTING_STATEMENT_EFFECT_FLAG)
    {
        jsonContent["effect"] = m_Effect;
    }
    if (m_settingFlag & SETTING_STATEMENT_ID_FLAG)
    {
        jsonContent["id"] = m_ID;
    }
    if (m_settingFlag & SETTING_STATEMENT_RESOURCE_FLAG)
    {
        Json::Value arrayResource;
        std::vector < std::string > resource = m_Resource;
        for (std::vector < std::string >::iterator it = resource.begin();
                it != resource.end(); it++)
        {
            arrayResource.append(*it);
        }
        jsonContent["resource"] = arrayResource;
    }
    if (m_settingFlag & SETTING_STATEMENT_USER_FLAG)
    {
        Json::Value arrayUser;
        std::vector < std::string > user = m_User;
        for (std::vector < std::string >::iterator it = user.begin();
                it != user.end(); it++)
        {
            arrayUser.append(*it);
        }
        jsonContent["user"] = arrayUser;
    }
    return jsonWriter.write(jsonContent);
}

#ifdef BUILD_C_STYLE_INTERFACE
StringLikeType::StringLikeType(qs_string_like_t string_like)
{
    if (string_like.referer)
        SetReferer(string_like.referer);
}

qs_string_like_t *StringLikeType::toCStyleObj()
{
    qs_string_like_t *string_like =
        (qs_string_like_t *) malloc(sizeof(qs_string_like_t));
    qs_list_t *list_referer = (qs_list_t *) malloc(sizeof(qs_list_t));
    qs_list_init(list_referer);
    std::vector < std::string > referer = GetReferer();
    for (std::vector < std::string >::iterator it = referer.begin();
            it != referer.end(); it++)
    {
        qs_string_like_referer_item_t *item =
            (qs_string_like_referer_item_t *)
            malloc(sizeof(qs_string_like_referer_item_t));
        int refererLength = it->length();
        if (refererLength > 0)
        {
            item->content = (char *) malloc(refererLength + 1);
            memset(item->content, 0, refererLength + 1);
            strncpy(item->content, it->c_str(), refererLength);
        }
        else
        {
            item->content = NULL;
        }
        qs_list_append(&item->node, list_referer);
    }
    string_like->referer = list_referer;
    return string_like;
}

#endif							// BUILD_C_STYLE_INTERFACE

StringLikeType::StringLikeType(std::string serializedString)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(serializedString, jsonContent);
    if (jsonContent.isMember("Referer"))
    {
        std::vector < std::string > vecReferer;
        for (unsigned i = 0; i < jsonContent["Referer"].size(); ++i)
        {
            vecReferer.push_back(jsonContent["Referer"][i].asString());
        }
        SetReferer(vecReferer);
    }
}

std::string StringLikeType::Serialize()
{
    Json::Value jsonContent;
    Json::FastWriter jsonWriter;
    if (m_settingFlag & SETTING_STRING_LIKE_REFERER_FLAG)
    {
        Json::Value arrayReferer;
        std::vector < std::string > referer = m_Referer;
        for (std::vector < std::string >::iterator it = referer.begin();
                it != referer.end(); it++)
        {
            arrayReferer.append(*it);
        }
        jsonContent["Referer"] = arrayReferer;
    }
    return jsonWriter.write(jsonContent);
}

#ifdef BUILD_C_STYLE_INTERFACE
StringNotLikeType::StringNotLikeType(qs_string_not_like_t string_not_like)
{
    if (string_not_like.referer)
        SetReferer(string_not_like.referer);
}

qs_string_not_like_t *StringNotLikeType::toCStyleObj()
{
    qs_string_not_like_t *string_not_like =
        (qs_string_not_like_t *) malloc(sizeof(qs_string_not_like_t));
    qs_list_t *list_referer = (qs_list_t *) malloc(sizeof(qs_list_t));
    qs_list_init(list_referer);
    std::vector < std::string > referer = GetReferer();
    for (std::vector < std::string >::iterator it = referer.begin();
            it != referer.end(); it++)
    {
        qs_string_not_like_referer_item_t *item =
            (qs_string_not_like_referer_item_t *)
            malloc(sizeof(qs_string_not_like_referer_item_t));
        int refererLength = it->length();
        if (refererLength > 0)
        {
            item->content = (char *) malloc(refererLength + 1);
            memset(item->content, 0, refererLength + 1);
            strncpy(item->content, it->c_str(), refererLength);
        }
        else
        {
            item->content = NULL;
        }
        qs_list_append(&item->node, list_referer);
    }
    string_not_like->referer = list_referer;
    return string_not_like;
}

#endif							// BUILD_C_STYLE_INTERFACE

StringNotLikeType::StringNotLikeType(std::string serializedString)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(serializedString, jsonContent);
    if (jsonContent.isMember("Referer"))
    {
        std::vector < std::string > vecReferer;
        for (unsigned i = 0; i < jsonContent["Referer"].size(); ++i)
        {
            vecReferer.push_back(jsonContent["Referer"][i].asString());
        }
        SetReferer(vecReferer);
    }
}

std::string StringNotLikeType::Serialize()
{
    Json::Value jsonContent;
    Json::FastWriter jsonWriter;
    if (m_settingFlag & SETTING_STRING_NOT_LIKE_REFERER_FLAG)
    {
        Json::Value arrayReferer;
        std::vector < std::string > referer = m_Referer;
        for (std::vector < std::string >::iterator it = referer.begin();
                it != referer.end(); it++)
        {
            arrayReferer.append(*it);
        }
        jsonContent["Referer"] = arrayReferer;
    }
    return jsonWriter.write(jsonContent);
}

#ifdef BUILD_C_STYLE_INTERFACE
TransitionType::TransitionType(qs_transition_t transition)
{
    if (transition.days)
        SetDays(*transition.days);
    if (transition.storage_class)
        SetStorageClass(*transition.storage_class);
}

qs_transition_t *TransitionType::toCStyleObj()
{
    qs_transition_t *transition =
        (qs_transition_t *) malloc(sizeof(qs_transition_t));
    transition->days = (int *) malloc(sizeof(int));
    *transition->days = GetDays();
    transition->storage_class = (int *) malloc(sizeof(int));
    *transition->storage_class = GetStorageClass();
    return transition;
}

#endif							// BUILD_C_STYLE_INTERFACE

TransitionType::TransitionType(std::string serializedString)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(serializedString, jsonContent);
    if (jsonContent.isMember("days"))
    {
        SetDays(jsonContent["days"].asInt());
    }
    if (jsonContent.isMember("storage_class"))
    {
        SetStorageClass(jsonContent["storage_class"].asInt());
    }
}

std::string TransitionType::Serialize()
{
    Json::Value jsonContent;
    Json::FastWriter jsonWriter;
    if (m_settingFlag & SETTING_TRANSITION_DAYS_FLAG)
    {
        jsonContent["days"] = m_Days;
    }
    if (m_settingFlag & SETTING_TRANSITION_STORAGE_CLASS_FLAG)
    {
        jsonContent["storage_class"] = m_StorageClass;
    }
    return jsonWriter.write(jsonContent);
}

#ifdef BUILD_C_STYLE_INTERFACE
UploadsType::UploadsType(qs_uploads_t uploads)
{
    if (uploads.created)
        SetCreated(uploads.created);
    if (uploads.key)
        SetKey(uploads.key);
    if (uploads.upload_id)
        SetUploadID(uploads.upload_id);
}

qs_uploads_t *UploadsType::toCStyleObj()
{
    qs_uploads_t *uploads = (qs_uploads_t *) malloc(sizeof(qs_uploads_t));
    int createdLength = 0;
    createdLength = GetCreated().length();
    if (createdLength > 0)
    {
        uploads->created = (char *) malloc(createdLength + 1);
        memset(uploads->created, 0, createdLength + 1);
        strncpy(uploads->created, GetCreated().c_str(), createdLength);
    }
    else
    {
        uploads->created = NULL;
    }
    int keyLength = 0;
    keyLength = GetKey().length();
    if (keyLength > 0)
    {
        uploads->key = (char *) malloc(keyLength + 1);
        memset(uploads->key, 0, keyLength + 1);
        strncpy(uploads->key, GetKey().c_str(), keyLength);
    }
    else
    {
        uploads->key = NULL;
    }
    int uploadIDLength = 0;
    uploadIDLength = GetUploadID().length();
    if (uploadIDLength > 0)
    {
        uploads->upload_id = (char *) malloc(uploadIDLength + 1);
        memset(uploads->upload_id, 0, uploadIDLength + 1);
        strncpy(uploads->upload_id, GetUploadID().c_str(), uploadIDLength);
    }
    else
    {
        uploads->upload_id = NULL;
    }
    return uploads;
}

#endif							// BUILD_C_STYLE_INTERFACE

UploadsType::UploadsType(std::string serializedString)
{
    // parse json content
    Json::Reader jsonReader;
    Json::Value jsonContent;
    jsonReader.parse(serializedString, jsonContent);
    if (jsonContent.isMember("created"))
    {
        SetCreated(jsonContent["created"].asString());
    }
    if (jsonContent.isMember("key"))
    {
        SetKey(jsonContent["key"].asString());
    }
    if (jsonContent.isMember("upload_id"))
    {
        SetUploadID(jsonContent["upload_id"].asString());
    }
}

std::string UploadsType::Serialize()
{
    Json::Value jsonContent;
    Json::FastWriter jsonWriter;
    if (m_settingFlag & SETTING_UPLOADS_CREATED_FLAG)
    {
        jsonContent["created"] = m_Created;
    }
    if (m_settingFlag & SETTING_UPLOADS_KEY_FLAG)
    {
        jsonContent["key"] = m_Key;
    }
    if (m_settingFlag & SETTING_UPLOADS_UPLOAD_ID_FLAG)
    {
        jsonContent["upload_id"] = m_UploadID;
    }
    return jsonWriter.write(jsonContent);
}
