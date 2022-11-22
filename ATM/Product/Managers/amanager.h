#ifndef IMANAGER_H
#define IMANAGER_H
#include <QString>
#include <memory>
#include "Product\Cards\icard.h"
#include "Product/ProductInfo.h"

class AManager;

template<>
class ProductCommonInfo <AManager>
{
public:
    using text_type = QString;
    using card_ptr = std::shared_ptr<ICard>;
public:
    text_type Login;
    text_type Password;
};

class AManager
{
public:
    using info_type = ProductCommonInfo<AManager>;
    using text_type = info_type::text_type;
    using card_ptr  = info_type::card_ptr;
public:
    AManager(const info_type&);
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
    info_type _info;
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
