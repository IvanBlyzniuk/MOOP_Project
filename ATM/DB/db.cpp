#include "db.h"
#include "Exceptions/AlreadyExistsException.h"
#include "Exceptions/DoesntExistException.h"
#include "Product/Cards/icard.h"
#include "Product/Cards/creditcard.h"
#include "Product/Cards/DebitCard.h"
#include "Product/Managers/amanager.h"
#include "Product/Managers/aadministrator.h"
#include "Product/Factories/CardFactory.h"
#include "Product/Factories/ManagerFactory.h"
#include "Product/Factories/AdministratorFactory.h"
#include "Product/Managers/standardmanager.h"
#include "Product/Managers/privilegedmanager.h"

DB::DB() :
    sdb(QSqlDatabase::addDatabase("QSQLITE"))
{
    //sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("data.sqlite");
    sdb.open();
    QSqlQuery query;
    query.exec("create table if not exists 'debit_cards' ('number' text PRIMARY KEY,'pin' text, 'balance' float, 'firstname' text, 'lastname' text)");
    query.exec("create table if not exists 'credit_cards' ('number' text PRIMARY KEY,'pin' text, 'balance' float, 'firstname' text, 'lastname' text, 'credit_limit' float)");
    query.exec("create table if not exists 'managers' ('login' text PRIMARY KEY, 'password' text)");
    query.exec("create table if not exists 'privileged_managers' ('login' text PRIMARY KEY, 'password' text)");
}

DB::~DB()
{
    sdb.close();
}

