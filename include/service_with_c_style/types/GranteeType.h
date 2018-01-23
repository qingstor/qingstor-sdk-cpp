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

    //Grantee user ID
    char *id;
    //Grantee group name
    char *name;
    //Grantee type//type's available values: user, group
    char *type;				// Required

    int setting_flag;
} qs_grantee_t;

typedef struct
{

    qs_list_t node;

    qs_grantee_t *content;

} qs_grantee_item_t;

// grantee init function.
void init_grantee(qs_grantee_t * input);

// grantee release function.
void release_grantee(qs_grantee_t * output);

#ifdef  __cplusplus
};
#endif
