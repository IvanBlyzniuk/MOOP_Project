#ifndef MANAGERFACTORY_H
#define MANAGERFACTORY_H
#include "Product/Managers/amanager.h"
#include "ifactory.h"

using IManagerFactory = IFactory<AManager>;

template<typename ManagerType>
class ManagerFactory : public IManagerFactory
{
public:
    using product_type = ManagerType;
public:
    product_ptr create_product(const product_info& info) const override
    {
        return std::make_unique<product_type>(info);
    }
};

#endif // MANAGERFACTORY_H
