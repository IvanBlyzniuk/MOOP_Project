#include "changepinwidget.h"
#include "Product/Cards/icard.h"
#include "ui_changepinwidget.h"

ChangePinWidget::ChangePinWidget(std::shared_ptr<ISerializer> ser,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePinWidget),
    serializer(ser)
{
    ui->setupUi(this);
}

ChangePinWidget::~ChangePinWidget()
{
    delete ui;
}

bool ChangePinWidget::check()
{
    if(ui->oldPinField->text().isEmpty() || ui->newPinField->text().isEmpty())
    {
        ui->infoField->setText("Please, fill in all fields.");
        return false;
    }
    if(ui->oldPinField->text() != currentCard->card_pincode())
    {
        ui->infoField->setText("Please, enter correct old PIN.");
        return false;
    }
    if(ui->oldPinField->text().length() < 3 || ui->oldPinField->text().length() > 3)
    {
        ui->infoField->setText("Incorrect PIN length!");
        return false;
    }
    if(ui->oldPinField->text() == ui->newPinField->text())
    {
        ui->infoField->setText("Please, enter new PIN.");
        return false;
    }
    return true;
}

void ChangePinWidget::setCurrentCard(std::shared_ptr<ICard> card)
{
    currentCard = card;
}

void ChangePinWidget::on_goBackButton_clicked()
{
    emit changePage(static_cast<int>(Widgets::MAIN_OPTIONS));
}


void ChangePinWidget::on_changePinButton_clicked()
{
    if(check())
    {
        //currentCard -> changePIN
        ui->infoField->setText("PIN changed succsessfully.");
    }
}

