#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include <QString>
#include <memory>

class ICard;

class Transaction;

class ISerializer;

class TransactionManager
{
private:
    const std::shared_ptr<ICard> currentCard;
    const std::shared_ptr<ISerializer> serializer;
public:
    TransactionManager(std::shared_ptr<ICard>,std::shared_ptr<ISerializer>);
    const std::shared_ptr<Transaction> getMoney(const float) const;
    const std::shared_ptr<Transaction> putMoney(const float) const;
    const std::shared_ptr<Transaction> sendTransaction(const float,const QString&) const;
};

#endif // TRANSACTIONMANAGER_H
