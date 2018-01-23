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

#include "http/HttpURI.h"
#include "HttpCommon.h"
#include <memory>
#include <sstream>

namespace QingStor
{
namespace Http
{
extern const char *CONTENT_LENGTH_HEADER;
extern const char *CONTENT_TYPE_HEADER;
extern const char *CONTENT_MD5_HEADER;
extern const char *DATE_HEADER;
extern const char *AUTHORIZATION_HEADER;

/**
* Abstract class for representing an HttpRequest.
*/
class QS_SDK_API HttpRequest
{
public:
    /**
    * Initializes an HttpRequest object with uri and http method.
    */
    HttpRequest(HttpMethod method, URI uri);

    virtual ~HttpRequest()
    {
    }

    /**
    * Get the value of a Header based on its name.
    */
    const std::string GetHeaderValue(const char *headerName) const;

    /**
    * Add a header pair
    */
    void SetHeaderValue(const char *headerName, const std::string &headerValue);

    void SetHeaderValue(const std::string &headerName, const std::string &headerValue);

    /**
    * Deletes a header from the request by name.
    */
    void DeleteHeader(const char *headerName);

    /**
    * Add a query parameter pair
    */
    void SetQueryStringParameter(const char* name, const std::string& value);

    void SetQueryStringParameter(const std::string &name, const std::string& value);

    /**
    * Adds a content body stream to the request. This stream will be used to send the body to the endpoint.
    */
    void AddContentBody(std::iostream *strContent)
    {
        bodyStream = strContent;
    };

    /**
    * Returns true if a header exists in the request with name
    */
    bool HasHeader(const char *name) const;

    /**
    * Gets underlying URI object with mutation access.
    */
    inline URI &GetUri()
    {
        return m_uri;
    }

    /**
    * Gets the underlying URI object.
    */
    const URI &GetUri() const
    {
        return m_uri;
    }

    /**
    * Gets the collectio of all headers.
    */
    inline HeaderValueCollection GetHeaders() const
    {
        return headerMap;
    }

    /**
    * Gets the collectio of all query param.
    */
    inline QueryParamCollection GetQueries() const
    {
        return queryMap;
    }

    /**
    * Gets the collectio of all query param.
    */
    inline std::string GetURLEncodedPath() const
    {
        return m_uri.GetURLEncodedPath();
    }

    /**
    * Get Encoded URL
    */
    inline std::string GetURIString() const
    {
        return m_uri.GetURIString();
    }

    /**
    * Get the http method for this request.
    */
    inline HttpMethod GetMethod() const
    {
        return m_method;
    }

    /**
    * Adds a query string parameter to the underlying URI by key and value.
    */
    inline void AddQueryStringParameter(const char *key, const std::string &value)
    {
        m_uri.AddQueryStringParameter(key, value);
    }

    /**
    * Gets content-length header.
    */
    inline const std::string GetContentLength() const
    {
        return GetHeaderValue(CONTENT_LENGTH_HEADER);
    }

    /**
    * Sets content-length header.
    */
    inline void SetContentLength(const std::string &value)
    {
        SetHeaderValue(CONTENT_LENGTH_HEADER, value);
    }

    /**
    * Gets the content body stream that will be used for this request.
    */
    std::iostream *GetContentBody() const
    {
        return bodyStream;
    };

    /**
     * Release the request body.
     */
    void ReleaseResponseBody()
    {
        if(bodyStream)
        {
            delete bodyStream;
            bodyStream = NULL;
        }
    }


private:
    std::iostream *bodyStream;
    URI m_uri;
    HttpMethod m_method;
    HeaderValueCollection headerMap;
    QueryParamCollection queryMap;
};

} // namespace Http
} // namespace QingStor
