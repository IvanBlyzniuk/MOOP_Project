#ifndef DOESNTEXISTEXCEPTION_H
#define DOESNTEXISTEXCEPTION_H
class DoesntExistException : public QException
{
public:
    DoesntExistException(const char* const message) : _message(message)
    {
    }
    const char* what() const noexcept override
    {
        return _message;
    }
private:
    const char* const _message;
};
#endif // DOESNTEXISTEXCEPTION_H
