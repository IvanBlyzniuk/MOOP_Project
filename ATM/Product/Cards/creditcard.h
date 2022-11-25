#ifndef CREDITCARD_H
#define CREDITCARD_H
#include "Product/Cards/icard.h"
#include "Exceptions/inputexception.h"

class CreditCard : public ICard
{
public:
    CreditCard(const info_type&);
private:
    const text_type& do_card_number()          const noexcept override;
    const text_type& do_card_pincode()         const noexcept override;
    balance_type     do_card_balance()         const noexcept override;
    void             do_set_balance(const balance_type)       override;
private:
    bool check_input() const noexcept;
private:
    info_type _info;
};

inline CreditCard::CreditCard(const info_type& info) :
    _info(info)
{
    if(!check_input())
    {
        throw InputException("Incorrect card input.");
    }
}

inline auto CreditCard::do_card_number() const noexcept -> const text_type&
{
    return _info.Number;
}

inline auto CreditCard::do_card_pincode() const noexcept -> const text_type&
{
    return _info.Pin;
}

inline auto CreditCard::do_card_balance() const noexcept -> balance_type
{
    return _info.Balance;
}

inline auto CreditCard::do_set_balance(const balance_type nval) -> void
{
    _info.Balance = nval;
}

inline auto CreditCard::check_input() const noexcept -> bool
{
    //TODO text input checking
    return card_balance() >= 0;
}

#endif // CREDITCARD_H
