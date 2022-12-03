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
class ProductCommonInfo<IProduct>{};

template<>
class ProductKeyInfo<IProduct>{};

template<>
class LoginParams<IProduct>{};

using CommonInfoBase = ProductCommonInfo<IProduct>;
using KeyInfoBase = ProductKeyInfo<IProduct>;
using LoginInfoBase = LoginParams<IProduct>;

#endif // PRODUCTINFO_H
