#ifndef DEBITCARD_H
#define DEBITCARD_H
#include "icard.h"
#include "Exceptions\inputexception.h"

class DebitCard : public ICard
{
public:
    DebitCard(const common_info_type&);
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
};

inline DebitCard::DebitCard(const common_info_type& info) :
    _info(info)
{
    if (!check_input())
    {
        throw InputException("Incorrect card input.");
    }
}

inline auto DebitCard::do_card_number() const noexcept -> const text_type&
{
    return _info.get_number();
}

inline auto DebitCard::do_card_pincode() const noexcept -> const text_type&
{
    return _info.get_pin();
}

inline auto DebitCard::do_card_balance() const noexcept -> balance_type
{
    return _info.get_balance();
}

inline auto DebitCard::do_set_balance(const balance_type nval) -> void
{
    if(nval < 0)
        throw NotEnoughMoneyException("Not enough money on balance to perform an operation.");
    _info.set_balance(nval);
}

inline const ProductKeyInfo<IProduct> &DebitCard::do_key_info() const noexcept
{
    return _info.get_key();
}

inline const LoginParams<IProduct> &DebitCard::do_login_info() const noexcept
{
    return _info.get_login_info();
}

inline const ProductCommonInfo<IProduct> &DebitCard::do_common_info() const noexcept
{
    return _info;
}

inline auto DebitCard::check_input() const noexcept -> bool
{
    //TODO text input checking
    return card_balance() >= 0;
}

inline auto DebitCard::do_owner_firstname() const noexcept -> const text_type&
{
    return _info.get_owner_firstname();
}
inline auto DebitCard::do_owner_lastname() const noexcept -> const text_type&
{
    return _info.get_owner_lastname();
}

inline void DebitCard::do_set_pin(const text_type & new_pin)
{
    _info.set_pin(new_pin);
}


#endif // DEBITCARD_H
