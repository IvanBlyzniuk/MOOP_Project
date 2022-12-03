#ifndef ISERIALIZER_H
#define ISERIALIZER_H
#include "Product/Cards/DebitCard.h"
#include "Product/Cards/creditcard.h"
#include "Product/Managers/amanager.h"
#include <memory>

class AAdministrator;

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
    void serialize(in_product_ptr<ICard>)    const;
    void serialize(in_product_ptr<AManager>)     const;
    bool exists_card(const ProductKeyInfo<ICard>&)    const noexcept;
    bool exists_manager(const ProductKeyInfo<AManager>&) const noexcept;
    void remove_card(const ProductKeyInfo<ICard>&) const;
    void remove_manager(const ProductKeyInfo<AManager>&) const;
    out_product_ptr<ICard> deserialize(const LoginParams<ICard>&)       const;
    out_product_ptr<AManager> deserialize(const LoginParams<AManager>&) const;
    void changeBalance(const ProductKeyInfo<ICard>&, const ICard::balance_type) const;
private:
    void do_serialize(const ICard&) const;
    virtual void do_serialize(const DebitCard&)                                      const = 0;
    virtual void do_serialize(const CreditCard&)                                     const = 0;
    virtual void do_serialize(const AManager&)                                       const = 0;
    virtual void do_serialize(const AAdministrator&)                                 const = 0;
    virtual bool do_exists(const ProductKeyInfo<ICard>&)                             const noexcept = 0;
    virtual bool do_exists(const ProductKeyInfo<AManager>&)                          const noexcept = 0;
    virtual void do_removeCard(const ProductKeyInfo<ICard>&)                         const = 0;
    virtual void do_removeManager(const ProductKeyInfo<AManager>&)                   const = 0;
    virtual out_product_ptr<ICard> do_deserialize(const LoginParams<ICard>&)         const = 0;
    virtual out_product_ptr<AManager> do_deserialize(const LoginParams<AManager>&)   const = 0;
    virtual void do_changeBalance(const ProductKeyInfo<ICard>&, ICard::balance_type) const = 0;
};

inline auto ISerializer::serialize(in_product_ptr<ICard> ptr) const -> void
{
    do_serialize(*ptr);
}

inline auto ISerializer::serialize(in_product_ptr<AManager> ptr) const -> void
{
    do_serialize(*ptr);
}

inline auto ISerializer::exists_card(const ProductKeyInfo<ICard>& info) const noexcept -> bool
{
    return do_exists(info);
}

inline auto ISerializer::exists_manager(const ProductKeyInfo<AManager>& info) const noexcept -> bool
{
    return do_exists(info);
}

inline auto ISerializer::deserialize(const LoginParams<ICard>& ps) const -> out_product_ptr<ICard>
{
    return do_deserialize(ps);
}

inline auto ISerializer::deserialize(const LoginParams<AManager>& ps) const -> out_product_ptr<AManager>
{
    return do_deserialize(ps);
}

inline void ISerializer::changeBalance(const ProductKeyInfo<ICard>& key, ICard::balance_type bal) const
{
    do_changeBalance(key, bal);
}

inline void ISerializer::do_serialize(const ICard &) const
{
    throw InputException("Unknown Card");
}

#endif // ISERIALIZER_H
