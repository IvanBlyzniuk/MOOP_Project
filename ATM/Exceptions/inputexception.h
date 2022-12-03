#ifndef CARDINPUTEXCEPTION_H
#define CARDINPUTEXCEPTION_H

#include <exception>
#include <QException>
class InputException : public QException
{
public:
    InputException(const char* const message) : _message(message)
    {
    }
    const char* what() const noexcept override
    {
        return _message;
    }
private:
    const char* const _message;
};

#endif // CARDINPUTEXCEPTION_H
