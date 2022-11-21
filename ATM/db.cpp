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

//TODO: make the method return ICard
void DB::deserializeCard(const QString& number,const QString& pin)
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
        //return DebitCard(number,pin,balance,first_name,last_name);
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
        //return CreditCard(number,pin,balance,first_name,last_name,credit_limit);
        qDebug() << "Deserialized credit card: num=" << number << " pin=" << pin << " balance=" << balance <<" firstname=" << first_name << " limit="<<credit_limit;
    }
    //throw new QException();
}

void DB::deserializeManager(const QString& login,const QString& password)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM managers WHERE login=(:login) AND password=(:password)");
    query.bindValue(":login",login);
    query.bindValue(":password",password);
    query.exec();
    if(query.first())
    {
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
        //return PrivilegedManager(login, password);
        qDebug() << "Deserialized priviliged_manager: login=" << login << " password=" << password;
    }
}

//Debit Card
void DB::serialize(const QString& number,const QString& pin,const float balance,const QString& owner_firstname,const QString& owner_lastname)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM debit_cards WHERE number=(:number)");
    query.bindValue(":number",number);
    qDebug() << query.exec();
    qDebug() << query.size();
    qDebug() << query.isSelect();
    if(!query.first())
    {
        query.prepare("INSERT INTO debit_cards VALUES (:number,:pin,:balance,:firstname,:lastname)");
        query.bindValue(":number",number);
        query.bindValue(":pin",pin);
        query.bindValue(":balance",balance);
        query.bindValue(":firstname",owner_firstname);
        query.bindValue(":lastname",owner_lastname);
        query.exec();
    }
    else
    {
        query.prepare("UPDATE debit_cards SET number=:number,pin=:pin,balance=:balance,firstname=:firstname,lastname=:lastname) WHERE number=(:number)");
        query.bindValue(":number",number);
        query.bindValue(":pin",pin);
        query.bindValue(":balance",balance);
        query.bindValue(":firstname",owner_firstname);
        query.bindValue(":lastname",owner_lastname);
        query.exec();
    }
}

//Credit card
void DB::serialize(const QString& number,const QString& pin,const float balance,const QString& owner_firstname,const QString& owner_lastname,const float credit_limit)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM credit_cards WHERE number=(:number)");
    query.bindValue(":number",number);
    query.exec();
    if(!query.first())
    {
        query.prepare("INSERT INTO credit_cards VALUES (:number,:pin,:balance,:firstname,:lastname,:credit_limit)");
        query.bindValue(":number",number);
        query.bindValue(":pin",pin);
        query.bindValue(":balance",balance);
        query.bindValue(":firstname",owner_firstname);
        query.bindValue(":lastname",owner_lastname);
        query.bindValue(":credit_limit",credit_limit);
        query.exec();
    }
    else
    {
        query.prepare("UPDATE credit_cards SET number=:number,pin=:pin,balance=:balance,firstname=:firstname,lastname=:lastname,credit_limit=:credit_limit) WHERE number=(:number)");
        query.bindValue(":number",number);
        query.bindValue(":pin",pin);
        query.bindValue(":balance",balance);
        query.bindValue(":firstname",owner_firstname);
        query.bindValue(":lastname",owner_lastname);
        query.bindValue(":credit_limit",credit_limit);
        query.exec();
    }
}

void DB::serialize(const QString& login, const QString& password, const bool isPriviliged)
{
    if(isPriviliged)
        serializePrivilegedManager(login, password);
    else
        serializeManager(login, password);
}

void DB::serializeManager(const QString& login, const QString& password)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM managers WHERE login=(:login)");
    query.bindValue(":login",login);
    query.exec();
    if(!query.first())
    {
        query.prepare("INSERT INTO managers VALUES (:login,:password)");
        query.bindValue(":login",login);
        query.bindValue(":password",password);
        query.exec();
    }
    else
    {
        qDebug() << "Manager already exists";
        //throw new QException();
    }
}

void DB::serializePrivilegedManager(const QString& login, const QString& password)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM privileged_managers WHERE login=(:login)");
    query.bindValue(":login",login);
    query.exec();
    if(!query.first())
    {
        query.prepare("INSERT INTO privileged_managers VALUES (:login,:password)");
        query.bindValue(":login",login);
        query.bindValue(":password",password);
        query.exec();
    }
    else
    {
        qDebug() << "Manager already exists";
        //throw new QException();
    }
}

