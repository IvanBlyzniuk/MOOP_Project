#ifndef IFACTORY_H
#define IFACTORY_H
#include <memory>
#include <type_traits>
#include "Product/ProductInfo.h"

template<typename AbstractProduct>
class IFactory
{
public:
    using product_abstract_type = AbstractProduct;
    using product_ptr = std::unique_ptr<product_abstract_type>;
    using product_info = ProductCommonInfo<product_abstract_type>;
public:
    virtual product_ptr create_product(const product_info&) const = 0;
};

#endif // IFACTORY_H
