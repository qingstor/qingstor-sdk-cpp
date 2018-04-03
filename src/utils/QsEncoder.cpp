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

#ifdef _WIN32
#include <windows.h>
#include <wincrypt.h>

typedef struct _qs_blob {

	BLOBHEADER hdr;

	DWORD dwKeySize;

	BYTE rgbKeyData[];

}qs_blob;
#else
#include <openssl/hmac.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <openssl/sha.h>
#endif

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


void sha256hmac(std::string src, unsigned char out[33], std::string secret)
{
#ifdef _WIN32

	DWORD kbLen = sizeof(qs_blob) + secret.size();
	qs_blob * kb = (qs_blob *)LocalAlloc(LPTR, kbLen);
	kb->hdr.bType = PLAINTEXTKEYBLOB;
	kb->hdr.bVersion = CUR_BLOB_VERSION;
	kb->hdr.reserved = 0;
	kb->hdr.aiKeyAlg = CALG_RC2;
	kb->dwKeySize = secret.size();
	memcpy(&kb->rgbKeyData, secret.c_str(), secret.size());
	
	HCRYPTPROV hProv = 0;
	HCRYPTKEY hKey = 0;
	HCRYPTHASH hHmacHash = 0;
	BYTE pbHash[32];
	DWORD dwDataLen = 32;

	HMAC_INFO HmacInfo;
	ZeroMemory(&HmacInfo, sizeof(HmacInfo));
	HmacInfo.HashAlgid = CALG_SHA_256;

	CryptAcquireContext(&hProv, NULL, MS_ENHANCED_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_NEWKEYSET);
	CryptImportKey(hProv, (BYTE*)kb, kbLen, 0, CRYPT_IPSEC_HMAC_KEY, &hKey);
	CryptCreateHash(hProv, CALG_HMAC, hKey, 0, &hHmacHash);
	CryptSetHashParam(hHmacHash, HP_HMAC_INFO, (BYTE*)&HmacInfo, 0);
	CryptHashData(hHmacHash, (BYTE*)(src.c_str()), src.size(),0);
	CryptGetHashParam(hHmacHash, HP_HASHVAL, pbHash, &dwDataLen, 0);

	LocalFree(kb);
	CryptDestroyHash(hHmacHash);
	CryptDestroyKey(hKey);
	CryptReleaseContext(hProv, 0);

	memcpy(out, pbHash, dwDataLen);
#else

    unsigned int len = 32;
	(void)HMAC(EVP_sha256(), secret.c_str(), secret.size(), (unsigned char *)src, strlen(src), out, &len);
  
#endif
	out[32] = '\0';
    return;
}

}
} // namespace Utils
} // namespace QingStor