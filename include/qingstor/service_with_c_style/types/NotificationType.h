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
#include "CloudfuncArgsType.h"
#ifdef  __cplusplus
extern "C" {
#endif

typedef struct
{

    //Event processing service//cloudfunc's available values: tupu-porn, notifier, image
    char *cloudfunc;		// Required

    qs_cloudfunc_args_t *cloudfunc_args;
    //event types

    qs_list_t *event_types;	// Required
    //notification id
    char *id;				// Required
    //notify url
    char *notify_url;
    //Object name matching rule

    qs_list_t *object_filters;

    int setting_flag;
} qs_notification_t;

typedef struct
{

    qs_list_t node;

    qs_notification_t *content;

} qs_notification_item_t;

typedef struct
{
    qs_list_t node;

    char *content;

} qs_notification_event_types_item_t;

typedef struct
{
    qs_list_t node;

    char *content;

} qs_notification_object_filters_item_t;

// notification init function.
QS_SDK_API void init_notification(qs_notification_t * input);

// notification release function.
QS_SDK_API void release_notification(qs_notification_t * output);

#ifdef  __cplusplus
};
#endif
