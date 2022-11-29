#ifndef CARDREGISTRATOR_H
#define CARDREGISTRATOR_H
#include "DB/iserializer.h"
#include "Product/Cards/icard.h"
#include "aregistrator.h"
#include "RegistratorTypedefs.h"

#define CardRegTemplate \
template<std::derived_from<ICardRegistrator::product_abstract_type> CardType>

#define CardRegMember \
CardRegTemplate \
CardRegistrator<CardType> ::

#define CardRegMethod \
CardRegTemplate \
auto CardRegistrator<CardType> ::

//using ICardRegistrator = ARegistrator<ICard>;

CardRegTemplate
class CardRegistrator : public ICardRegistrator
{
public:
    template<typename T>
    using ptr = std::shared_ptr<T>;
    using product_type = CardType;
    using serializer_ptr = ptr<ISerializer>;
public:
    CardRegistrator(serializer_ptr) noexcept;
private:
    void do_make_registration(const product_abstract_type&) const override;
    void do_remove_registration(const product_abstract_type&) const override;
    bool do_can_be_registered(const product_abstract_type&) const noexcept override;
private:
    serializer_ptr _db;
};

CardRegMember CardRegistrator(serializer_ptr db) noexcept :
    _db(db)
{

}

CardRegMethod do_make_registration(const product_abstract_type& info) const -> void
{
    //if(can_be_registered())
    //{

        //_db->serialize()
    //}
    //else throw
}

CardRegMethod do_remove_registration(const product_abstract_type& info) const -> void
{
    //if (can_be_registered(info))
    //{
        //_db->serialize()
    //}
    //else throw
}

CardRegMethod do_can_be_registered(const product_abstract_type& info) const noexcept -> bool
{
    return false;//!_db->exists(info);
}

using DebitCardRegistrator = CardRegistrator<DebitCard>;
using CreditCardRegistrator = CardRegistrator<CreditCard>;

#endif // CARDREGISTRATOR_H
