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
#include "service_with_c_style/Types.h"

// acl init function.
void init_acl(qs_acl_t * content)
{
    content->grantee = NULL;
    content->permission = NULL;
}

// acl release function.
void release_acl(qs_acl_t * content)
{
    if (content->grantee)
    {
        release_grantee(content->grantee);
        free(content->grantee);
    }
    if (content->permission)
    {
        free(content->permission);
    }
}

// bucket init function.
void init_bucket(qs_bucket_t * content)
{
    content->created = NULL;
    content->location = NULL;
    content->name = NULL;
    content->url = NULL;
}

// bucket release function.
void release_bucket(qs_bucket_t * content)
{
    if (content->created)
    {
        free(content->created);
    }
    if (content->location)
    {
        free(content->location);
    }
    if (content->name)
    {
        free(content->name);
    }
    if (content->url)
    {
        free(content->url);
    }
}

// condition init function.
void init_condition(qs_condition_t * content)
{
    content->ip_address = NULL;
    content->is_null = NULL;
    content->not_ip_address = NULL;
    content->string_like = NULL;
    content->string_not_like = NULL;
}

// condition release function.
void release_condition(qs_condition_t * content)
{
    if (content->ip_address)
    {
        release_ip_address(content->ip_address);
        free(content->ip_address);
    }
    if (content->is_null)
    {
        release_is_null(content->is_null);
        free(content->is_null);
    }
    if (content->not_ip_address)
    {
        release_not_ip_address(content->not_ip_address);
        free(content->not_ip_address);
    }
    if (content->string_like)
    {
        release_string_like(content->string_like);
        free(content->string_like);
    }
    if (content->string_not_like)
    {
        release_string_not_like(content->string_not_like);
        free(content->string_not_like);
    }
}

// cors_rule init function.
void init_cors_rule(qs_cors_rule_t * content)
{
    content->allowed_headers = NULL;
    content->allowed_methods = NULL;
    content->allowed_origin = NULL;
    content->expose_headers = NULL;
    content->max_age_seconds = NULL;
}

// cors_rule release function.
void release_cors_rule(qs_cors_rule_t * content)
{
    if (content->allowed_headers)
    {
        qs_string_item_t *item = NULL;
        qs_string_item_t *item_to_delete = NULL;
        qs_list_for_each_entry(qs_string_item_t, item, content->allowed_headers)
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
        free(content->allowed_headers);
    }
    if (content->allowed_methods)
    {
        qs_string_item_t *item = NULL;
        qs_string_item_t *item_to_delete = NULL;
        qs_list_for_each_entry(qs_string_item_t, item, content->allowed_methods)
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
        free(content->allowed_methods);
    }
    if (content->allowed_origin)
    {
        free(content->allowed_origin);
    }
    if (content->expose_headers)
    {
        qs_string_item_t *item = NULL;
        qs_string_item_t *item_to_delete = NULL;
        qs_list_for_each_entry(qs_string_item_t, item, content->expose_headers)
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
        free(content->expose_headers);
    }
    if (content->max_age_seconds)
    {
        free(content->max_age_seconds);
    }
}

// grantee init function.
void init_grantee(qs_grantee_t * content)
{
    content->id = NULL;
    content->name = NULL;
    content->type = NULL;
}

// grantee release function.
void release_grantee(qs_grantee_t * content)
{
    if (content->id)
    {
        free(content->id);
    }
    if (content->name)
    {
        free(content->name);
    }
    if (content->type)
    {
        free(content->type);
    }
}

// ip_address init function.
void init_ip_address(qs_ip_address_t * content)
{
    content->source_ip = NULL;
}

// ip_address release function.
void release_ip_address(qs_ip_address_t * content)
{
    if (content->source_ip)
    {
        qs_string_item_t *item = NULL;
        qs_string_item_t *item_to_delete = NULL;
        qs_list_for_each_entry(qs_string_item_t, item, content->source_ip)
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
        free(content->source_ip);
    }
}

// is_null init function.
void init_is_null(qs_is_null_t * content)
{
    content->referer = NULL;
}

// is_null release function.
void release_is_null(qs_is_null_t * content)
{
    if (content->referer)
    {
        free(content->referer);
    }
}

// key init function.
void init_key(qs_key_t * content)
{
    content->created = NULL;
    content->encrypted = NULL;
    content->etag = NULL;
    content->key = NULL;
    content->mime_type = NULL;
    content->modified = NULL;
    content->size = NULL;
}

