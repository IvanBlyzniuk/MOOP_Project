#ifndef IREGISTRATOR_H
#define IREGISTRATOR_H
#include "Product/Factories/ifactory.h"
#include "Product/ProductInfo.h"

template<typename AbstractProduct>
class ARegistrator
{
public:
    using product_abstract_type = AbstractProduct;
    using product_info = ProductCommonInfo<product_abstract_type>;
protected:
    template<typename Factory>
    using ptr = std::shared_ptr<Factory>;
    using factory_ptr= ptr<IFactory<product_abstract_type>>;
public:
    ARegistrator(factory_ptr) noexcept;
    virtual ~ARegistrator() = default;
public:
    void make_registration(const product_info&) const;
    bool can_be_registered(const product_info&) const noexcept;
private:
    virtual void do_make_registration(const product_info&) const          = 0;
    virtual bool do_can_be_registered(const product_info&) const noexcept = 0;
private:
    factory_ptr _factory;
};

template<typename AbstractProduct>
inline ARegistrator<AbstractProduct>::ARegistrator(factory_ptr factory) noexcept :
    _factory(factory)
{
}

template<typename AbstractProduct>
inline auto ARegistrator<AbstractProduct>::make_registration(const product_info& info) const -> void
{
    return do_make_registration(info);
}

template<typename AbstractProduct>
inline auto ARegistrator<AbstractProduct>::can_be_registered(const product_info& info) const noexcept -> bool
{
    return do_can_be_registered(info);
}

#endif // IREGISTRATOR_H
