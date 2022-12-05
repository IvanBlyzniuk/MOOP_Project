#include "mainoptionswidget.h"
#include "Product/Cards/icard.h"
#include "ui_mainoptionswidget.h"

#include <QString>


MainOptionsWidget::MainOptionsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainOptionsWidget)
{
    ui->setupUi(this);
    ui->infoField->setReadOnly(true);
}

MainOptionsWidget::~MainOptionsWidget()
{
    delete ui;
}

void MainOptionsWidget::cleanOutput()
{
    ui->infoField->clear();
}



void MainOptionsWidget::on_exitButton_clicked()
{
    cleanOutput();
    emit changePage(static_cast<int>(Widgets::CARD_LOGIN));
}

void MainOptionsWidget::setCurrentCard(std::shared_ptr<ICard> card)
{
    currentCard = card;
}


void MainOptionsWidget::on_withdrawPutButton_clicked()
{
    cleanOutput();
    emit changePage(static_cast<int>(Widgets::PUT_WITHDRAW));
}


void MainOptionsWidget::on_sendMoneyButton_clicked()
{
    cleanOutput();
    emit changePage(static_cast<int>(Widgets::TRANSACTIONS));
}


void MainOptionsWidget::on_changePinButton_clicked()
{
    cleanOutput();
    emit changePage(static_cast<int>(Widgets::CHANGE_PIN));
}


void MainOptionsWidget::on_checkBalanceButton_clicked()
{
    ui->infoField->setText("Current balance: " + QString::number(currentCard->card_balance()));
}

