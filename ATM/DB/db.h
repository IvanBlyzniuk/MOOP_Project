#ifndef DB_H
#define DB_H
#include "DB/iserializer.h"
#include <QtSql>
#include <memory>

class DebitCard;
class CreditCard;
class AManager;
class AAdministrator;
class ICard;

class DB : public ISerializer
{
public:
    DB();
    ~DB();
private:
    void do_changeBalance(const ProductKeyInfo<ICard>&, ICard::balance_type) const override;
    void do_serialize(const DebitCard&)                                      const override;
    void do_serialize(const CreditCard&)                                     const override;
    void do_serialize(const AManager&)                                       const override;
    void do_serialize(const AAdministrator&)                                 const override;
    bool do_exists(const ProductKeyInfo<ICard>&)                    const noexcept override;
    bool do_exists(const ProductKeyInfo<AManager>&)                 const noexcept override;
    void do_removeCard(const ProductKeyInfo<ICard>&)                         const override;
    void do_removeManager(const ProductKeyInfo<AManager>&)                   const override;
    out_product_ptr<ICard> do_deserialize(const LoginParams<ICard>&)         const override;
    out_product_ptr<AManager> do_deserialize(const LoginParams<AManager>&)   const override;
private:
    QSqlDatabase sdb;
};

#endif // DB_H
