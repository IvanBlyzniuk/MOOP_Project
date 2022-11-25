#ifndef CARDFACTORY_H
#define CARDFACTORY_H
#include "Product/Cards/icard.h"
#include "ifactory.h"

template<typename CardType>
class CardFactory : public IFactory<ICard>
{
public:
    using product_type = CardType;
public:
    product_ptr create_product(const product_info& info) const override
    {
        return std::make_unique<product_type>(info);
    }
};

#endif // CARDFACTORY_H
