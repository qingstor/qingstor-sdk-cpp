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

#include "CurlHandlerPool.h"
#include "QsSdkOption.h"
#include "QsConfig.h"
#include <curl/curl.h>
#include <string>
#include <memory>

namespace QingStor
{
namespace Http
{
static CurlHandlerPool* gCurlPool           = NULL;
static int              gCurlPoolSize       = 32;

class HttpRequest;
class HttpResponse;

/**
* HttpClient. All it does is make HttpRequests and return their response.
*/
class QS_SDK_API HttpClient
{
public:
    HttpClient(int timeOutPeriod = 3):m_timeOutPeriod(timeOutPeriod) {};
    virtual ~HttpClient() {};

    // Send an http request, returns the newly allocated HttpResponse
    HttpResponse * SendRequest(HttpRequest *request) const;

    static void CreateGlobaleCurlPool();

    static void DestroyGlobaleCurlPool();

private:
    //bool m_allowRedirects;
    int m_timeOutPeriod;		// The timeout length of a single attempt, wthich in the unit of second.

    //Callback to read the content from the content body of the request
    static size_t ReadBody(char *ptr, size_t size, size_t nmemb, void *userdata);
    //callback to write the content to the response.
    static size_t WriteData(char *ptr, size_t size, size_t nmemb, void *userdata);
    //callback to write the headers to the response
    static size_t WriteHeader(char *ptr, size_t size, size_t nmemb, void *userdata);
};

} // namespace Http
} // namespace QingStor
