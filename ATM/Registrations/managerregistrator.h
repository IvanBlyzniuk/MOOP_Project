#ifndef MANAGERREGISTRATOR_H
#define MANAGERREGISTRATOR_H

#include "DB/iserializer.h"
#include "Product/Managers/amanager.h"
#include "aregistrator.h"
#include "RegistratorTypedefs.h"
#include "Product/Managers/standardmanager.h"
#include "Product/Managers/privilegedmanager.h"

#define ManagerRegTemplate \
template<std::derived_from<IManagerRegistrator::product_abstract_type> ManagerType>

#define ManagerRegMember \
ManagerRegTemplate \
ManagerRegistrator<ManagerType> ::

#define ManagerRegMethod \
ManagerRegTemplate \
auto ManagerRegistrator<ManagerType> ::

ManagerRegTemplate
class ManagerRegistrator : public IManagerRegistrator
{
public:
    using product_type = ManagerType;
    using serializer_ptr = std::shared_ptr<ISerializer>;
public:
    ManagerRegistrator(serializer_ptr) noexcept;
private:
    void do_make_registration(product_ptr) const override;
    void do_remove_registration(const product_key_type&) const override;
    bool do_can_be_registered(const product_key_type&) const noexcept override;
private:
    serializer_ptr _db;
};

ManagerRegMember ManagerRegistrator(serializer_ptr db) noexcept :
    _db(db)
{

}

ManagerRegMethod do_make_registration(product_ptr info) const -> void
{
    _db->serialize(info);
}

ManagerRegMethod do_remove_registration(const product_key_type& info) const -> void
{
    _db->remove_manager(info);
}

ManagerRegMethod do_can_be_registered(const product_key_type& info) const noexcept -> bool
{
    return !_db->exists_manager(info);
}

using StandardManagerRegistrator = ManagerRegistrator<StandardManager>;
using PrivilegedManagerRegistrator = ManagerRegistrator<PrivilegedManager>;
#endif // MANAGERREGISTRATOR_H
