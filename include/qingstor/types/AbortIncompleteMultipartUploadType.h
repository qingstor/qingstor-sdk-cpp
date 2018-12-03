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

#include "../QsBaseType.h"
#include <string>

// Headers of CustomizedType.

#ifdef BUILD_C_STYLE_INTERFACE
#include "../service_with_c_style/types/AbortIncompleteMultipartUploadType.h"
#endif							// BUILD_C_STYLE_INTERFACE

// days after initiation'flag
#define SETTING_ABORT_INCOMPLETE_MULTIPART_UPLOAD_DAYS_AFTER_INITIATION_FLAG 0x1

//AbortIncompleteMultipartUploadType presents costom type：AbortIncompleteMultipartUpload.
class QS_SDK_API AbortIncompleteMultipartUploadType:QsBaseType
{

public:
    AbortIncompleteMultipartUploadType()
    {
    };
    AbortIncompleteMultipartUploadType(std::string serializedStr);

#ifdef BUILD_C_STYLE_INTERFACE
    AbortIncompleteMultipartUploadType(qs_abort_incomplete_multipart_upload_t
                                       abort_incomplete_multipart_upload);
    qs_abort_incomplete_multipart_upload_t *toCStyleObj();
#endif							// BUILD_C_STYLE_INTERFACE// days after initiation

    inline void SetDaysAfterInitiation(int DaysAfterInitiation)
    {
        m_settingFlag |=
            SETTING_ABORT_INCOMPLETE_MULTIPART_UPLOAD_DAYS_AFTER_INITIATION_FLAG;
        m_DaysAfterInitiation = DaysAfterInitiation;
    };

    inline int GetDaysAfterInitiation()
    {
        return m_DaysAfterInitiation;
    };

    std::string Serialize();

private:

    // days after initiation
    int m_DaysAfterInitiation;	// Required

    int setting_flag;
};
