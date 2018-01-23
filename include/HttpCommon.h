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
#include "StringUtils.h"
#include <map>
#include <memory>
#include <utility>

namespace QingStor
{
namespace Http
{
/**
 *  Http methods.
 */
enum HttpMethod
{
    HTTP_GET,
    HTTP_POST,
    HTTP_DELETE,
    HTTP_PUT,
    HTTP_HEAD,
    HTTP_OPTIONS,
    HTTP_PATCH
};

namespace HttpMethodMapper
{
/**
 * Gets the string value of an httpMethod.
 */
QS_SDK_API const char *GetNameForHttpMethod(HttpMethod httpMethod);
} typedef std::pair < std::string, std::string > HeaderValuePair;
typedef std::map < std::string, std::string > HeaderValueCollection;
typedef std::map < std::string, std::string > QueryParamCollection;

/**
 * Enum representing URI scheme.
 */
enum Scheme
{
    HTTP,
    HTTPS
};

namespace SchemeMapper
{
/**
 * Converts a Scheme instance to a String.
 */
QS_SDK_API const char *ToString(Scheme scheme);
/**
* Converts a string instance to a Scheme. Defaults to https.
*/
QS_SDK_API Scheme FromString(const char *name);
} enum HttpResponseCode
{
    REQUEST_NOT_MADE = 0,
    CONTINUE = 100,
    SWITCHING_PROTOCOLS = 101,
    PROCESSING = 102,
    OK = 200,
    CREATED = 201,
    ACCEPTED = 202,
    NON_AUTHORITATIVE_INFORMATION = 203,
    NO_CONTENT = 204,
    RESET_CONTENT = 205,
    PARTIAL_CONTENT = 206,
    MULTI_STATUS = 207,
    ALREADY_REPORTED = 208,
    IM_USED = 226,
    MULTIPLE_CHOICES = 300,
    MOVED_PERMANENTLY = 301,
    FOUND = 302,
    SEE_OTHER = 303,
    NOT_MODIFIED = 304,
    USE_PROXY = 305,
    SWITCH_PROXY = 306,
    TEMPORARY_REDIRECT = 307,
    PERMANENT_REDIRECT = 308,
    BAD_REQUEST = 400,
    UNAUTHORIZED_OR_EXPIRED = 401,
    DELINQUENT_ACCOUNT = 402,
    FORBIDDEN = 403,
    NOT_FOUND = 404,
    METHOD_NOT_ALLOWED = 405,
    CONFLICT = 409,
    PRECONDITION_FAILED = 412,
    INVALID_RANGE = 416,
    TOO_MANY_REQUESTS = 429,
    INTERNAL_SERVER_ERROR = 500,
    SERVICE_UNAVAILABLE = 503,
    GATEWAY_TIMEOUT = 504,
    HTTP_VERSION_NOT_SUPPORTED = 505,
    VARIANT_ALSO_NEGOTIATES = 506,
    INSUFFICIENT_STORAGE = 506,
    LOOP_DETECTED = 508,
    BANDWIDTH_LIMIT_EXCEEDED = 509,
    NOT_EXTENDED = 510,
    NETWORK_AUTHENTICATION_REQUIRED = 511,
    NETWORK_READ_TIMEOUT = 598,
    NETWORK_CONNECT_TIMEOUT = 599
};
}
}								// namespace QingStor
