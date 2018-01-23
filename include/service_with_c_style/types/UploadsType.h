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
#include "KeyType.h"
#ifdef  __cplusplus
extern "C" {
#endif

typedef struct
{

    //Object part created time
    char *created;
    //Object key
    char *key;
    //Object upload id
    char *upload_id;

    int setting_flag;
} qs_uploads_t;

typedef struct
{

    qs_list_t node;

    qs_uploads_t *content;

} qs_uploads_item_t;

// uploads init function.
void init_uploads(qs_uploads_t * input);

// uploads release function.
void release_uploads(qs_uploads_t * output);

#ifdef  __cplusplus
};
#endif
