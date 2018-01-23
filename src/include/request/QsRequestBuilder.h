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
#include "QsErrors.h"
#include "QsConfig.h"
#include "signer/QsSigner.h"
#include "HttpCommon.h"
#include "http/HttpClient.h"
#include "Types.h"
#include  <memory>

using namespace QingStor;

class QS_SDK_API QsRequestBuilder
{
public:
    /**
     * Defult and Base Builder Class
     */
    QsRequestBuilder() {};

    virtual ~QsRequestBuilder() {};

    virtual bool CkeckIfInputIsVaild() = 0;

    virtual Http::HeaderValueCollection GetHeaderValueCollection() = 0;

    virtual Http::QueryParamCollection  GetQueryParamCollection() = 0;

    virtual std::iostream* GetRequestBody() = 0;

    virtual bool CkeckIfNeedReleaseBody() = 0;

};


template<typename InputType>
class QS_SDK_API QsDefaultRequestBuilder :public QsRequestBuilder
{
public:
    /**
    * Defult and Base Unparker Class
    */
    QsDefaultRequestBuilder(InputType * input) :QsRequestBuilder(), m_input(input),m_bNeedReleaseBody(false) {};

    virtual ~QsDefaultRequestBuilder() {};

    virtual bool CkeckIfInputIsVaild()
    {
        return true;
    };
    virtual Http::HeaderValueCollection GetHeaderValueCollection()
    {
        Http::HeaderValueCollection emptyCollection;
        return emptyCollection;
    }

    virtual Http::QueryParamCollection  GetQueryParamCollection()
    {
        Http::QueryParamCollection emptyCollection;
        return emptyCollection;
    }

    virtual std::iostream* GetRequestBody()
    {
        return NULL;
    };

    bool CkeckIfNeedReleaseBody()
    {
        return m_bNeedReleaseBody;
    };

protected:
    InputType * m_input;
    bool m_bNeedReleaseBody;
};
