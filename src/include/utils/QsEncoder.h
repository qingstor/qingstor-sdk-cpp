// +-------------------------------------------------------------------------
// | Copyright (C) 2016 Yunify, Inc.
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

#ifndef _WIN32
#include <stdlib.h>
#endif

#include <string>

namespace QingStor
{
namespace Utils
{
namespace Encoder
{
/* Encodes a binary safe base 64 string */
std::string	Base64Encode(const char *buffer, size_t length);

void 	sha256hmac(const char *str, char out[33], const char *secret);

} // namespace Encoder
} // namespace Utils
} // namespace QingStor

