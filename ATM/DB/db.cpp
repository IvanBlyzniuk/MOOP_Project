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
    bool exists = QFile::exists("data.sqlite");
    sdb.setDatabaseName("data.sqlite");
    sdb.open();
    QSqlQuery query;
    query.exec("create table if not exists 'debit_cards' ('number' text PRIMARY KEY,'pin' text, 'balance' float, 'firstname' text, 'lastname' text)");
    query.exec("create table if not exists 'credit_cards' ('number' text PRIMARY KEY,'pin' text, 'balance' float, 'firstname' text, 'lastname' text, 'credit_limit' float)");
    query.exec("create table if not exists 'managers' ('login' text PRIMARY KEY, 'password' text)");
    query.exec("create table if not exists 'privileged_managers' ('login' text PRIMARY KEY, 'password' text)");
    if(!exists)
    {
        query.prepare("INSERT INTO debit_cards VALUES ('1234567890123456','1234',100,'Vasiliy','Pupkin')");
        query.exec();
        query.prepare("INSERT INTO credit_cards VALUES ('1234567890123457','5678',200,'Petrik','Pyatochkin',100)");
        query.exec();
        query.prepare("INSERT INTO privileged_managers VALUES ('admin','admin')");
        query.exec();
        query.prepare("INSERT INTO managers VALUES ('login','password')");
        query.exec();
    }
}

DB::~DB()
{
    sdb.close();
}

void DB::do_serialize(in_product_ptr ptr) const
{
    const IProduct& ref = *ptr;
    try
    {
        const AAdministrator& admin = dynamic_cast<const AAdministrator&>(ref);
        serialize_aadministrator(admin);
        return;
    }
    catch(const std::bad_cast&)
    {
        try
        {
            const AManager& manager = dynamic_cast<const AManager&>(ref);
            serialize_amanager(manager);
            return;
        }
        catch (const std::bad_cast&)
        {
            try
            {
                const DebitCard& card = dynamic_cast<const DebitCard&>(ref);
                serialize_debit_card(card);
                return;
            }
            catch(const std::bad_cast&)
            {
                try
                {
                    const CreditCard& card = dynamic_cast<const CreditCard&>(ref);
                    serialize_credit_card(card);
                    return;
                }
                catch (const std::bad_cast&)
                {
                    throw InputException("Trying to serialize unknown product.");
                }
            }
        }
    }
}

bool DB::do_exists(const key_info_type& key) const noexcept
{
    using card_key_t = ICard::key_type;
    using manager_key_t = AManager::key_type;
    try
    {
        const card_key_t& card_key = dynamic_cast<const card_key_t&>(key);
        return exists_card(card_key);
    }
    catch (const std::bad_cast&)
    {
        const manager_key_t& manager_key = dynamic_cast<const manager_key_t&>(key);
        return exists_manager(manager_key);
    }
}

void DB::do_remove(const key_info_type& key) const
{
    using card_key_t = ICard::key_type;
    using manager_key_t = AManager::key_type;
    try
    {
        const card_key_t& card_key = dynamic_cast<const card_key_t&>(key);
        remove_card(card_key);
    }
    catch (const std::bad_cast&)
    {
        const manager_key_t& manager_key = dynamic_cast<const manager_key_t&>(key);
        remove_manager(manager_key);
    }
}

auto DB::do_deserialize(const login_info_type& info) const -> out_product_ptr
{
    using card_log_t = ICard::login_info_type;
    using manager_log_t = AManager::login_info_type;
    try
    {
        const card_log_t& card_key = dynamic_cast<const card_log_t&>(info);
        return deserialize_card(card_key);
    }
    catch (const std::bad_cast&)
    {
        const manager_log_t& manager_key = dynamic_cast<const manager_log_t&>(info);
        return deserialize_manager(manager_key);
    }
}

void DB::serialize_debit_card(const DebitCard& card) const
{
    //qDebug() << "Serialize debitCard";
    QSqlQuery query;
    query.prepare("SELECT * FROM debit_cards WHERE number=(:number)");
    query.bindValue(":number",card.card_number());
    query.exec();
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
        query.prepare("UPDATE debit_cards SET pin=:pin,balance=:balance,firstname=:firstname,lastname=:lastname WHERE number=(:number)");
        query.bindValue(":number",card.card_number());
        query.bindValue(":pin",card.card_pincode());
        query.bindValue(":balance",card.card_balance());
        query.bindValue(":firstname",card.owner_firstname());
        query.bindValue(":lastname",card.owner_lastname());
        query.exec();
    }
}
void DB::serialize_credit_card(const CreditCard& card) const
{
    qDebug() << "Serialize creditCard";
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
        query.prepare("UPDATE credit_cards SET pin=:pin,balance=:balance,firstname=:firstname,lastname=:lastname,credit_limit=:credit_limit WHERE number=(:number)");
        query.bindValue(":number",card.card_number());
        query.bindValue(":pin",card.card_pincode());
        query.bindValue(":balance",card.card_balance());
        query.bindValue(":firstname",card.owner_firstname());
        query.bindValue(":lastname",card.owner_lastname());
        query.bindValue(":credit_limit",card.credit_limit());
        query.exec();
    }
}
void DB::serialize_amanager(const AManager& manager) const
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
void DB::serialize_aadministrator(const AAdministrator& admin) const
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
bool DB::exists_card(const ProductKeyInfo<ICard>& key) const noexcept
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
bool DB::exists_manager(const ProductKeyInfo<AManager>& key) const noexcept
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
void DB::remove_card(const ProductKeyInfo<ICard>& key) const
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
void DB::remove_manager(const ProductKeyInfo<AManager>& key) const
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
auto DB::deserialize_card(const LoginParams<ICard>& key) const -> out_product_ptr
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
        return uptr;
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
        std::unique_ptr<CreditCard> res(dynamic_cast<CreditCard*>(uicardPtr.release()));
        res->set_credit_limit(credit_limit);
        return res;
    }
    throw DoesntExistException("Specified card doesn't exist");
}
auto DB::deserialize_manager(const LoginParams<AManager>& key) const -> out_product_ptr
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

void DB::do_change_balance(const ProductKeyInfo<ICard>& key, const ICard::balance_type amount) const
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
