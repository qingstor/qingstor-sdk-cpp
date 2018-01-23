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

#include <yaml/yaml.h>
#include <plog/Log.h>
#include "QsConfig.h"
#include "StringUtils.h"
#include <map>

namespace QingStor
{

static const char *CONFIG_KEY_ACCESS_KEY_ID = "access_key_id";

static const char *CONFIG_KEY_SECRET_ACCESS_KEY = "secret_access_key";

static const char *CONFIG_KEY_HOST = "host";

static const char *CONFIG_KEY_PORT = "port";

static const char *CONFIG_KEY_PROTOCOL = "protocol";

static const char *CONFIG_KEY_CONNECTION_RETRIES = "connection_retries";

static const char *CONFIG_KEY_ADDITIONAL_USER_AGENT = "additional_user_agent";

static const char *CONFIG_KEY_TIMEOUT_PERIOD = "timeOutPeriod";

// Default value

static const char *DEFAULT_HOST = "qingstor.com";

static const char *DEFAULT_PROTOCOL = "https";

static const char *DEFAULT_ADDITIONAL_USER_AGENT = "";

static int DEFAULT_RETRIES = 3;

static int DEFAULT_PORT = 443;

static int DEFAULT_TIMEOUT_PERIOD = 3;

QsConfig::QsConfig(const std::string & access_key_id, const std::string & secret_access_key)
    : additionalUserAgent(DEFAULT_ADDITIONAL_USER_AGENT),
      accessKeyId(access_key_id),secretAccessKey(secret_access_key),
      host(DEFAULT_HOST),protocol(DEFAULT_PROTOCOL),
      port(DEFAULT_PORT),connectionRetries(DEFAULT_RETRIES),
      timeOutPeriod(DEFAULT_TIMEOUT_PERIOD)
{
}

QsError QsConfig::LoadConfigFile(const std::string &config_file)
{
    FILE *fh = NULL;
    yaml_parser_t parser;
    yaml_token_t token;
    std::map<std::string, std::string> kvs;
    std::string token_key;
    std::string token_value;
    bool reach_key = false;
    bool reach_value = false;
    /* Initialize parser */
    if (!yaml_parser_initialize(&parser))
    {
        LOG_FATAL << "couldn't initialize yaml parser";
        return QS_ERR_INVAILD_CONFIG_FILE;
    }
    /* Open configuration file */
    if ((fh = fopen(config_file.c_str(), "rb")) == NULL)
    {
        yaml_parser_delete(&parser);
        LOG_FATAL << "couldn't open configure file " << config_file.c_str();
        return QS_ERR_INVAILD_CONFIG_FILE;
    }
    /* Set input file */
    yaml_parser_set_input_file(&parser, fh);
    do
    {
        yaml_parser_scan(&parser, &token);
        switch (token.type)
        {
        case YAML_STREAM_START_TOKEN:
        case YAML_STREAM_END_TOKEN:
        case YAML_BLOCK_SEQUENCE_START_TOKEN:
        case YAML_BLOCK_ENTRY_TOKEN:
        case YAML_BLOCK_END_TOKEN:
        case YAML_BLOCK_MAPPING_START_TOKEN:
            break;
        case YAML_KEY_TOKEN:
        {
            reach_key = true;
        }
        break;
        case YAML_VALUE_TOKEN:
        {
            reach_value = true;
        }
        break;
        case YAML_SCALAR_TOKEN:
        {
            bool config_invalid = false;
            if (reach_key)
            {
                token_key = std::string((const char *)(token.data.scalar.value));
                reach_key = false;
                break;
            }
            else if (reach_value)
            {
                token_value = std::string((const char *)(token.data.scalar.value));
                reach_value = false;
                if (token_key.empty() || token_value.empty())
                {
                    config_invalid = true;
                }
            }
            else
            {
                config_invalid = true;
            }
            if (config_invalid)
            {
                yaml_token_delete(&token);
                yaml_parser_delete(&parser);
                fclose(fh);
                LOG_FATAL << "YAML configuration is invalid";
                return QS_ERR_INVAILD_CONFIG_FILE;
            }
            else
            {
                kvs.insert(std::pair<std::string, std::string>(token_key, token_value));
                token_key.clear();
                token_value.clear();
            }
        }
        break;
        default:
        {
            yaml_token_delete(&token);
            yaml_parser_delete(&parser);
            fclose(fh);
            LOG_FATAL << "YAML configuration is invalid with token type" << token.type;
            return QS_ERR_INVAILD_CONFIG_FILE;
        }
        break;
        }
        if (token.type != YAML_STREAM_END_TOKEN)
        {
            yaml_token_delete(&token);
        }
    }
    while (token.type != YAML_STREAM_END_TOKEN);
    yaml_token_delete(&token);
    yaml_parser_delete(&parser);
    fclose(fh);
    /* Go through the interested configurations */
    if (kvs[std::string(CONFIG_KEY_ACCESS_KEY_ID)].empty())
    {
        LOG_FATAL << "YAML configuration is invalid with token type" << token.type;
        return QS_ERR_INVAILD_CONFIG_FILE;
    }
    else
    {
        accessKeyId = kvs[std::string(CONFIG_KEY_ACCESS_KEY_ID)];
    }
    if (kvs[std::string(CONFIG_KEY_SECRET_ACCESS_KEY)].empty())
    {
        return QS_ERR_INVAILD_CONFIG_FILE;
    }
    else
    {
        secretAccessKey = kvs[std::string(CONFIG_KEY_SECRET_ACCESS_KEY)];
    }
    if (kvs[std::string(CONFIG_KEY_HOST)].empty())
    {
        host = DEFAULT_HOST;
    }
    else
    {
        host = kvs[std::string(CONFIG_KEY_HOST)];
    }
    if (kvs[std::string(CONFIG_KEY_PORT)].empty())
    {
        port = DEFAULT_PORT;
    }
    else
    {
        std::string port_str = kvs[std::string(CONFIG_KEY_PORT)];
        int tmp_prot = atoi(port_str.c_str());
        if (tmp_prot <= 0 || tmp_prot > 65535)
        {
            LOG_WARNING << "Configuration Port" << port_str.c_str() << "is invalid, using default vaule:" << DEFAULT_PORT;
            tmp_prot = DEFAULT_PORT;
        }
        port = tmp_prot;
    }
    if (kvs[std::string(CONFIG_KEY_PROTOCOL)].empty())
    {
        protocol = DEFAULT_PROTOCOL;
    }
    else
    {
        protocol = kvs[std::string(CONFIG_KEY_PROTOCOL)];
    }
    if (kvs[std::string(CONFIG_KEY_CONNECTION_RETRIES)].empty())
    {
        connectionRetries = 3;
    }
    else
    {
        std::string retries_str = kvs[std::string(CONFIG_KEY_CONNECTION_RETRIES)];
        int retries = atoi(retries_str.c_str());
        if (retries <= 0 || retries > 16)
        {
            LOG_WARNING << "Configuration connection retries" << retries_str.c_str() << " is invalid, using default value:" << DEFAULT_RETRIES;
            retries = DEFAULT_RETRIES;
        }
        connectionRetries = retries;
    }
    if (kvs[std::string(CONFIG_KEY_TIMEOUT_PERIOD)].empty())
    {
        timeOutPeriod = 3;
    }
    else
    {
        std::string timeOutPeriod_str = kvs[std::string(CONFIG_KEY_TIMEOUT_PERIOD)];
        int timeOut = atoi(timeOutPeriod_str.c_str());
        if (connectionRetries <= 0)
        {
            LOG_WARNING << "Configuration connection retries" << timeOutPeriod_str.c_str() << " is invalid, using default value:" << DEFAULT_RETRIES;
            timeOutPeriod = DEFAULT_TIMEOUT_PERIOD;
        }
        timeOutPeriod = timeOut;
    }
    if (kvs[std::string(CONFIG_KEY_ADDITIONAL_USER_AGENT)].empty())
    {
        additionalUserAgent = "";
    }
    else
    {
        additionalUserAgent = kvs[std::string(CONFIG_KEY_ADDITIONAL_USER_AGENT)];
    }
    return QS_ERR_NO_ERROR;
}
}
