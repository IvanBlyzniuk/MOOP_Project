#ifndef AADMINISTRATOR_H
#define AADMINISTRATOR_H
#include "amanager.h"

class AAdministrator : public AManager
{
public:
    using manager_ptr = std::shared_ptr<AManager>;
public:
    AAdministrator(const info_type&);
public:
    void add_manager(manager_ptr) const;
    void rem_manager(manager_ptr) const;
private:
    virtual void do_add_manager(manager_ptr) const = 0;
    virtual void do_rem_manager(manager_ptr) const = 0;
};

AAdministrator::AAdministrator(const info_type& info) :
    AManager(info)
{
}

inline void AAdministrator::add_manager(manager_ptr mptr) const
{
    do_add_manager(mptr);
}

inline void AAdministrator::rem_manager(manager_ptr mptr) const
{
    do_rem_manager(mptr);
}

#endif // AADMINISTRATOR_H
