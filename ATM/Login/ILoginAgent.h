#ifndef ILOGINAGENT_H
#define ILOGINAGENT_H

#include <memory>

template<typename Product>
class LoginParams;
template<typename AbstractProduct>
class ILoginAgent
{
public:
    std::shared_ptr<AbstractProduct> login(const LoginParams<AbstractProduct>&) const;
    virtual ~ILoginAgent() = default;
private:
    virtual std::shared_ptr<AbstractProduct> do_login(const LoginParams<AbstractProduct>&) const = 0;
};
template<typename AbstractProduct>
inline std::shared_ptr<AbstractProduct> ILoginAgent<AbstractProduct>::login(const LoginParams<AbstractProduct> & param) const
{
    return do_login(param);
}


#endif // ILOGINAGENT_H
