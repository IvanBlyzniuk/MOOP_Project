#include "standardmanager.h"

StandardManager::StandardManager(const common_info_type& info) noexcept :
    _info(info)
{
}

void StandardManager::do_add_card(card_ptr card, card_reg_ptr reg) const
{
    reg->make_registration(card);
}

void StandardManager::do_rem_card(const card_key_type& key, card_reg_ptr reg) const
{
    reg->remove_registration(key);
}