// key release function.
void release_key(qs_key_t * content)
{
    if (content->created)
    {
        free(content->created);
    }
    if (content->encrypted)
    {
        free(content->encrypted);
    }
    if (content->etag)
    {
        free(content->etag);
    }
    if (content->key)
    {
        free(content->key);
    }
    if (content->mime_type)
    {
        free(content->mime_type);
    }
    if (content->modified)
    {
        free(content->modified);
    }
    if (content->size)
    {
        free(content->size);
    }
}

// key_delete_error init function.
void init_key_delete_error(qs_key_delete_error_t * content)
{
    content->code = NULL;
    content->key = NULL;
    content->message = NULL;
}

// key_delete_error release function.
void release_key_delete_error(qs_key_delete_error_t * content)
{
    if (content->code)
    {
        free(content->code);
    }
    if (content->key)
    {
        free(content->key);
    }
    if (content->message)
    {
        free(content->message);
    }
}

// not_ip_address init function.
void init_not_ip_address(qs_not_ip_address_t * content)
{
    content->source_ip = NULL;
}

// not_ip_address release function.
void release_not_ip_address(qs_not_ip_address_t * content)
{
    if (content->source_ip)
    {
        qs_string_item_t *item = NULL;
        qs_string_item_t *item_to_delete = NULL;
        qs_list_for_each_entry(qs_string_item_t, item, content->source_ip)
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
        free(content->source_ip);
    }
}

// object_part init function.
void init_object_part(qs_object_part_t * content)
{
    content->created = NULL;
    content->etag = NULL;
    content->part_number = NULL;
    content->size = NULL;
}

// object_part release function.
void release_object_part(qs_object_part_t * content)
{
    if (content->created)
    {
        free(content->created);
    }
    if (content->etag)
    {
        free(content->etag);
    }
    if (content->part_number)
    {
        free(content->part_number);
    }
    if (content->size)
    {
        free(content->size);
    }
}

// owner init function.
void init_owner(qs_owner_t * content)
{
    content->id = NULL;
    content->name = NULL;
}

// owner release function.
void release_owner(qs_owner_t * content)
{
    if (content->id)
    {
        free(content->id);
    }
    if (content->name)
    {
        free(content->name);
    }
}

// statement init function.
void init_statement(qs_statement_t * content)
{
    content->action = NULL;
    content->condition = NULL;
    content->effect = NULL;
    content->id = NULL;
    content->resource = NULL;
    content->user = NULL;
}

// statement release function.
void release_statement(qs_statement_t * content)
{
    if (content->action)
    {
        qs_string_item_t *item = NULL;
        qs_string_item_t *item_to_delete = NULL;
        qs_list_for_each_entry(qs_string_item_t, item, content->action)
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
        free(content->action);
    }
    if (content->condition)
    {
        release_condition(content->condition);
        free(content->condition);
    }
    if (content->effect)
    {
        free(content->effect);
    }
    if (content->id)
    {
        free(content->id);
    }
    if (content->resource)
    {
        qs_string_item_t *item = NULL;
        qs_string_item_t *item_to_delete = NULL;
        qs_list_for_each_entry(qs_string_item_t, item, content->resource)
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
        free(content->resource);
    }
    if (content->user)
    {
        qs_string_item_t *item = NULL;
        qs_string_item_t *item_to_delete = NULL;
        qs_list_for_each_entry(qs_string_item_t, item, content->user)
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
        free(content->user);
    }
}

// string_like init function.
void init_string_like(qs_string_like_t * content)
{
    content->referer = NULL;
}

// string_like release function.
void release_string_like(qs_string_like_t * content)
{
    if (content->referer)
    {
        qs_string_item_t *item = NULL;
        qs_string_item_t *item_to_delete = NULL;
        qs_list_for_each_entry(qs_string_item_t, item, content->referer)
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
        free(content->referer);
    }
}

// string_not_like init function.
void init_string_not_like(qs_string_not_like_t * content)
{
    content->referer = NULL;
}

// string_not_like release function.
void release_string_not_like(qs_string_not_like_t * content)
{
    if (content->referer)
    {
        qs_string_item_t *item = NULL;
        qs_string_item_t *item_to_delete = NULL;
        qs_list_for_each_entry(qs_string_item_t, item, content->referer)
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
        free(content->referer);
    }
}

// uploads init function.
void init_uploads(qs_uploads_t * content)
{
    content->created = NULL;
    content->key = NULL;
    content->upload_id = NULL;
}

// uploads release function.
void release_uploads(qs_uploads_t * content)
{
    if (content->created)
    {
        free(content->created);
    }
    if (content->key)
    {
        free(content->key);
    }
    if (content->upload_id)
    {
        free(content->upload_id);
    }
}