void DB::do_serialize(const DebitCard& card) const
{
    QSqlQuery query;
    query.prepare("SELECT * FROM debit_cards WHERE number=(:number)");
    query.bindValue(":number",card.card_number());
    if(!query.first())
    {
        query.prepare("INSERT INTO debit_cards VALUES (:number,:pin,:balance,:firstname,:lastname)");
        query.bindValue(":number",card.card_number());
        query.bindValue(":pin",card.card_pincode());
        query.bindValue(":balance",card.card_balance());
        query.bindValue(":firstname",card.owner_firstname());
        query.bindValue(":lastname",card.owner_lastname());
        query.exec();
    }
    else
    {
        query.prepare("UPDATE debit_cards SET number=:number,pin=:pin,balance=:balance,firstname=:firstname,lastname=:lastname) WHERE number=(:number)");
        query.bindValue(":number",card.card_number());
        query.bindValue(":pin",card.card_pincode());
        query.bindValue(":balance",card.card_balance());
        query.bindValue(":firstname",card.owner_firstname());
        query.bindValue(":lastname",card.owner_lastname());
        query.exec();
    }
}
void DB::do_serialize(const CreditCard& card) const
{
    QSqlQuery query;
    query.prepare("SELECT * FROM credit_cards WHERE number=(:number)");
    query.bindValue(":number",card.card_number());
    query.exec();
    if(!query.first())
    {
        query.prepare("INSERT INTO credit_cards VALUES (:number,:pin,:balance,:firstname,:lastname,:credit_limit)");
        query.bindValue(":number",card.card_number());
        query.bindValue(":pin",card.card_pincode());
        query.bindValue(":balance",card.card_balance());
        query.bindValue(":firstname",card.owner_firstname());
        query.bindValue(":lastname",card.owner_lastname());
        query.bindValue(":credit_limit",card.credit_limit());
        query.exec();
    }
    else
    {
        query.prepare("UPDATE credit_cards SET number=:number,pin=:pin,balance=:balance,firstname=:firstname,lastname=:lastname,credit_limit=:credit_limit) WHERE number=(:number)");
        query.bindValue(":number",card.card_number());
        query.bindValue(":pin",card.card_pincode());
        query.bindValue(":balance",card.card_balance());
        query.bindValue(":firstname",card.owner_firstname());
        query.bindValue(":lastname",card.owner_lastname());
        query.bindValue(":credit_limit",card.credit_limit());
        query.exec();
    }
}
void DB::do_serialize(const AManager& manager) const
{
    QSqlQuery query;
    query.prepare("SELECT * FROM managers WHERE login=(:login)");
    query.bindValue(":login",manager.login());
    query.exec();
    if(!query.first())
    {
        query.prepare("INSERT INTO managers VALUES (:login,:password)");
        query.bindValue(":login",manager.login());
        query.bindValue(":password",manager.password());
        query.exec();
    }
    else
    {
        throw AlreadyExistsException("Specified manager already exists");
    }
}
void DB::do_serialize(const AAdministrator& admin) const
{
    QSqlQuery query;
    query.prepare("SELECT * FROM privileged_managers WHERE login=(:login)");
    query.bindValue(":login",admin.login());
    query.exec();
    if(!query.first())
    {
        query.prepare("INSERT INTO privileged_managers VALUES (:login,:password)");
        query.bindValue(":login",admin.login());
        query.bindValue(":password",admin.password());
        query.exec();
    }
    else
    {
        throw AlreadyExistsException("Specified manager already exists");
    }
}
bool DB::do_exists(const ProductKeyInfo<ICard>& key) const noexcept
{
    const QString& number = key.get_number();
    QSqlQuery query;
    query.prepare("SELECT * FROM credit_cards WHERE number=(:number)");
    query.bindValue(":number",number);
    query.exec();
    if(query.first())
        return true;
    query.prepare("SELECT * FROM debit_cards WHERE number=(:number)");
    query.bindValue(":number",number);
    query.exec();
    if(query.first())
        return true;
    return false;
}
bool DB::do_exists(const ProductKeyInfo<AManager>& key) const noexcept
{
    const QString& login = key.get_login();
    QSqlQuery query;
    query.prepare("SELECT * FROM managers WHERE login=(:login)");
    query.bindValue(":login",login);
    query.exec();
    if(query.first())
        return true;
    query.prepare("SELECT * FROM privileged_managers WHERE login=(:login)");
    query.bindValue(":login",login);
    query.exec();
    if(query.first())
        return true;
    return false;
}
void DB::do_removeCard(const ProductKeyInfo<ICard>& key) const
{
    const QString& number = key.get_number();
    if (!exists_card(number))
        throw DoesntExistException("Specified card doesn't exist");
    QSqlQuery query;
    query.prepare("DELETE FROM debit_cards WHERE number=(:number)");
    query.bindValue(":number",number);
    query.exec();
    query.prepare("DELETE FROM credit_cards WHERE number=(:number)");
    query.bindValue(":number",number);
    query.exec();
}
void DB::do_removeManager(const ProductKeyInfo<AManager>& key) const
{
    const QString& login = key.get_login();
    if(!exists_manager(login))
        throw DoesntExistException("Specified manager doesn't exist");
    QSqlQuery query;
    query.prepare("DELETE FROM managers WHERE login=(:login)");
    query.bindValue(":login",login);
    query.exec();
    query.prepare("DELETE FROM privileged_managers WHERE login=(:login)");
    query.bindValue(":login",login);
    query.exec();
}
auto DB::do_deserialize(const LoginParams<ICard>& key) const -> out_product_ptr<ICard>
{
    const QString& number = key.get_number();
    const QString& pin = key.get_pin();
    QSqlQuery query;
    query.prepare("SELECT * FROM debit_cards WHERE number=(:number) AND pin=(:pin)");
    query.bindValue(":number",number);
    query.bindValue(":pin",pin);
    query.exec();
    if(query.first())
    {
        QSqlRecord rec = query.record();
        float balance = query.value(rec.indexOf("balance")).toFloat();
        QString first_name = query.value(rec.indexOf("firstname")).toString();
        QString last_name = query.value(rec.indexOf("lastname")).toString();
        CardFactory<DebitCard> factory;
        std::unique_ptr<ICard> uptr = factory.create_product(ProductCommonInfo<ICard>(number,pin,first_name,last_name,balance));
        return std::unique_ptr<ICard>(dynamic_cast<ICard*>(uptr.release()));
    }
    query.prepare("SELECT * FROM credit_cards WHERE number=(:number) AND pin=(:pin)");
    query.bindValue(":number",number);
    query.bindValue(":pin",pin);
    query.exec();
    if(query.first())
    {
        QSqlRecord rec = query.record();
        float balance = query.value(rec.indexOf("balance")).toFloat();
        QString first_name = query.value(rec.indexOf("firstname")).toString();
        QString last_name = query.value(rec.indexOf("lastname")).toString();
        float credit_limit = query.value(rec.indexOf("credit_limit")).toFloat();
        CardFactory<CreditCard> factory;
        std::unique_ptr<ICard> uicardPtr = factory.create_product({number,pin,first_name,last_name,balance});
        ICard * icardPtr = uicardPtr.release();
        CreditCard * cardPtr = dynamic_cast<CreditCard*>(icardPtr);
        std::unique_ptr<CreditCard> res(cardPtr);
        res->set_credit_limit(credit_limit);
        return res;
    }
    throw DoesntExistException("Specified card doesn't exist");
}
std::unique_ptr<AManager> DB::do_deserialize(const LoginParams<AManager>& key) const
{
    const QString& login = key.get_login();
    const QString& password = key.get_password();
    QSqlQuery query;
    query.prepare("SELECT * FROM managers WHERE login=(:login) AND password=(:password)");
    query.bindValue(":login",login);
    query.bindValue(":password",password);
    query.exec();
    if(query.first())
    {
        ManagerFactory<StandardManager> factory;
        return factory.create_product(ProductCommonInfo<AManager>(login,password));
    }

    query.prepare("SELECT * FROM privileged_managers WHERE login=(:login) AND password=(:password)");
    query.bindValue(":login",login);
    query.bindValue(":password",password);
    query.exec();
    if(query.first())
    {
        QSqlRecord rec = query.record();
        QString login = query.value(rec.indexOf("login")).toString();
        QString password = query.value(rec.indexOf("password")).toString();
        AdministratorFactory<PrivilegedManager> factory;
        std::unique_ptr<AAdministrator> uptr = factory.create_product(ProductCommonInfo<AAdministrator>(login,password));
        return std::unique_ptr<AManager>(dynamic_cast<AManager*>(uptr.release()));
    }
    throw DoesntExistException("Specified manager doesn't exist");
}

void DB::do_changeBalance(const ProductKeyInfo<ICard>& key, ICard::balance_type amount) const
{
    const QString& number = key.get_number();
    if(!exists_card(number))
        throw DoesntExistException("Specified card doesn't exist");
    if(amount < 0)
        throw InputException("Negative transaction sum");
    QSqlQuery query;
    query.prepare("UPDATE debit_cards SET balance = balance + (:amount) WHERE number = (:number)");
    query.bindValue(":amount",amount);
    query.bindValue(":number",number);
    query.exec();
    query.prepare("UPDATE credit_cards SET balance = balance + (:amount) WHERE number = (:number)");
    query.bindValue(":amount",amount);
    query.bindValue(":number",number);
    query.exec();
}
