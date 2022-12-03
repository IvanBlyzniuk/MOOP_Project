#ifndef DB_H
#define DB_H
#include <QtSql>
#include "Product/Cards/icard.h"
#include "Product/Cards/creditcard.h"
#include "Product/Cards/DebitCard.h"
#include "Product/Managers/amanager.h"
#include "Product/Managers/aadministrator.h"
#include "Product/Factories/CardFactory.h"
#include "Product/Factories/ManagerFactory.h"
#include "Product/Factories/AdministratorFactory.h"
#include "Product/Managers/StandardManager.h"
#include "Product/Managers/privilegedmanager.h"
#include <memory>

class DB
{
public:
    DB();
    ~DB();
private:
    QSqlDatabase sdb;

    void serialize(const DebitCard&) const;
    void serialize(const CreditCard&) const;
    void serialize(const AManager&) const;
    void serialize(const AAdministrator&) const;

    bool existstCard(const QString&) const;
    bool existstManager(const QString&) const;

    void removeCard(const QString&) const;
    void removeManager(const QString&) const;

    std::unique_ptr<ICard> deserializeCard(const QString& number,const QString& pin) const;
    std::unique_ptr<AManager> deserializeManager(const QString& login,const QString& password) const;

    void changeBalance(const QString&,float) const;
};

#endif // DB_H
