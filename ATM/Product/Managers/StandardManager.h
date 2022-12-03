#ifndef STANDARDMANAGER_H
#define STANDARDMANAGER_H

#include "amanager.h"

class StandardManager : public AManager
{
public:
    explicit StandardManager(const common_info_type&) noexcept;
private:
    virtual const text_type& do_login() const noexcept override;
    virtual const text_type& do_password() const noexcept override;
    virtual void do_set_login(const text_type&) override;
    virtual void do_set_password(const text_type&) override;
    virtual void do_add_card(card_ptr, card_reg_ptr) const override;
    virtual void do_rem_card(const card_key_type&, card_reg_ptr) const override;
    const KeyInfoBase&    do_key_info()        const noexcept override;
    const LoginInfoBase&  do_login_info()      const noexcept override;
    const CommonInfoBase& do_common_info()     const noexcept override;
private:
    common_info_type _info;
};

inline auto StandardManager::do_login() const noexcept -> const text_type&
{
    return _info.get_login();
}

inline auto StandardManager::do_password() const noexcept -> const text_type&
{
    return _info.get_password();
}

inline auto StandardManager::do_set_login(const text_type& login) -> void
{
    _info.set_login(login);
}

inline auto StandardManager::do_set_password(const text_type& password) -> void
{
    _info.set_password(password);
}

inline const ProductKeyInfo<IProduct> &StandardManager::do_key_info() const noexcept
{
    return _info.get_key();
}

inline const LoginParams<IProduct> &StandardManager::do_login_info() const noexcept
{
    return _info.get_login_info();
}

inline const ProductCommonInfo<IProduct> &StandardManager::do_common_info() const noexcept
{
    return _info;
}
#endif // STANDARDMANAGER_H
