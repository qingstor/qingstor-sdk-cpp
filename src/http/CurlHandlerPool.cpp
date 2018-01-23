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

#include "plog/Log.h"
#include "http/CurlHandlerPool.h"

bool CurlHandlerPool::Init()
{
    if (0 != pthread_mutex_init(&m_lock, NULL))
    {
        LOGE << "Init curl handlers lock failed";
        return false;
    }
    m_handlers = new CURL*[m_maxHandlers]();
    for (int i = 0; i < m_maxHandlers; ++i, ++m_index)
    {
        m_handlers[i] = curl_easy_init();
        if (!m_handlers[i])
        {
            LOGE << "Init curl handlers pool failed";
            Destroy();
            return false;
        }
    }
    return true;
}

bool CurlHandlerPool::Destroy()
{
    for (int i = 0; i <= m_index; ++i)
    {
        curl_easy_cleanup(m_handlers[i]);
    }
    delete[] m_handlers;
    if (0 != pthread_mutex_destroy(&m_lock))
    {
        LOGE << "Destroy curl handlers lock failed";
        return false;
    }
    return true;
}

CURL* CurlHandlerPool::GetHandler()
{
    CURL* handle = NULL;
    pthread_mutex_lock(&m_lock);
    if (m_index >= 0)
    {
        LOGD << "Get handler from pool: " << m_index;
        handle = m_handlers[m_index--];
    }
    pthread_mutex_unlock(&m_lock);
    if (!handle)
    {
        LOGI << "Pool empty: create new handler";
        handle = curl_easy_init();
    }
    return handle;
}

void CurlHandlerPool::ReleaseHandler(CURL* handle)
{
    bool needCleanup = true;
    pthread_mutex_lock(&m_lock);
    if (m_index < m_maxHandlers - 1)
    {
        m_handlers[++m_index] = handle;
        needCleanup = false;
        LOGD << "Release handler to pool: %d", m_index;
    }
    pthread_mutex_unlock(&m_lock);
    if (needCleanup)
    {
        LOGI << "Pool full: destroy the handler";
        curl_easy_cleanup(handle);
    }
}