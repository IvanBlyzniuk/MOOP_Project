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

CardRegTemplate
class CardRegistrator : public ICardRegistrator
{
public:
    using product_type = CardType;
    using serializer_ptr = std::shared_ptr<ISerializer>;
public:
    CardRegistrator(serializer_ptr) noexcept;
private:
    void do_make_registration(product_ptr) const override;
    void do_remove_registration(const product_key_type&) const override;
    bool do_can_be_registered(const product_key_type&) const noexcept override;
private:
    serializer_ptr _db;
};

CardRegMember CardRegistrator(serializer_ptr db) noexcept :
    _db(db)
{

}

CardRegMethod do_make_registration(product_ptr info) const -> void
{
    _db->serialize(info);
}

CardRegMethod do_remove_registration(const product_key_type& info) const -> void
{
    _db->remove_card(info);
}

CardRegMethod do_can_be_registered(const product_key_type& info) const noexcept -> bool
{
    return !_db->exists_card(info);
}

using DebitCardRegistrator = CardRegistrator<DebitCard>;
using CreditCardRegistrator = CardRegistrator<CreditCard>;

#endif // CARDREGISTRATOR_H
