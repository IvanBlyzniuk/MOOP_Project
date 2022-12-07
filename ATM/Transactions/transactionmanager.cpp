#include "transaction.h"
#include "transactionmanager.h"
#include "DB/iserializer.h"
#include <Product/Cards/icard.h>
#include <QDebug>

TransactionManager::TransactionManager(std::shared_ptr<ICard> card,std::shared_ptr<ISerializer> ser) : currentCard(card) , serializer(ser)
{
}

const std::shared_ptr<Transaction> TransactionManager::getMoney(const float sum) const
{
    currentCard -> set_balance(currentCard ->card_balance() - sum);
    std::shared_ptr<Transaction> transaction = std::make_shared<Transaction>(sum,currentCard);
    serializer->serialize(currentCard);
    return transaction;
}

const std::shared_ptr<Transaction> TransactionManager::putMoney(const float sum) const
{
    currentCard -> set_balance(currentCard ->card_balance() + sum);
    std::shared_ptr<Transaction> transaction = std::make_shared<Transaction>(sum,currentCard);
    serializer->serialize(currentCard);
    return transaction;
}

const std::shared_ptr<Transaction> TransactionManager::sendTransaction(const float sum,const QString& cardToNum) const
{
    currentCard -> set_balance(currentCard ->card_balance() - sum);
    serializer -> change_balance(cardToNum,sum);
    std::shared_ptr<Transaction> transaction = std::make_shared<Transaction>(sum,currentCard,cardToNum);
    serializer->serialize(currentCard);
    return transaction;
}

