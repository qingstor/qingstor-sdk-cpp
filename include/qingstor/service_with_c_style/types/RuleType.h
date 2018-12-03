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
#include "AbortIncompleteMultipartUploadType.h"
#include "ExpirationType.h"
#include "FilterType.h"
#include "TransitionType.h"
#ifdef  __cplusplus
extern "C" {
#endif

typedef struct
{

    qs_abort_incomplete_multipart_upload_t
    *abort_incomplete_multipart_upload;

    qs_expiration_t *expiration;

    qs_filter_t *filter;	// Required
    //rule id
    char *id;				// Required
    //rule status//status's available values: enabled, disabled
    char *status;			// Required

    qs_transition_t *transition;

    int setting_flag;
} qs_rule_t;

typedef struct
{

    qs_list_t node;

    qs_rule_t *content;

} qs_rule_item_t;

// rule init function.
QS_SDK_API void init_rule(qs_rule_t * input);

// rule release function.
QS_SDK_API void release_rule(qs_rule_t * output);

#ifdef  __cplusplus
};
#endif
