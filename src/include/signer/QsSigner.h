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

#include "http/HttpRequest.h"
#include "QsErrors.h"
#include <string>

namespace QingStor
{

class QS_SDK_API QsSigner
{
public:
    QsSigner(std::string strAccessKeyID, std::string strSecretAccessKey) : m_AccessKeyID(strAccessKeyID), m_strSecretAccessKey(strSecretAccessKey) {};
    virtual ~QsSigner() {};
    std::string GetTimestamp() const;
    QsError SignRequest(Http::HttpRequest* request) const;
    std::string BuildStringToSign(Http::HttpRequest* request) const;

private:
    std::string BuildCanonicalizedHeaders(Http::HeaderValueCollection headers) const;
    std::string BuildCanonicalizedResource(Http::QueryParamCollection queryMap, std::string urlEncodedPath)  const;

private:
    std::string m_AccessKeyID;
    std::string m_strSecretAccessKey;
};

} // namespace QingStor