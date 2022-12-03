#ifndef AADMINISTRATOR_H
#define AADMINISTRATOR_H
#include "amanager.h"

class AAdministrator;

template<>
class ProductKeyInfo<AAdministrator> : public KeyInfoBase
{
public:
    using key_type = ProductKeyInfo<AAdministrator>;
    using login_info_type = LoginParams<AAdministrator>;
    using text_type = QString;
public:
    ProductKeyInfo(const text_type& login) noexcept :
        _login(login)
    {}
public:
    const text_type& get_login() const noexcept { return _login; }
    void set_login(const text_type& login) noexcept { _login = login; }
private:
    text_type _login;
};

template<>
class LoginParams<AAdministrator> : public LoginInfoBase
{
public:
    using key_type = ProductKeyInfo<AAdministrator>;
    using login_info_type = LoginParams<AAdministrator>;
    using text_type = ProductKeyInfo<AAdministrator>::text_type;
public:
    LoginParams(const text_type& login, const text_type& password) noexcept :
        _key(login),
        _password(password)
    {}
public:
    const key_type& get_key() const noexcept { return _key; }
    const text_type& get_login() const noexcept { return get_key().get_login(); }
    const text_type& get_password() const noexcept { return _password; }
    void set_login(const text_type& l) { _key.set_login(l); }
    void set_password(const text_type& p) { _password = p; }
private:
    key_type _key;
    text_type _password;
};

template<>
class ProductCommonInfo <AAdministrator> : public CommonInfoBase
{
public:
    using key_type = ProductKeyInfo<AAdministrator>;
    using login_info_type = LoginParams<AAdministrator>;
    using text_type = QString;
public:
    ProductCommonInfo(const text_type& login, const text_type& password) noexcept :
        _login_info(login, password)
    {}
public:
    const login_info_type& get_login_info() const noexcept { return _login_info; }
    const key_type& get_key() const noexcept { return get_login_info().get_key(); }
    const text_type& get_login() const noexcept { return get_login_info().get_login(); }
    const text_type& get_password() const noexcept { return get_login_info().get_password(); }
    void set_login(const text_type& l) { _login_info.set_login(l); }
    void set_password(const text_type& p) { _login_info.set_password(p); }
private:
    LoginParams<AAdministrator> _login_info;
};

class AAdministrator : public AManager
{
public:
    using manager_ptr = std::shared_ptr<AManager>;
    using manager_reg_ptr = std::shared_ptr<ARegistrator<AManager>>;
    using common_info_type = ProductCommonInfo<AAdministrator>;
public:
    void add_manager(manager_ptr, manager_reg_ptr) const;
    void rem_manager(const key_type&, manager_reg_ptr) const;
private:
    virtual void do_add_manager(manager_ptr, manager_reg_ptr) const = 0;
    virtual void do_rem_manager(const key_type&, manager_reg_ptr) const = 0;
};

inline void AAdministrator::add_manager(manager_ptr mptr, manager_reg_ptr db) const
{
    do_add_manager(mptr, db);
}

inline void AAdministrator::rem_manager(const key_type& key, manager_reg_ptr db) const
{
    do_rem_manager(key, db);
}

#endif // AADMINISTRATOR_H
