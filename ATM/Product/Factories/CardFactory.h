#ifndef CARDFACTORY_H
#define CARDFACTORY_H
#include "Product/Cards/icard.h"
#include "Product/Cards/creditcard.h"
#include "Product/Cards/DebitCard.h"
#include "ifactory.h"

using ICardFactory = IFactory<ICard>;

template<typename CardType>
class CardFactory : public ICardFactory
{
public:
    using product_type = CardType;
public:
    product_ptr create_product(const product_info& info) const override
    {
        return std::make_unique<product_type>(info);
    }
};

using CreditCardFactory = CardFactory<CreditCard>;
using DebitCardFactory = CardFactory<DebitCard>;

#endif // CARDFACTORY_H
