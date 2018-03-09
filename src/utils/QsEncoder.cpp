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

#include "utils/QsEncoder.h"
#include <string>
#include<string.h>

#include <openssl/hmac.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <openssl/sha.h>

static const char base64_encode_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

namespace QingStor
{
namespace Utils
{
namespace Encoder
{

std::string Base64Encode(const unsigned char *buffer, size_t length)
{
    size_t blockCount = (length + 2) / 3;
    size_t remainderCount = (length % 3);

    std::string outputString;
    outputString.reserve(4 * ((length + 2) / 3));

    for(size_t i = 0; i < length; i += 3 )
    {
        unsigned int block = buffer[ i ];

        block <<= 8;
        if (i + 1 < length)
        {
            block = block | buffer[ i + 1 ];
        }

        block <<= 8;
        if (i + 2 < length)
        {
            block = block | buffer[ i + 2 ];
        }

        outputString.push_back(base64_encode_table[(block >> 18) & 0x3F]);
        outputString.push_back(base64_encode_table[(block >> 12) & 0x3F]);
        outputString.push_back(base64_encode_table[(block >> 6) & 0x3F]);
        outputString.push_back(base64_encode_table[block & 0x3F]);
    }

    if(remainderCount > 0)
    {
        outputString[blockCount * 4 - 1] = '=';
        if(remainderCount == 1)
        {
            outputString[blockCount * 4 - 2] = '=';
        }
    }

    return outputString;
}


void sha256hmac(const char *str, unsigned char out[33], const char *secret)
{
    unsigned int len = 32;
    (void)HMAC(EVP_sha256(), secret, strlen(secret), (unsigned char *)str, strlen(str), out, &len);
    out[32] = '\0';
    return;
}

}
} // namespace Utils
} // namespace QingStor