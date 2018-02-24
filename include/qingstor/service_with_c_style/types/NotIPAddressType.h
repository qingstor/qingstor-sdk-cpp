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

    //Source IP

    qs_list_t *source_ip;

    int setting_flag;
} qs_not_ip_address_t;

typedef struct
{

    qs_list_t node;

    qs_not_ip_address_t *content;

} qs_not_ip_address_item_t;

typedef struct
{
    qs_list_t node;

    char *content;

} qs_not_ip_address_source_ip_item_t;

// not_ip_address init function.
void init_not_ip_address(qs_not_ip_address_t * input);

// not_ip_address release function.
void release_not_ip_address(qs_not_ip_address_t * output);

#ifdef  __cplusplus
};
#endif
