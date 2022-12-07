#include "transaction.h"
#include "Product/Cards/icard.h"

Transaction::Transaction(float sum, std::shared_ptr<ICard> from,const QString& to) : cardFrom(from),cardTo(to),msum(sum)
{
}


const QString Transaction::toMessage() const
{
    QString message;
    if(cardTo != "")
    {
        message = "Transaktion sent to " + cardTo
                + "<br> Transaction amount: " + QString::number(msum)
                + "<br> Current account: " + QString::number(cardFrom->card_balance());
    }
    else
    {
       if(msum > 0)
       {
           message = "Account replenishment was successful <br>Transaction amount: " + QString::number(qAbs(msum))
                   + "<br>Current account: " + QString::number(cardFrom->card_balance());
       }
       else
       {
           message = "Money withdrawn from account successfully <br>Transaction amount: " + QString::number(msum)
                   + "<br>Current account: " + QString::number(cardFrom->card_balance());
       }
    }
    return message;
}

