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

    //Object created time
    char *created;
    //Whether this key is encrypted
    int *encrypted;
    //MD5sum of the object
    char *etag;
    //Object key
    char *key;
    //MIME type of the object
    char *mime_type;
    //Last modified time in unix time format
    int *modified;
    //Object content size
    long *size;

    int setting_flag;
} qs_key_t;

typedef struct
{

    qs_list_t node;

    qs_key_t *content;

} qs_key_item_t;

// key init function.
void init_key(qs_key_t * input);

// key release function.
void release_key(qs_key_t * output);

#ifdef  __cplusplus
};
#endif
