#ifndef ISERIALIZER_H
#define ISERIALIZER_H
#include "Product/Cards/DebitCard.h"
#include "Product/Cards/creditcard.h"
#include "Product/Managers/amanager.h"
#include "Product/ProductInfo.h"
#include <memory>

class ISerializer
{
public:
    template<typename ProductType>
    using in_product_ptr = std::shared_ptr<ProductType>;
    template<typename ProductType>
    using out_product_ptr = std::unique_ptr<ProductType>;
    template<typename ProductType>
    using product_info = ProductCommonInfo<ProductType>;
public:
    void serialize(in_product_ptr<DebitCard>)     const;
    void serialize(in_product_ptr<CreditCard>)      const;
    void serialize(in_product_ptr<AManager>)       const;
    bool exists(const product_info<ICard>&)        const noexcept;
    bool exists(const product_info<AManager>&)     const noexcept;
    out_product_ptr<ICard> deserializeCard()       const;
    out_product_ptr<AManager> deserializeManager() const;
private:
    virtual void do_serialize(in_product_ptr<DebitCard>)            const = 0;
    virtual void do_serialize(in_product_ptr<CreditCard>)             const = 0;
    virtual void do_serialize(in_product_ptr<AManager>)              const = 0;
    virtual bool do_exists(const product_info<ICard>&)      const noexcept = 0;
    virtual bool do_exists(const product_info<AManager>&)   const noexcept = 0;
    virtual out_product_ptr<ICard> do_deserialize_card()             const = 0;
    virtual out_product_ptr<AManager> do_deserialize_manager()       const = 0;
};

inline auto ISerializer::serialize(in_product_ptr<DebitCard> ptr) const -> void
{
    do_serialize(ptr);
}

inline auto ISerializer::serialize(in_product_ptr<CreditCard> ptr) const -> void
{
    do_serialize(ptr);
}

inline auto ISerializer::serialize(in_product_ptr<AManager> ptr) const -> void
{
    do_serialize(ptr);
}

inline auto ISerializer::exists(const product_info<ICard>& info) const noexcept -> bool
{
    return do_exists(info);
}

inline auto ISerializer::exists(const product_info<AManager>& info) const noexcept -> bool
{
    return do_exists(info);
}

inline auto ISerializer::deserializeCard() const -> out_product_ptr<ICard>
{
    return do_deserialize_card();
}

inline auto ISerializer::deserializeManager() const -> out_product_ptr<AManager>
{
    return do_deserialize_manager();
}

#endif // ISERIALIZER_H
