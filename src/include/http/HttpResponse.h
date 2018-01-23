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

#include "QsSdkOption.h"
#include "http/HttpRequest.h"
#include "utils/QsStream.h"

namespace QingStor
{
namespace Utils
{
namespace Stream
{
class ResponseStream;
}
}
namespace Http
{
/**
 * Abstract class for representing an Http Response.
 */
class QS_SDK_API HttpResponse
{
public:
    /**
     * Initializes an http response with the originalRequest and the response code.
     */
    HttpResponse() : responseCode(REQUEST_NOT_MADE)
    {
        bodyStream = new QsStream();
    }

    virtual ~HttpResponse() {}; // = default;

    /**
     * Get the headers from this response
     */
    HeaderValueCollection GetHeaders();
    /**
     * Returns true if the response contains a header by headerName
     */
    bool HasHeader(const char *headerName) const;
    /**
     * Returns the value for a header at headerName if it exists.
     */
    std::string GetHeader(const std::string &) const;
    /**
     * Gets response code for this http response.
     */
    inline HttpResponseCode GetResponseCode() const
    {
        return responseCode;
    }
    /**
     * Sets the response code for this http response.
     */
    inline void SetResponseCode(HttpResponseCode httpResponseCode)
    {
        responseCode = httpResponseCode;
    }

    /**
     * Gets the response body of the response.
     */
    std::iostream *GetResponseBody()
    {
        return bodyStream; // bodyStream.GetUnderlyingStream();
    }

    /**
     * Release the response body.
     */
    void ReleaseResponseBody()
    {
        if(bodyStream)
        {
            delete bodyStream;
            bodyStream = NULL;
        }
    }

    /**
     * Adds a header to the http response object.
     */
    void AddHeader(const std::string &, const std::string &);
    /**
     * Sets the content type header on the http response object.
     */
    void SetContentType(const std::string &contentType)
    {
        AddHeader("content-type", contentType);
    };

private:
    QsStream *bodyStream;
    HttpResponseCode responseCode;
    HeaderValueCollection headerMap;

};

} // namespace Http
} // namespace QingStor
