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

#include "QsErrors.h"
#include <string>

namespace QingStor
{

class QsConfig
{
public:
    QsConfig(const std::string & access_key_id =
                 "", const std::string & secret_access_key = "");

    QsError LoadConfigFile(const std::string & config_file);

public:
    std::string additionalUserAgent;
    std::string accessKeyId;
    std::string secretAccessKey;
    std::string host;
    std::string protocol;
    int port;
    int connectionRetries;
    int timeOutPeriod;		// The timeout length of a single attempt, wthich in the unit of second.
};
}
