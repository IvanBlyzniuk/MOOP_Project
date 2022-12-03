#ifndef AADMINISTRATOR_H
#define AADMINISTRATOR_H
#include "amanager.h"

class AAdministrator : public AManager
{
public:
    using manager_ptr = std::shared_ptr<AManager>;
    using manager_reg_ptr = std::shared_ptr<ARegistrator<AManager>>;
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
