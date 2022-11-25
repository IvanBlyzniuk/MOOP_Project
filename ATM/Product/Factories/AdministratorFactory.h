#ifndef ADMINISTRATORFACTORY_H
#define ADMINISTRATORFACTORY_H
#include "Product/Managers/aadministrator.h"
#include "ifactory.h"

template<std::derived_from<AAdministrator> AdminType>
class AdministratorFactory : public IFactory<AAdministrator>
{
public:
    using product_type = AdminType;
public:
    product_ptr create_product(const product_info& info) const override
    {
        return std::make_unique<product_type>(info);
    }
};

#endif // ADMINISTRATORFACTORY_H
