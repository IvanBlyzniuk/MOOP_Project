#ifndef CARDLOGINAGENT_H
#define CARDLOGINAGENT_H

#include <DB/iserializer.h>
#include "Login/ILoginAgent.h"
#include "Product/Cards/icard.h"
#include "Utils/casting.h"



class CardLoginAgent : public ILoginAgent<ICard>
{
public:
    CardLoginAgent(const std::shared_ptr<ISerializer>);
private:
    std::shared_ptr<ISerializer> serializer;
    std::shared_ptr<ICard> do_login(const LoginParams<ICard>&) const;
};


CardLoginAgent::CardLoginAgent(const std::shared_ptr<ISerializer> s) : serializer(s)
{
}

inline std::shared_ptr<ICard> CardLoginAgent::do_login(const LoginParams<ICard> & params) const
{

    try
    {
        std::shared_ptr<ICard> card = cast_to<ICard>(serializer -> deserialize(params));
        return card;
    }
    catch (...)
    {
        throw;
    }

}





#endif // CARDLOGINAGENT_H
