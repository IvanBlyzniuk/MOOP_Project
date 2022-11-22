#ifndef IMANAGER_H
#define IMANAGER_H
#include <QString>
#include <memory>
#include "Product\Cards\icard.h"

class AManager
{
public:
    using text_type = QString;
    using card_ptr = std::shared_ptr<ICard>;
public:
    AManager(const text_type&, const text_type&);
    virtual ~AManager() = default;
public:
    const text_type& login() const noexcept;
    const text_type& password() const noexcept;
    void set_login(const text_type&);
    void set_password(const text_type&);
    void add_card(card_ptr) const;
    void rem_card(card_ptr) const;
private:
    bool check_input() const noexcept;
private:
    virtual void do_add_card(card_ptr) const = 0;
    virtual void do_rem_card(card_ptr) const = 0;
private:
    text_type _login;
    text_type _password;
};

inline void AManager::add_card(card_ptr card) const
{
    do_add_card(card);
}

inline void AManager::rem_card(card_ptr card) const
{
    do_rem_card(card);
}

#endif // IMANAGER_H
