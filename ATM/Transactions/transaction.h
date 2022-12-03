#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <memory>


class ICard;

class Transaction
{
private:
    std::shared_ptr<ICard> cardFrom;
    const QString cardTo;
    const float msum;

public:
    Transaction(float,std::shared_ptr<ICard>,const QString& = "");

    const QString toMessage() const;
};

#endif // TRANSACTION_H
