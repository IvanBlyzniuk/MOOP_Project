#ifndef CREDITCARD_H
#define CREDITCARD_H
#include "Product/Cards/icard.h"
#include "Exceptions/inputexception.h"

class CreditCard : public ICard
{
public:
    CreditCard(const info_type&, const balance_type = s_dflt_credit_limit);
    ~CreditCard() override = default;
public:
    balance_type credit_limit() const;
private:
    const text_type& do_card_number()          const noexcept override;
    const text_type& do_card_pincode()         const noexcept override;
    balance_type     do_card_balance()         const noexcept override;
    void             do_set_balance(const balance_type)       override;
private:
    bool check_input() const noexcept;
private:
    info_type _info;
    balance_type _credit_limit;
private:
    static const balance_type s_dflt_credit_limit;
};

const CreditCard::balance_type CreditCard::s_dflt_credit_limit = 0;

inline CreditCard::CreditCard
(
    const info_type& info,
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

inline auto CreditCard::credit_limit() const -> balance_type
{
    return _credit_limit;
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
