#ifndef ISERIALIZER_H
#define ISERIALIZER_H
#include <memory>
#include "Product/IProduct.h"
#include "Product/ProductInfo.h"

class ISerializer
{
public:
    using in_product_ptr = std::shared_ptr<IProduct>;
    using out_product_ptr = std::unique_ptr<IProduct>;
    using common_info_type = CommonInfoBase;
    using login_info_type = LoginInfoBase;
    using key_info_type = KeyInfoBase;
public:
    void serialize(in_product_ptr) const;
    bool exists(const key_info_type&) const noexcept;
    void remove(const key_info_type&) const;
    out_product_ptr deserialize(const login_info_type&) const;
private:
    virtual void do_serialize(in_product_ptr) const = 0;
    virtual bool do_exists(const key_info_type&) const noexcept = 0;
    virtual void do_remove(const key_info_type&) const = 0;
    virtual out_product_ptr do_deserialize(const login_info_type&) const = 0;
};

inline void ISerializer::serialize(in_product_ptr ptr) const
{
    do_serialize(ptr);
}

inline bool ISerializer::exists(const key_info_type& key) const noexcept
{
    return do_exists(key);
}

inline void ISerializer::remove(const key_info_type& key) const
{
    do_remove(key);
}

inline auto ISerializer::deserialize(const login_info_type& info) const -> out_product_ptr
{
    return do_deserialize(info);
}


#endif // ISERIALIZER_H
