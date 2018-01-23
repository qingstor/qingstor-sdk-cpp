// +-------------------------------------------------------------------------
// | Copyright (C) 2017 Yunify, Inc.
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

typedef enum QsError
{
    QS_ERR_NO_ERROR = 0,		// Every is fline, send request sucussfully and get excepted response from QingStor.
    QS_ERR_INVAILD_CONFIG_FILE,	// There something wrong with your config file.
    QS_ERR_NO_REQUIRED_PARAMETER,	// The input object lacks some of the parameters that must be filled in .
    QS_ERR_SEND_REQUEST_ERROR,	// No response has been received.
    QS_ERR_UNEXCEPTED_RESPONSE,	// Response has been received, but it is not in line with expectations.
} QsError;
