#ifndef ICARD_H
#define ICARD_H
#include <QString>
#include "Product/ProductInfo.h"

class ICard;
template<typename Product>
class LoginParams;
template<>
class LoginParams<ICard>
{
public:
    QString Number;
    QString Pin;
};
template<>
class ProductCommonInfo <ICard>
{
public:
    using balance_type = double;
    using text_type = QString;
public:
    const text_type Number;
    const text_type Pin;
    const text_type Owner_firstname;
    const text_type Owner_lastname;
    balance_type Balance;
};

//ProductCommonInfo<ICard> p = {"2", "2345",...};
//make_registration(ProductCommonInfo<ICard>({"2", "3",...}))
//  dynamic_cast<shared_ptr<>>(ICard& smth)

//TODO addMoney, getMoney
class ICard
{
public:
    using info_type = ProductCommonInfo<ICard>;
    using balance_type = info_type::balance_type;
    using text_type = info_type::text_type;
public:
    virtual ~ICard() = default;
public:
    const text_type& card_number()          const noexcept;
    const text_type& card_pincode()         const noexcept;
    balance_type     card_balance()         const noexcept;
    void             set_balance(const balance_type);
private:
    virtual const text_type& do_card_number()        const noexcept  = 0;
    virtual const text_type& do_card_pincode()       const noexcept  = 0;
    virtual balance_type     do_card_balance()       const noexcept  = 0;
    virtual void             do_set_balance(const balance_type)      = 0;
};

inline auto ICard::card_number() const noexcept -> const text_type&
{
    return do_card_number();
}

inline auto ICard::card_pincode() const noexcept -> const text_type&
{
    return do_card_pincode();
}

inline auto ICard::card_balance() const noexcept -> balance_type
{
    return do_card_balance();
}

inline auto ICard::set_balance(const balance_type new_val) -> void
{
    return do_set_balance(new_val);
}

#endif // ICARD_H
