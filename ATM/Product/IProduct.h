#ifndef IPRODUCT_H
#define IPRODUCT_H

//template<typename T>
//concept c_product = requires(T prod)
//{
//  {prod.key_info()} ->
//};
template<typename AbstractProduct>
class ProductCommonInfo;

template<typename AbstractProduct>
class ProductKeyInfo;

template<typename AbstractProduct>
class LoginParams;

class IProduct
{
public:
    virtual ~IProduct() = default;
public:
    const ProductKeyInfo<IProduct>&    key_info()    const noexcept;
    const LoginParams<IProduct>&       login_info()  const noexcept;
    const ProductCommonInfo<IProduct>& common_info() const noexcept;
private:
    virtual const ProductKeyInfo<IProduct>&    do_key_info()    const noexcept = 0;
    virtual const LoginParams<IProduct>&       do_login_info()  const noexcept = 0;
    virtual const ProductCommonInfo<IProduct>& do_common_info() const noexcept = 0;
};

inline const ProductCommonInfo<IProduct>& IProduct::common_info() const noexcept
{
    return do_common_info();
}

inline const ProductKeyInfo<IProduct>& IProduct::key_info() const noexcept
{
    return do_key_info();
}

inline const LoginParams<IProduct>& IProduct::login_info() const noexcept
{
    return do_login_info();
}

//#include "ProductInfo.h"
#endif // IPRODUCT_H
