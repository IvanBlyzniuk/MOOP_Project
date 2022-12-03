#ifndef ALREADYEXISTSEXCEPTION_H
#define ALREADYEXISTSEXCEPTION_H
class AlreadyExistsException : public QException
{
public:
    AlreadyExistsException(const char* const message) : _message(message)
    {
    }
    const char* what() const noexcept override
    {
        return _message;
    }
private:
    const char* const _message;
};
#endif // ALREADYEXISTSEXCEPTION_H
