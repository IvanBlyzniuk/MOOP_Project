#ifndef DEBITCARD_H
#define DEBITCARD_H
#include "icard.h"
#include "Exceptions\inputexception.h"

class DebitCard : public ICard
{
public:
    DebitCard
    (
        const text_type&,
        const text_type&,
        const text_type&,
        const text_type&,
        const balance_type,
        const balance_type
    );
    ~DebitCard() override = default;
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
    const text_type    _number;
    const text_type    _pin;
    const text_type    _owner_firstname;
    const text_type    _owner_lastname;
    balance_type _balance;
    balance_type _credit_limit;
};

inline DebitCard::DebitCard
(
    const text_type& number,
    const text_type& pin,
    const text_type& owner_firstname,
    const text_type& owner_lastname,
    const balance_type balance,
    const balance_type credit_limit
) :
    _number(number),
    _pin(pin),
    _owner_firstname(owner_firstname),
    _owner_lastname(owner_lastname),
    _balance(balance),
    _credit_limit(credit_limit)
{
    if(!check_input())
    {
        throw InputException("Incorrect card input.");
    }
}

inline auto DebitCard::credit_limit() const -> balance_type
{
    return _credit_limit;
}

inline auto DebitCard::do_card_number() const noexcept -> const text_type&
{
    return _number;
}

inline auto DebitCard::do_card_pincode() const noexcept -> const text_type&
{
    return _pin;
}

inline auto DebitCard::do_card_balance() const noexcept -> balance_type
{
    return _balance;
}

inline auto DebitCard::do_set_balance(const balance_type nval) -> void
{
    _balance = nval;
}

inline auto DebitCard::check_input() const noexcept -> bool
{
    //TODO text input checking
    return card_balance() >= 0;
}

#endif // DEBITCARD_H
