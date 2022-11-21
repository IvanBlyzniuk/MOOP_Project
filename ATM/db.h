#ifndef DB_H
#define DB_H
#include <QtSql>

class DB
{
public:
    DB();
    ~DB();
    void deserializeCard(const QString& number,const QString& pin);
    void deserializeManager(const QString& login,const QString& password);
    //Debit card
    void serialize(const QString& number,const QString& pin,const float balance,const QString& owner_firstname,const QString& owner_lastname);
    //Credit card
    void serialize(const QString& number,const QString& pin,const float balance,const QString& owner_firstname,const QString& owner_lastname,const float credit_limit);
    //Manager
    void serialize(const QString& login, const QString& password, const bool isPriviliged);
private:
    QSqlDatabase sdb;
    void serializeManager(const QString& login, const QString& password);
    void serializePrivilegedManager(const QString& login, const QString& password);
};

#endif // DB_H
