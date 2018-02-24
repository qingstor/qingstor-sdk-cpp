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

#include "../QsList.h"
// Headers of CustomizedType.
#ifdef  __cplusplus
extern "C" {
#endif

typedef struct
{

    //Allowed headers

    qs_list_t *allowed_headers;
    //Allowed methods

    qs_list_t *allowed_methods;	// Required
    //Allowed origin
    char *allowed_origin;	// Required
    //Expose headers

    qs_list_t *expose_headers;
    //Max age seconds
    int *max_age_seconds;

    int setting_flag;
} qs_cors_rule_t;

typedef struct
{

    qs_list_t node;

    qs_cors_rule_t *content;

} qs_cors_rule_item_t;

typedef struct
{
    qs_list_t node;

    char *content;

} qs_cors_rule_allowed_headers_item_t;
typedef struct
{
    qs_list_t node;

    char *content;

} qs_cors_rule_allowed_methods_item_t;

typedef struct
{
    qs_list_t node;

    char *content;

} qs_cors_rule_expose_headers_item_t;

// cors_rule init function.
void init_cors_rule(qs_cors_rule_t * input);

// cors_rule release function.
void release_cors_rule(qs_cors_rule_t * output);

#ifdef  __cplusplus
};
#endif
