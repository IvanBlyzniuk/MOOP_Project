#ifndef NOTENOUGHMONEYEXCEPTION_H
#define NOTENOUGHMONEYEXCEPTION_H

#include <QException>>

class NotEnoughMoneyException : public QException
{
public:
    NotEnoughMoneyException(const char* const message) : _message(message)
    {
    }
    const char* what() const noexcept override
    {
        return _message;
    }
private:
    const char* const _message;
};

#endif // NOTENOUGHMONEYEXCEPTION_H
