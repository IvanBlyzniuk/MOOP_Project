#include "transactionwidget.h"
#include "Product/Cards/icard.h"
#include "Transactions/transaction.h"
#include "Transactions/transactionmanager.h"
#include "ui_transactionwidget.h"

#include <QRegularExpressionValidator>

#include <Exceptions/DoesntExistException.h>

TransactionWidget::TransactionWidget(std::shared_ptr<ISerializer> ser,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransactionWidget),
    serializer(ser)
{
    ui->setupUi(this);
    ui->pinInputField->setEchoMode(QLineEdit::Password);
    ui->pinInputField->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->moneyInputField->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9]{0,6}(\\.[0-9]{1,2})?$ ")));
    ui->cardNumField->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
}

TransactionWidget::~TransactionWidget()
{
    delete ui;
}

void TransactionWidget::setCurrentCard(std::shared_ptr<ICard> card)
{
    currentCard = card;
}

void TransactionWidget::on_backButton_clicked()
{
    emit changePage(static_cast<int>(Widgets::MAIN_OPTIONS));
}

bool TransactionWidget::check()
{
    if(ui->pinInputField->text() != currentCard->card_pincode())
    {
        ui->infoField->setText("Please, enter correct PIN.");
        return false;
    }
    if(ui->moneyInputField->text().toFloat() == 0)
    {
        ui->infoField->setText("Please, enter sum which is more then 0.");
        return false;
    }
    return true;
}


void TransactionWidget::on_sendTransactionButton_clicked()
{
    if(check())
    {
        TransactionManager tr(currentCard,serializer);
        try
        {
            float sum = ui->moneyInputField->text().toFloat();
            QString cardNum = ui->cardNumField->text();
            ui->infoField->setText(tr.sendTransaction(sum,cardNum)->toMessage());
        }
        catch (const DoesntExistException&)
        {
            ui->infoField->setText("Card number of the receiver is not valid.");
        }
    }
}

