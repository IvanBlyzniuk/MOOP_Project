 #ifndef IMANAGER_H
#define IMANAGER_H
#include <QString>
#include <memory>
#include "Product\Cards\icard.h"
#include "Product/ProductInfo.h"
#include "Exceptions/inputexception.h"

class AManager;

template<>
class ProductKeyInfo<AManager>
{
public:
    using key_type = ProductKeyInfo<AManager>;
    using login_info_type = LoginParams<AManager>;
    using text_type = QString;
public:
    ProductKeyInfo(const text_type& login) noexcept :
        _login(login)
    {}
public:
    const text_type& get_login() const noexcept { return _login; }
private:
    const text_type _login;
};

template<>
class LoginParams<AManager>
{
public:
    using key_type = ProductKeyInfo<AManager>;
    using login_info_type = LoginParams<AManager>;
    using text_type = ProductKeyInfo<AManager>::text_type;
public:
    LoginParams(const text_type& login, const text_type& password) noexcept :
        _key(login),
        _password(password)
    {}
public:
    const key_type& get_key() const noexcept { return _key; }
    const text_type& get_login() const noexcept { return get_key().get_login(); }
    const text_type& get_password() const noexcept { return _password; }
private:
    key_type _key;
    const text_type _password;
};

template<>
class ProductCommonInfo <AManager>
{
public:
    using key_type = ProductKeyInfo<AManager>;
    using login_info_type = LoginParams<AManager>;
    using text_type = QString;
public:
    const login_info_type& get_login_info() const noexcept { return _login_info; }
    const key_type& get_key() const noexcept { return get_login_info().get_key(); }
    const text_type& get_login() const noexcept { return get_login_info().get_login(); }
    const text_type& get_password() const noexcept { return get_login_info().get_password(); }
private:
    LoginParams<AManager> _login_info;
};

class AManager
{
public:
    using info_type = ProductCommonInfo<AManager>;
    using text_type = info_type::text_type;
    using card_ptr  = std::shared_ptr<ICard>;
public:
    virtual ~AManager() = default;
public:
    const text_type& login() const noexcept;
    const text_type& password() const noexcept;
    void set_login(const text_type&);
    void set_password(const text_type&);
    void add_card(card_ptr) const;
    void rem_card(card_ptr) const;
private:
    virtual const text_type& do_login() const noexcept = 0;
    virtual const text_type& do_password() const noexcept = 0;
    virtual void do_set_login(const text_type&) = 0;
    virtual void do_set_password(const text_type&) = 0;
    virtual void do_add_card(card_ptr) const = 0;
    virtual void do_rem_card(card_ptr) const = 0;
};

inline auto AManager::login() const noexcept -> const text_type&
{
    return do_login();
}

inline auto AManager::password() const noexcept -> const text_type&
{
    return do_password();
}

inline auto AManager::set_login(const text_type& nval) -> void
{
    do_set_login(nval);
}

inline auto AManager::set_password(const text_type& nval) -> void
{
    do_set_password(nval);
}

inline void AManager::add_card(card_ptr card) const
{
    do_add_card(card);
}

inline void AManager::rem_card(card_ptr card) const
{
    do_rem_card(card);
}

#endif // IMANAGER_H
