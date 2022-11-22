#ifndef CARDINPUTEXCEPTION_H
#define CARDINPUTEXCEPTION_H

#include <exception>

class InputException : public std::exception
{
public:
    InputException(const char* const message) :
        std::exception(message)
    {
    }
};

#endif // CARDINPUTEXCEPTION_H
