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

#include <curl/curl.h>
#include <pthread.h>

class CurlHandlerPool
{
public:
    explicit CurlHandlerPool(int maxHandlers)
        : m_maxHandlers(maxHandlers)
        , m_handlers(NULL)
        , m_index(-1)
    {
    }

    bool Init();
    bool Destroy();

    CURL* GetHandler();
    void ReleaseHandler(CURL* handle);

private:
    int m_maxHandlers;

    pthread_mutex_t m_lock;
    CURL** m_handlers;
    int m_index;
};
