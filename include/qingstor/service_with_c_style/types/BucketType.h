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

    //Created time of the bucket
    char *created;
    //QingCloud Zone ID
    char *location;
    //Bucket name
    char *name;
    //URL to access the bucket
    char *url;

    int setting_flag;
} qs_bucket_t;

typedef struct
{

    qs_list_t node;

    qs_bucket_t *content;

} qs_bucket_item_t;

// bucket init function.
void init_bucket(qs_bucket_t * input);

// bucket release function.
void release_bucket(qs_bucket_t * output);

#ifdef  __cplusplus
};
#endif
