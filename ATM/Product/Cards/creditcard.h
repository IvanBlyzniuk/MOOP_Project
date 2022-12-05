#ifndef CREDITCARD_H
#define CREDITCARD_H
#include "Product/Cards/icard.h"
#include "Exceptions/inputexception.h"

class CreditCard : public ICard
{
public:
    CreditCard(const common_info_type&, const balance_type = s_dflt_credit_limit);
    ~CreditCard() override = default;
public:
    balance_type credit_limit() const noexcept;
    void set_credit_limit(const balance_type);
private:
    const text_type& do_card_number()          const noexcept override;
    const text_type& do_card_pincode()         const noexcept override;
    balance_type     do_card_balance()         const noexcept override;
    void             do_set_balance(const balance_type)       override;
    const KeyInfoBase&    do_key_info()        const noexcept override;
    const LoginInfoBase&  do_login_info()      const noexcept override;
    const CommonInfoBase& do_common_info()     const noexcept override;
    const text_type& do_owner_firstname()      const noexcept override;
    const text_type& do_owner_lastname()       const noexcept override;
    void do_set_pin(const text_type&)                         override;
private:
    bool check_input() const noexcept;
private:
    common_info_type _info;
    balance_type _credit_limit;
private:
    static constexpr balance_type s_dflt_credit_limit = 0;
};

inline CreditCard::CreditCard
(
    const common_info_type& info,
    const balance_type credit_limit
) :
    _info(info),
    _credit_limit(credit_limit)
{
    if (!check_input())
    {
        throw InputException("Incorrect card input.");
    }
}

inline auto CreditCard::credit_limit() const noexcept -> balance_type
{
    return _credit_limit;
}

inline void CreditCard::set_credit_limit(const balance_type credit_limit)
{
    if (credit_limit < 0)
        throw InputException("Negative credit limit");
    _credit_limit = credit_limit;
}

inline auto CreditCard::do_card_number() const noexcept -> const text_type&
{
    return _info.get_number();
}

inline auto CreditCard::do_card_pincode() const noexcept -> const text_type&
{
    return _info.get_pin();
}

inline auto CreditCard::do_card_balance() const noexcept -> balance_type
{
    return _info.get_balance();
}

inline auto CreditCard::do_set_balance(const balance_type nval) -> void
{
    if(nval < -credit_limit())
        throw InputException("Balance cannot exceed credit limit.");
    _info.set_balance(nval);
}

inline const ProductKeyInfo<IProduct> &CreditCard::do_key_info() const noexcept
{
    return _info.get_key();
}

inline const LoginParams<IProduct> &CreditCard::do_login_info() const noexcept
{
    return _info.get_login_info();
}

inline const ProductCommonInfo<IProduct> &CreditCard::do_common_info() const noexcept
{
    return _info;
}

inline auto CreditCard::check_input() const noexcept -> bool
{
    //TODO text input checking
    return card_balance() >= 0;
}

inline auto CreditCard::do_owner_firstname() const noexcept -> const text_type&
{
    return _info.get_owner_firstname();
}
inline auto CreditCard::do_owner_lastname() const noexcept -> const text_type&
{
    return _info.get_owner_lastname();
}

inline void CreditCard::do_set_pin(const text_type & new_pin)
{
    _info.set_pin(new_pin);
}

#endif // CREDITCARD_H
