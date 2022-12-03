#include "privilegedmanager.h"

PrivilegedManager::PrivilegedManager(const common_info_type& info) noexcept :
    _info(info)
{
}

void PrivilegedManager::do_add_card(card_ptr card, card_reg_ptr reg) const
{
    reg->make_registration(*card);
}

void PrivilegedManager::do_rem_card(const card_key_type& key, card_reg_ptr reg) const
{
    reg->remove_registration(key);
}

void PrivilegedManager::do_add_manager(manager_ptr manager, manager_reg_ptr reg) const
{
    reg->make_registration(*manager);
}

void PrivilegedManager::do_rem_manager(const key_type& key, manager_reg_ptr reg) const
{
    reg->remove_registration(key);
}
