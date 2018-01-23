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

#include  "../QsSdkOption.h"
#include  "../QsErrors.h"
#include  "types/ACLType.h"
#include  "types/BucketType.h"
#include  "types/ConditionType.h"
#include  "types/CORSRuleType.h"
#include  "types/GranteeType.h"
#include  "types/IPAddressType.h"
#include  "types/IsNullType.h"
#include  "types/KeyType.h"
#include  "types/KeyDeleteErrorType.h"
#include  "types/NotIPAddressType.h"
#include  "types/ObjectPartType.h"
#include  "types/OwnerType.h"
#include  "types/StatementType.h"
#include  "types/StringLikeType.h"
#include  "types/StringNotLikeType.h"
#include  "types/UploadsType.h"

typedef struct
{
    char *code;
    char *message;
    char *request_id;
    char *url;
} qs_error_info_t;

typedef struct
{
    int response_code;
    qs_error_info_t error_info;

} qs_default_output_s;

typedef struct
{
    int response_code;
} qs_default_input_s;
