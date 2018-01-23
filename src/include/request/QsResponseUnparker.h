
#include "external/json/json.h"

//
class QS_SDK_API QsResponseUnparker
{
public:
    /**
     * Defult and Base Unparker Class
     */
    QsResponseUnparker() {};

    virtual ~QsResponseUnparker() {};

    virtual void ParseRequestID(const std::string &requestID) = 0;

    virtual void ParseResponseErrInfo(std::iostream * responseBody) = 0;

    virtual bool CheckIfResponseExpected(Http::HttpResponseCode responseCode) = 0;

    virtual void ParseResponseHeaders(const Http::HeaderValueCollection &headerValueCollection)=0;

    virtual void ParseResponseBody(std::iostream *responseBody) = 0;

    virtual bool CkeckIfNeedReleaseBody() = 0;

};

template <typename OutputType>
class QS_SDK_API QsDefaultResponseUnparker : public QsResponseUnparker
{
public:
    /**
     * Defult and Base Unparker Class
     */
    QsDefaultResponseUnparker(OutputType *output) : QsResponseUnparker(), m_output(output),m_bNeedReleaseBody(false) {};

    virtual ~QsDefaultResponseUnparker() {};

    virtual void ParseResponseHeaders(const Http::HeaderValueCollection &headerValueCollection)
    {
        return;
    };

    virtual void ParseResponseBody(std::iostream *responseBody)
    {
        m_bNeedReleaseBody = true;
        return;
    };

    bool CkeckIfNeedReleaseBody()
    {
        return m_bNeedReleaseBody;
    };

    bool CheckIfResponseExpected(Http::HttpResponseCode responseCode)
    {
        m_output->SetResponseCode(responseCode);
        return true;
    };

    virtual void ParseRequestID(const std::string &requestID)
    {
        m_output->SetRequestID(requestID);
    };

    void ParseResponseErrInfo(std::iostream * responseBody)
    {
        QingStor::ResponseErrorInfo errorInfo;
        // parse json content
        Json::Reader jsonReader;
        Json::Value jsonContent;
        jsonReader.parse(*responseBody, jsonContent);
        if (jsonContent.isMember("code"))
        {
            errorInfo.code = jsonContent["code"].asString();
        }
        if (jsonContent.isMember("message"))
        {
            errorInfo.message = jsonContent["message"].asString();
        }
        if (jsonContent.isMember("request_id"))
        {
            errorInfo.requestID = jsonContent["request_id"].asString();
        }
        if (jsonContent.isMember("url"))
        {
            errorInfo.url = jsonContent["url"].asString();
        }
        m_output->SetResponseErrInfo(errorInfo);
        m_bNeedReleaseBody = true;
    }

protected:
    OutputType *m_output;
    bool m_bNeedReleaseBody;
};
