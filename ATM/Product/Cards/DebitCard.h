#ifndef DEBITCARD_H
#define DEBITCARD_H
#include "icard.h"
#include "Exceptions\inputexception.h"

class DebitCard : public ICard
{
public:
    DebitCard(const info_type&);
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

inline DebitCard::DebitCard(const info_type& info) :
    _info(info)
{
    if (!check_input())
    {
        throw InputException("Incorrect card input.");
    }
}

inline auto DebitCard::do_card_number() const noexcept -> const text_type&
{
    return _info.Number;
}

inline auto DebitCard::do_card_pincode() const noexcept -> const text_type&
{
    return _info.Pin;
}

inline auto DebitCard::do_card_balance() const noexcept -> balance_type
{
    return _info.Balance;
}

inline auto DebitCard::do_set_balance(const balance_type nval) -> void
{
    _info.Balance = nval;
}

inline auto DebitCard::check_input() const noexcept -> bool
{
    //TODO text input checking
    return card_balance() >= 0;
}



#endif // DEBITCARD_H
