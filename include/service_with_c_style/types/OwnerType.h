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

    //User ID
    char *id;
    //Username
    char *name;

    int setting_flag;
} qs_owner_t;

typedef struct
{

    qs_list_t node;

    qs_owner_t *content;

} qs_owner_item_t;

// owner init function.
void init_owner(qs_owner_t * input);

// owner release function.
void release_owner(qs_owner_t * output);

#ifdef  __cplusplus
};
#endif
