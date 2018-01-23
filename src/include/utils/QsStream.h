
#pragma once

#include "QsSdkOption.h"
#include <utils/QsAlloc.h>

#include <iostream>

typedef std::basic_stringbuf<char, std::char_traits<char>, std::allocator<char> > StringBuf;

namespace QingStor
{
class QsStream : public std::iostream
{
public:
    typedef   std::iostream Base;
    QsStream() : Base(QingStor::New<StringBuf>()) {};
    virtual ~QsStream()
    {
        if (rdbuf())
        {
            QingStor::Delete(rdbuf());
        }
    };
};
}