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
#include "ConditionType.h"
#ifdef  __cplusplus
extern "C" {
#endif

typedef struct
{

    //QingStor API methods

    qs_list_t *action;		// Required

    qs_condition_t *condition;
    //Statement effect//effect's available values: allow, deny
    char *effect;			// Required
    //Bucket policy id, must be unique
    char *id;				// Required
    //The resources to apply bucket policy

    qs_list_t *resource;
    //The user to apply bucket policy

    qs_list_t *user;		// Required

    int setting_flag;
} qs_statement_t;

typedef struct
{

    qs_list_t node;

    qs_statement_t *content;

} qs_statement_item_t;

typedef struct
{
    qs_list_t node;

    char *content;

} qs_statement_action_item_t;

typedef struct
{
    qs_list_t node;

    char *content;

} qs_statement_resource_item_t;
typedef struct
{
    qs_list_t node;

    char *content;

} qs_statement_user_item_t;

// statement init function.
void init_statement(qs_statement_t * input);

// statement release function.
void release_statement(qs_statement_t * output);

#ifdef  __cplusplus
};
#endif
