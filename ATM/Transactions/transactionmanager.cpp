#include "transaction.h"
#include "transactionmanager.h"

#include <Product/Cards/icard.h>

TransactionManager::TransactionManager(std::shared_ptr<ICard> card,std::shared_ptr<ISerializer> ser) : currentCard(card) , serializer(ser)
{
}

const std::shared_ptr<Transaction> TransactionManager::getMoney(const float sum) const
{
    //TODO add methods in ICard class
    currentCard -> set_balance(currentCard ->card_balance() - sum);
    std::shared_ptr<Transaction> transaction = std::make_shared<Transaction>(sum,currentCard);
    return transaction;
}

const std::shared_ptr<Transaction> TransactionManager::putMoney(const float sum) const
{
    //TODO add methods in ICard class

    currentCard -> set_balance(currentCard ->card_balance() + sum);
    std::shared_ptr<Transaction> transaction = std::make_shared<Transaction>(sum,currentCard);
    return transaction;
}

const std::shared_ptr<Transaction> TransactionManager::sendTransaction(const float sum,const QString& cardToNum) const
{
    //TODO add methods in ICard class
    currentCard -> set_balance(currentCard ->card_balance() - sum);
    //serializer -> changeBalance(sum);
    std::shared_ptr<Transaction> transaction = std::make_shared<Transaction>(sum,currentCard,cardToNum);
    return transaction;
}

