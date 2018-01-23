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

namespace QingStor
{
namespace Utils
{
namespace Encoder
{
/* Encodes a binary safe base 64 string */
std::string	Base64Encode(const char *buffer, size_t length)
{
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;
    char *ret;
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);  // Ignore newlines - write
    // everything in one line
    BIO_write(bio, buffer, length);
    (void) BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
    ret = (char *) malloc(bufferPtr->length + 1);
    memcpy(ret, bufferPtr->data, bufferPtr->length);
    ret[bufferPtr->length] = 0;
    (void) BIO_set_close(bio, BIO_NOCLOSE);
    BIO_free_all(bio);
    std::string strEncoded(ret);
    free(ret);
#ifndef _WIN32
    free(bufferPtr->data);
    free(bufferPtr);
#endif
    return strEncoded;
}


void sha256hmac(const char *str, char out[33], const char *secret)
{
    unsigned int len = 32;
    (void)HMAC(EVP_sha256(), secret, strlen(secret), (unsigned char *)str, strlen(str), (unsigned char *)out, &len);
    out[32] = '\0';
    return;
}

}
} // namespace Utils
} // namespace QingStor