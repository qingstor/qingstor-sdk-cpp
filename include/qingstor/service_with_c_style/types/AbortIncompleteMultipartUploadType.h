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

    //days after initiation
    int *days_after_initiation;	// Required

    int setting_flag;
} qs_abort_incomplete_multipart_upload_t;

typedef struct
{

    qs_list_t node;

    qs_abort_incomplete_multipart_upload_t *content;

} qs_abort_incomplete_multipart_upload_item_t;

// abort_incomplete_multipart_upload init function.
QS_SDK_API void
init_abort_incomplete_multipart_upload
(qs_abort_incomplete_multipart_upload_t * input);

// abort_incomplete_multipart_upload release function.
QS_SDK_API void
release_abort_incomplete_multipart_upload
(qs_abort_incomplete_multipart_upload_t * output);

#ifdef  __cplusplus
};
#endif
