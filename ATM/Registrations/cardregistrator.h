#ifndef CARDREGISTRATOR_H
#define CARDREGISTRATOR_H
#include "DB/iserializer.h"
#include "Product/Factories/CardFactory.h"
#include "Product/Cards/icard.h"
#include "aregistrator.h"


template<typename CardType>
class CardRegistrator : public ARegistrator<ICard>
{
public:
    using product_type = CardType;
    using factory_ptr = ptr<CardFactory<product_type>>;
    using serializer_ptr = ptr<ISerializer>;
public:
    static_assert(std::is_base_of_v<product_type, product_abstract_type>,
    "Product type must inherit from product abstract type.");
public:
    CardRegistrator(factory_ptr, serializer_ptr) noexcept;
private:
    void do_make_registration(const product_info&) const override;
    bool do_can_be_registered(const product_info&) const noexcept override;
private:
    serializer_ptr _db;
};

#endif // CARDREGISTRATOR_H
