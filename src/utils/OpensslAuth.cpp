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

#ifdef _WIN32
#else
#include "utils/OpensslAuth.h"
#include "plog/Log.h"
using namespace std;

//-------------------------------------------------------------------
// Utility Function for version
//-------------------------------------------------------------------
const char* qingstor_crypt_lib_name(void)
{
  static const char version[] = "OpenSSL";

  return version;
}
/*
//-------------------------------------------------------------------
// Utility Function for global init
//-------------------------------------------------------------------
bool qingstor_init_global_ssl(void)
{
  ERR_load_crypto_strings();
  ERR_load_BIO_strings();
  OpenSSL_add_all_algorithms();
  return true;
}

bool qingstor_destroy_global_ssl(void)
{
  EVP_cleanup();
  ERR_free_strings();
  return true;
}
*/
//-------------------------------------------------------------------
// Utility Function for crypt lock
//-------------------------------------------------------------------
// internal use struct for openssl
struct CRYPTO_dynlock_value
{
  pthread_mutex_t dyn_mutex;
};

static pthread_mutex_t* qingstor_crypt_mutex = NULL;

static void qingstor_crypt_mutex_lock(int mode, int pos, const char* file, int line)
{
  if(qingstor_crypt_mutex){
    if(mode & CRYPTO_LOCK){
      pthread_mutex_lock(&qingstor_crypt_mutex[pos]);
    }else{
      pthread_mutex_unlock(&qingstor_crypt_mutex[pos]);
    }
  }
}

static unsigned long qingstor_crypt_get_threadid(void)
{
  // For FreeBSD etc, some system's pthread_t is structure pointer.
  // Then we use cast like C style(not C++) instead of ifdef.
  return (unsigned long)(pthread_self());
}

static struct CRYPTO_dynlock_value* qingstor_dyn_crypt_mutex(const char* file, int line)
{
  struct CRYPTO_dynlock_value* dyndata;

  if(NULL == (dyndata = static_cast<struct CRYPTO_dynlock_value*>(malloc(sizeof(struct CRYPTO_dynlock_value))))){
    LOG_FATAL << "Could not allocate memory for CRYPTO_dynlock_value";
    return NULL;
  }
  pthread_mutex_init(&(dyndata->dyn_mutex), NULL);
  return dyndata;
}

static void qingstor_dyn_crypt_mutex_lock(int mode, struct CRYPTO_dynlock_value* dyndata, const char* file, int line)
{
  if(dyndata){
    if(mode & CRYPTO_LOCK){
      pthread_mutex_lock(&(dyndata->dyn_mutex));
    }else{
      pthread_mutex_unlock(&(dyndata->dyn_mutex));
    }
  }
}

static void qingstor_destroy_dyn_crypt_mutex(struct CRYPTO_dynlock_value* dyndata, const char* file, int line)
{
  if(dyndata){
    pthread_mutex_destroy(&(dyndata->dyn_mutex));
    free(dyndata);
  }
}

bool qingstor_init_crypt_mutex(void)
{
  if(qingstor_crypt_mutex){
    LOG_FATAL << "qingstor_crypt_mutex is not NULL, destroy it.";
    if(!qingstor_destroy_crypt_mutex()){
      LOG_ERROR << "Failed to qingstor_crypt_mutex";
      return false;
    }
  }
  if(NULL == (qingstor_crypt_mutex = static_cast<pthread_mutex_t*>(malloc(CRYPTO_num_locks() * sizeof(pthread_mutex_t))))){
     LOG_FATAL << "Could not allocate memory for qingstor_crypt_mutex";
    return false;
  }
  for(int cnt = 0; cnt < CRYPTO_num_locks(); cnt++){
    pthread_mutex_init(&qingstor_crypt_mutex[cnt], NULL);
  }
  // static lock
  CRYPTO_set_locking_callback(qingstor_crypt_mutex_lock);
  CRYPTO_set_id_callback(qingstor_crypt_get_threadid);
  // dynamic lock
  CRYPTO_set_dynlock_create_callback(qingstor_dyn_crypt_mutex);
  CRYPTO_set_dynlock_lock_callback(qingstor_dyn_crypt_mutex_lock);
  CRYPTO_set_dynlock_destroy_callback(qingstor_destroy_dyn_crypt_mutex);

  return true;
}

bool qingstor_destroy_crypt_mutex(void)
{
  if(!qingstor_crypt_mutex){
    return true;
  }

  CRYPTO_set_dynlock_destroy_callback(NULL);
  CRYPTO_set_dynlock_lock_callback(NULL);
  CRYPTO_set_dynlock_create_callback(NULL);
  CRYPTO_set_id_callback(NULL);
  CRYPTO_set_locking_callback(NULL);

  for(int cnt = 0; cnt < CRYPTO_num_locks(); cnt++){
    pthread_mutex_destroy(&qingstor_crypt_mutex[cnt]);
  }
  CRYPTO_cleanup_all_ex_data();
  free(qingstor_crypt_mutex);
  qingstor_crypt_mutex = NULL;

  return true;
}

//-------------------------------------------------------------------
// Utility Function for HMAC
//-------------------------------------------------------------------
static bool qingstor_HMAC_RAW(const void* key, size_t keylen, const unsigned char* data, size_t datalen, unsigned char* digest, unsigned int* digestlen, bool is_sha256)
{
  if(!key || !data || !digest || !digestlen){
    return false;
}
/*
  (*digestlen) = EVP_MAX_MD_SIZE * sizeof(unsigned char);
  if(NULL == ((*digest) = (unsigned char*)malloc(*digestlen))){
    return false;
}
*/
  if(is_sha256){
    HMAC(EVP_sha256(), key, keylen, data, datalen, digest, digestlen);
  }else{
    HMAC(EVP_sha1(), key, keylen, data, datalen, digest, digestlen);
  }

  return true;
}

bool qingstor_HMAC256(const void* key, size_t keylen, const unsigned char* data, size_t datalen, unsigned char* digest, unsigned int* digestlen)
{
  return qingstor_HMAC_RAW(key, keylen, data, datalen, digest, digestlen, true);
}

#endif
