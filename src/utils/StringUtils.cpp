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

#include "StringUtils.h"
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <functional>
#include <stdio.h>

using namespace QingStor::Utils;

#ifdef _WIN32

std::wstring StringUtils::ToWString(const char* source)
{
    std::wstring outString;
    outString.resize(std::strlen(source));
    std::copy(source, source + std::strlen(source), outString.begin());
    return outString;
}

std::string StringUtils::FromWString(const wchar_t* source)
{
    std::wstring inWString(source);
    std::string outString(inWString.begin(), inWString.end());
    return outString;
}

#endif

bool StringUtils::HasPrefix(std::string& s, const char* prefix)
{
    if (!prefix)
    {
        return false;
    }
    std::size_t pos = 0;
    pos = s.find(prefix, pos);
    return (pos != std::string::npos);
}

void StringUtils::Replace(std::string& s, const char* search, const char* replace)
{
    if(!search || !replace)
    {
        return;
    }
    size_t replaceLength = strlen(replace);
    size_t searchLength = strlen(search);
    for (std::size_t pos = 0;; pos += replaceLength)
    {
        pos = s.find(search, pos);
        if (pos == std::string::npos)
            break;
        s.erase(pos, searchLength);
        s.insert(pos, replace);
    }
}


std::string StringUtils::ToLower(const char* source)
{
    std::string copy;
    size_t sourceLength = strlen(source);
    for(size_t i = 0; i < sourceLength; i++)
    {
        copy += tolower(source[i]);
    }
    return copy;
}


std::string StringUtils::ToUpper(const char* source)
{
    std::string copy;
    size_t sourceLength = strlen(source);
    for(size_t i = 0; i < sourceLength; i++)
    {
        copy += toupper(source[i]);
    }
    return copy;
}


bool StringUtils::CaselessCompare(const char* value1, const char* value2)
{
    std::string value1Lower = ToLower(value1);
    std::string value2Lower = ToLower(value2);
    return value1Lower == value2Lower;
}


std::vector<std::string> StringUtils::Split(const std::string& toSplit, char splitOn)
{
    // std::stringstream input(toSplit.c_str());
    std::stringstream ss;
    ss << toSplit;
    std::vector<std::string> returnValues;
    std::string item;
    while (std::getline(ss, item, splitOn))
    {
        if(item.size() > 0)
        {
            returnValues.push_back(item);
        }
    }
    return returnValues;
}


std::string StringUtils::URLEncode(const char* unsafe)
{
    std::stringstream escaped;
    escaped.fill('0');
    escaped << std::hex << std::uppercase;
    size_t unsafeLength = strlen(unsafe);
    const char  * i;
    const char  * n;
    n = unsafe + unsafeLength;
    for ( i = unsafe ; i != n; ++i)
    {
        int c = *i;
        //MSVC 2015 has an assertion that c is positive in isalnum(). This breaks unicode support.
        //bypass that with the first check.
        if (c >= 0 && (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~' || c == '=') )
        {
            escaped << (char)c;
        }
        else
        {
            //this unsigned char cast allows us to handle unicode characters.
            escaped << '%' << std::setw(2) << int((unsigned char)c) << std::setw(0);
        }
    }
    return escaped.str();
}

std::string StringUtils::URLEncode(double unsafe)
{
    char buffer[32];
#if defined(_MSC_VER) && _MSC_VER < 1900
    _snprintf_s(buffer, sizeof(buffer), _TRUNCATE, "%g", unsafe);
#else
    snprintf(buffer, sizeof(buffer), "%g", unsafe);
#endif
    return StringUtils::URLEncode(buffer);
}


std::string StringUtils::URLDecode(const char* safe)
{
    std::stringstream unescaped;
    unescaped.fill('0');
    unescaped << std::hex;
    size_t safeLength = strlen(safe);
    const char* n = safe + safeLength;
    for (const char* i = safe; i != n; ++i)
    {
        char c = *i;
        if(c == '%')
        {
            char hex[3];
            hex[0] = *(i + 1);
            hex[1] = *(i + 2);
            hex[2] = 0;
            i += 2;
            long int hexAsInteger = strtol(hex, NULL, 16);
            unescaped << (char)hexAsInteger;
        }
        else
        {
            unescaped << *i;
        }
    }
    return unescaped.str();
}

std::string StringUtils::LTrim(const char* source)
{
    std::string copy(source);
    copy.erase(copy.begin(), std::find_if(copy.begin(), copy.end(), std::not1(std::ptr_fun<int, int>(::isspace))));
    return copy;
}

// trim from end
std::string StringUtils::RTrim(const char* source)
{
    std::string copy(source);
    copy.erase(std::find_if(copy.rbegin(), copy.rend(), std::not1(std::ptr_fun<int, int>(::isspace))).base(), copy.end());
    return copy;
}

// trim from both ends
std::string StringUtils::Trim(const char* source)
{
    return LTrim(RTrim(source).c_str());
}

long long StringUtils::ConvertToInt64(const char* source)
{
    if(!source)
    {
        return 0;
    }
    return std::atoll(source);
}


long StringUtils::ConvertToInt32(const char* source)
{
    if (!source)
    {
        return 0;
    }
    return std::atol(source);
}


bool StringUtils::ConvertToBool(const char* source)
{
    if(!source)
    {
        return false;
    }
    std::string strValue = ToLower(source);
    if(strValue == "true" || strValue == "1")
    {
        return true;
    }
    return false;
}


double StringUtils::ConvertToDouble(const char* source)
{
    if(!source)
    {
        return 0.0;
    }
    return std::strtod(source, NULL);
}



