#include "db.h"

DB::DB()
{
    sdb = QSqlDatabase::addDatabase("QSQLITE");
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

void DB::serialize(const DebitCard& card) const
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
        //query.bindValue(":firstname",card.owner_firstname);
        //query.bindValue(":lastname",card.owner_lastname);
        query.exec();
    }
    else
    {
        query.prepare("UPDATE debit_cards SET number=:number,pin=:pin,balance=:balance,firstname=:firstname,lastname=:lastname) WHERE number=(:number)");
        query.bindValue(":number",card.card_number());
        query.bindValue(":pin",card.card_pincode());
        query.bindValue(":balance",card.card_balance());
        //query.bindValue(":firstname",card.owner_firstname);
        //query.bindValue(":lastname",card.owner_lastname);
        query.exec();
    }
}
void DB::serialize(const CreditCard& card) const
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
        //query.bindValue(":firstname",card.owner_firstname);
        //query.bindValue(":lastname",card.owner_lastname);
        query.bindValue(":credit_limit",card.credit_limit());
        query.exec();
    }
    else
    {
        query.prepare("UPDATE credit_cards SET number=:number,pin=:pin,balance=:balance,firstname=:firstname,lastname=:lastname,credit_limit=:credit_limit) WHERE number=(:number)");
        query.bindValue(":number",card.card_number());
        query.bindValue(":pin",card.card_pincode());
        query.bindValue(":balance",card.card_balance());
        //query.bindValue(":firstname",card.owner_firstname);
        //query.bindValue(":lastname",card.owner_lastname);
        query.bindValue(":credit_limit",card.credit_limit());
        query.exec();
    }
}
void DB::serialize(const AManager& manager) const
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
        qDebug() << "Manager already exists";
        //throw new QException();
    }
}
void DB::serialize(const AAdministrator& admin) const
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
        qDebug() << "Manager already exists";
        //throw new QException();
    }
}
bool DB::existstCard(const QString& number) const
{
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
bool DB::existstManager(const QString& login) const
{
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
void DB::removeCard(const QString& number) const
{
    QSqlQuery query;
    query.prepare("DELETE FROM debit_cards WHERE number=(:number)");
    query.bindValue(":number",number);
    query.exec();
    query.prepare("DELETE FROM credit_cards WHERE number=(:number)");
    query.bindValue(":number",number);
    query.exec();
}
void DB::removeManager(const QString& login) const
{
    QSqlQuery query;
    query.prepare("DELETE FROM managers WHERE login=(:login)");
    query.bindValue(":login",login);
    query.exec();
    query.prepare("DELETE FROM privileged_managers WHERE login=(:login)");
    query.bindValue(":login",login);
    query.exec();
}
std::unique_ptr<ICard> DB::deserializeCard(const QString& number,const QString& pin) const
{
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
        return factory.create_product({number,pin,first_name,last_name,balance});
        qDebug() << "Deserialized debit card: num=" << number << " pin=" << pin << " balance=" << balance <<" firstname=" << first_name;
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
        auto uicardPtr = factory.createProduct({number,pin,first_name,last_name,balance});
        ICard * icardPtr = uicardPtr.release();
        CreditCard * cardPtr = dynamic_cast<CreditCard*>(icardPtr);
        std::unique_ptr<CreditCard> res = std::make_unique<CreditCard>(cardPtr);
        //res->set_credit_limit(credit_limit);
        return res;
        qDebug() << "Deserialized credit card: num=" << number << " pin=" << pin << " balance=" << balance <<" firstname=" << first_name << " limit="<<credit_limit;
    }
    //throw new QException();
    return nullptr;
}
std::unique_ptr<AManager> DB::deserializeManager(const QString& login,const QString& password) const
{
    QSqlQuery query;
    query.prepare("SELECT * FROM managers WHERE login=(:login) AND password=(:password)");
    query.bindValue(":login",login);
    query.bindValue(":password",password);
    query.exec();
    if(query.first())
    {
        ManagerFactory<AManager> factory;
        return factory.create_product({login,password});
        //return StandardManager(login, password);
        qDebug() << "Deserialized manager: login=" << login << " password=" << password;
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
        AdministratorFactory<AAdministrator> factory;
        std::unique_ptr<AAdministrator> uptr = factory.create_product({login,password});
        //return std::make_unique(dynamic_cast<AManager*>(uptr.release()));
        qDebug() << "Deserialized priviliged_manager: login=" << login << " password=" << password;
    }
    return nullptr;
}

void DB::changeBalance(const QString& number,double amount) const
{
    if(amount < 0)
        throw new QException();
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
