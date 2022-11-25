#include "cardregistrator.h"

template<typename CardType>
CardRegistrator<CardType>::CardRegistrator(factory_ptr factory, serializer_ptr db) noexcept :
    ARegistrator(factory),
    _db(db)
{

}

template<typename CardType>
auto CardRegistrator<CardType>::do_make_registration(const product_info& info) const -> void
{
    if(can_be_registered())
    {

        //_db->serialize()
    }
    //else throw
}

template<typename CardType>
auto CardRegistrator<CardType>::do_can_be_registered(const product_info& info) const noexcept -> bool
{
    return !_db->exists(info);
}
