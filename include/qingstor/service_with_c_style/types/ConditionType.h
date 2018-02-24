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
#include "IPAddressType.h"
#include "IsNullType.h"
#include "NotIPAddressType.h"
#include "StringLikeType.h"
#include "StringNotLikeType.h"
#ifdef  __cplusplus
extern "C" {
#endif

typedef struct
{

    qs_ip_address_t *ip_address;

    qs_is_null_t *is_null;

    qs_not_ip_address_t *not_ip_address;

    qs_string_like_t *string_like;

    qs_string_not_like_t *string_not_like;

    int setting_flag;
} qs_condition_t;

typedef struct
{

    qs_list_t node;

    qs_condition_t *content;

} qs_condition_item_t;

// condition init function.
void init_condition(qs_condition_t * input);

// condition release function.
void release_condition(qs_condition_t * output);

#ifdef  __cplusplus
};
#endif
