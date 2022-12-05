#ifndef MANAGERLOGINAGENT_H
#define MANAGERLOGINAGENT_H
#include <DB/iserializer.h>
#include "Product/Managers/amanager.h"
#include "Login/ILoginAgent.h"
#include "Utils/casting.h"




class ManagerLoginAgent : public ILoginAgent<AManager>
{
public:
    ManagerLoginAgent(const std::shared_ptr<ISerializer>);
private:
    std::shared_ptr<ISerializer> serializer;
    std::shared_ptr<AManager> do_login(const LoginParams<AManager>&) const;
};


ManagerLoginAgent::ManagerLoginAgent(const std::shared_ptr<ISerializer> s) : serializer(s)
{
}

inline std::shared_ptr<AManager> ManagerLoginAgent::do_login(const LoginParams<AManager> & params) const
{
    std::shared_ptr<AManager> manager = cast_to<AManager>(serializer -> deserialize(params));
    return manager;
}

#endif // MANAGERLOGINAGENT_H
