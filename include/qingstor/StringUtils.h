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

#include <vector>
#include <string>

namespace QingStor
{
namespace Utils
{

class StringUtils
{
public:
    static bool HasPrefix(std::string & s, const char *prefix);

    static void Replace(std::string & s, const char *search,
                        const char *replace);

#ifdef _WIN32
    /**
    * Converts a string to wstring.
    */
    static std::wstring ToWString(const char *source);

    /**
    * Converts a wstring to string.
    */
    static std::string FromWString(const wchar_t * source);
#endif

    /**
    * Converts a string to lower case.
    */
    static std::string ToLower(const char *source);

    /**
    * Converts a string to upper case.
    */
    static std::string ToUpper(const char *source);

    /**
    * Does a caseless comparison of two strings.
    */
    static bool CaselessCompare(const char *value1, const char *value2);

    /**
    * URL encodes a string (uses %20 not + for spaces).
    */
    static std::string URLEncode(const char *unsafe);

    /**
    * URL encodes a double (if it ends up going to scientific notation) otherwise it just returns it as a string.
    */
    static std::string URLEncode(double unsafe);

    /**
    * Decodes a URL encoded string (will handle both encoding schemes for spaces).
    */
    static std::string URLDecode(const char *safe);

    /**
    * Splits a string on a delimiter (empty items are excluded).
    */
    static std::vector < std::string >
    Split(const std::string & toSplit, char splitOn);

    /**
     *  trim from start
     */
    static std::string LTrim(const char *source);

    /**
     * trim from end
     */
    static std::string RTrim(const char *source);

    /**
     * trim from both ends
     */
    static std::string Trim(const char *source);

    /**
     * convert to int 64
     */
    static long long ConvertToInt64(const char *source);

    /**
     * convert to int 32
     */
    static long ConvertToInt32(const char *source);

    /**
     * convert to bool
     */
    static bool ConvertToBool(const char *source);

    /**
     * convert to double
     */
    static double ConvertToDouble(const char *source);

};
}
}								// namespace QingStor
