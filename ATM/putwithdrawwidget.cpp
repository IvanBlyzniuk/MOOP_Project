#include "putwithdrawwidget.h"
#include "Product/Cards/icard.h"
#include "Transactions/transaction.h"
#include "ui_putwithdrawwidget.h"

#include <Transactions/transactionmanager.h>

#include <QRegularExpressionValidator>

PutWithdrawWidget::PutWithdrawWidget(std::shared_ptr<ISerializer> ser,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PutWithdrawWidget),
    serializer(ser)
{
    ui->setupUi(this);
    ui->pinInputField->setEchoMode(QLineEdit::Password);
    ui->pinInputField->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->moneyInputField->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9]{0,6}(\.[0-9]{1,2})?$ ")));
}

PutWithdrawWidget::~PutWithdrawWidget()
{
    delete ui;
}

bool PutWithdrawWidget::check()
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

void PutWithdrawWidget::setCurrentCard(std::shared_ptr<ICard> card)
{
    currentCard = card;
}

void PutWithdrawWidget::on_backButton_clicked()
{
    emit changePage(static_cast<int>(Widgets::MAIN_OPTIONS));
}


void PutWithdrawWidget::on_putMoneyButton_clicked()
{
    if(check())
    {
    TransactionManager tr(currentCard,serializer);
    ui->infoField->setText(tr.putMoney(ui->moneyInputField->text().toFloat())->toMessage());
    }
}


void PutWithdrawWidget::on_withdrawMoneyButton_clicked()
{
    if(check())
    {
        try {
            TransactionManager tr(currentCard,serializer);
            ui->infoField->setText(tr.getMoney(ui->moneyInputField->text().toFloat()*(-1))->toMessage());
        } catch (...)
        {
            ui->infoField->setText("Your current limit does not allow you to withdraw such amount of money.");
        }
    }
}

