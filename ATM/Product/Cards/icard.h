#ifndef ICARD_H
#define ICARD_H
#include <QString>
#include "Product/ProductInfo.h"

class ICard;

template<>
class ProductKeyInfo<ICard>
{
public:
    using text_type = QString;
public:
    ProductKeyInfo(const text_type& number) noexcept :
        _number(number)
    {}
public:
    const text_type& get_number() const noexcept { return _number; }
private:
    const QString _number;
};

template<>
class LoginParams<ICard>
{
public:
    using text_type = ProductKeyInfo<ICard>::text_type;
public:
    LoginParams(const text_type& number, const text_type& pin) noexcept :
        _key({number}), _pin(pin)
    {}
public:
    const ProductKeyInfo<ICard>& get_key () const noexcept {return _key; }
    const text_type& get_number() const noexcept { return get_key().get_number(); }
    const text_type& get_pin() const noexcept { return _pin; }
private:
    ProductKeyInfo<ICard> _key;
    const text_type _pin;
};

template<>
class ProductCommonInfo <ICard>
{
public:
    using balance_type = double;
    using text_type = LoginParams<ICard>::text_type;
public:
    ProductCommonInfo
    (
        const text_type number,
        const text_type pin,
        const text_type owner_firstname,
        const text_type owner_lastname,
        const balance_type balance
    ) noexcept :
        _login_info({number, pin}),
        _owner_firstname(owner_firstname),
        _owner_lastname(owner_lastname),
        _balance(balance)
    {}
public:
    const ProductKeyInfo<ICard>& get_key () const noexcept {return get_login_info().get_key(); }
    const LoginParams<ICard>& get_login_info() const noexcept { return _login_info; }
    const text_type&    get_number() const noexcept { return get_login_info().get_number(); }
    const text_type&    get_pin() const noexcept { return get_login_info().get_pin(); }
    const text_type&    get_owner_firstname() const noexcept { return _owner_firstname; }
    const text_type&    get_owner_lastname() const noexcept { return _owner_lastname; }
    const balance_type  get_balance() const noexcept { return _balance; }
    void set_balance(const balance_type bal) { _balance = bal; }
private:
    LoginParams<ICard> _login_info;
    const text_type _owner_firstname;
    const text_type _owner_lastname;
    balance_type _balance;
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
