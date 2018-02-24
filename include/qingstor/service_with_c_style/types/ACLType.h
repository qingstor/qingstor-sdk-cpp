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
#include "GranteeType.h"
#ifdef  __cplusplus
extern "C" {
#endif

typedef struct
{

    qs_grantee_t *grantee;	// Required
    //Permission for this grantee//permission's available values: READ, WRITE, FULL_CONTROL
    char *permission;		// Required

    int setting_flag;
} qs_acl_t;

typedef struct
{

    qs_list_t node;

    qs_acl_t *content;

} qs_acl_item_t;

// acl init function.
void init_acl(qs_acl_t * input);

// acl release function.
void release_acl(qs_acl_t * output);

#ifdef  __cplusplus
};
#endif
