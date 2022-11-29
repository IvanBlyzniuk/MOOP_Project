#ifndef REGISTRATORTYPEDEFS_H
#define REGISTRATORTYPEDEFS_H
#include "aregistrator.h"
#include "Product/Cards/icard.h"
#include "Product/Managers/amanager.h"
#include "Product/Managers/aadministrator.h"
#include "Product/Cards/DebitCard.h"
#include "Product/Cards/creditcard.h"

using ICardRegistrator = ARegistrator<ICard>;
using IManagerRegistrator = ARegistrator<AManager>;
using IAdministratorRegistrator = ARegistrator<AManager>;

#endif // REGISTRATORTYPEDEFS_H
