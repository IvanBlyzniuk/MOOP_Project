#ifndef PRIVILEGEDMANAGER_H
#define PRIVILEGEDMANAGER_H

#include "aadministrator.h"

class PrivilegedManager : public AAdministrator
{
public:
    PrivilegedManager(const common_info_type&) noexcept;
private:
    const text_type& do_login() const noexcept override;
    const text_type& do_password() const noexcept override;
    void do_set_login(const text_type&) override;
    void do_set_password(const text_type&) override;
    void do_add_card(card_ptr, card_reg_ptr) const override;
    void do_rem_card(const card_key_type&, card_reg_ptr) const override;
    void do_add_manager(manager_ptr, manager_reg_ptr) const override;
    void do_rem_manager(const key_type&, manager_reg_ptr) const override;
    const KeyInfoBase&    do_key_info()        const noexcept override;
    const LoginInfoBase&  do_login_info()      const noexcept override;
    const CommonInfoBase& do_common_info()     const noexcept override;
private:
    common_info_type _info;
};

inline auto PrivilegedManager::do_login() const noexcept -> const text_type&
{
    return _info.get_login();
}

inline auto PrivilegedManager::do_password() const noexcept -> const text_type&
{
    return _info.get_password();
}

inline void PrivilegedManager::do_set_login(const text_type& login)
{
    _info.set_login(login);
}

inline void PrivilegedManager::do_set_password(const text_type& password)
{
    _info.set_password(password);
}

inline const ProductKeyInfo<IProduct> &PrivilegedManager::do_key_info() const noexcept
{
    return _info.get_key();
}

inline const LoginParams<IProduct> &PrivilegedManager::do_login_info() const noexcept
{
    return _info.get_login_info();
}

inline const ProductCommonInfo<IProduct> &PrivilegedManager::do_common_info() const noexcept
{
    return _info;
}

#endif // PRIVILEGEDMANAGER_H
