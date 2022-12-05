#ifndef PRODUCTINFO_H
#define PRODUCTINFO_H
#include "IProduct.h"

template<typename AbstractProduct>
class ProductCommonInfo;

template<typename AbstractProduct>
class ProductKeyInfo;

template<typename AbstractProduct>
class LoginParams;

template<>
class ProductCommonInfo<IProduct>
{
public:
    virtual ~ProductCommonInfo() = default;
};

template<>
class ProductKeyInfo<IProduct>
{
public:
    virtual ~ProductKeyInfo() = default;
};

template<>
class LoginParams<IProduct>
{
public:
    virtual ~LoginParams() = default;
};

using CommonInfoBase = ProductCommonInfo<IProduct>;
using KeyInfoBase = ProductKeyInfo<IProduct>;
using LoginInfoBase = LoginParams<IProduct>;

#endif // PRODUCTINFO_H
