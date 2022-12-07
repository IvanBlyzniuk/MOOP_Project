#ifndef AADMINISTRATOR_H
#define AADMINISTRATOR_H
#include "amanager.h"

class AAdministrator;

template<>
class ProductKeyInfo<AAdministrator> : public ProductKeyInfo<AManager>
{
public:
    ProductKeyInfo(const text_type& login) noexcept :
        ProductKeyInfo<AManager>(login)
    {}
};

template<>
class LoginParams<AAdministrator> : public LoginParams<AManager>
{
public:
    LoginParams(const text_type& login, const text_type& password) noexcept :
        LoginParams<AManager>(login, password)
    {}
};

template<>
class ProductCommonInfo <AAdministrator> : public ProductCommonInfo <AManager>
{
public:
    ProductCommonInfo(const text_type& login, const text_type& password) noexcept :
        ProductCommonInfo<AManager>(login, password)
    {}
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
