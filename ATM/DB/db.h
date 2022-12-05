#ifndef DB_H
#define DB_H
#include "DB/iserializer.h"
#include <QtSql>
#include <memory>
#include "Product/Cards/icard.h"

class DebitCard;
class CreditCard;
class AManager;
class AAdministrator;

class DB : public ISerializer
{
public:
    DB();
    ~DB();
private:
    void do_serialize(in_product_ptr) const override;
    bool do_exists(const key_info_type&) const noexcept override;
    void do_remove(const key_info_type&) const override;
    out_product_ptr do_deserialize(const login_info_type&) const override;
    void change_balance(const ProductKeyInfo<ICard>&, const ICard::balance_type) const;
private:
    void serialize_debit_card(const DebitCard&) const;
    void serialize_credit_card(const CreditCard&) const;
    void serialize_amanager(const AManager&) const;
    void serialize_aadministrator(const AAdministrator&) const;
    bool exists_card(const ProductKeyInfo<ICard>&) const noexcept;
    bool exists_manager(const ProductKeyInfo<AManager>&) const noexcept;
    void remove_card(const ProductKeyInfo<ICard>&) const;
    void remove_manager(const ProductKeyInfo<AManager>&) const;
    out_product_ptr deserialize_card(const LoginParams<ICard>&) const;
    out_product_ptr deserialize_manager(const LoginParams<AManager>&) const;
private:
    QSqlDatabase sdb;
};

#endif // DB_H
