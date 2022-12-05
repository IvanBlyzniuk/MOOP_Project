#include "loginwidget.h"
#include "ui_loginwidget.h"
#include <QRegularExpressionValidator>
#include "Product/Cards/icard.h"
#include "Login/iloginagent.h"

#include "Login/cardloginagent.h"


LoginWidget::LoginWidget(QWidget *parent,std::shared_ptr<ISerializer> mserializer) :
    QWidget(parent),
    ui(new Ui::LoginWidget),
    serializer(mserializer)
{
    ui->setupUi(this);
    ui->pinField->setEchoMode(QLineEdit::Password);
    ui->cardNumField->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->pinField->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->infoField->setReadOnly(true);
    loginAgent = std::make_shared<CardLoginAgent>(serializer);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::login()
{
    if(!ui->cardNumField->text().isEmpty() && !ui->pinField->text().isEmpty())
    {
    try
    {
    //    loginAgent -> login({ui->cardNumField->text(),ui->pinField->text()});
        std::shared_ptr<ICard> card = loginAgent -> login({ui->cardNumField->text(),ui->pinField->text()});
        cleanInput();
        cleanOutput();
        emit sendCard(card);
        emit changePage(static_cast<int>(Widgets::MAIN_OPTIONS));
    }
    catch(...)
    {
        ui->infoField->setText("Login data is incorrect!");
    }
    }
    else
    {
        ui->infoField->setText("Please, fill in all the fields.");
    }
}

void LoginWidget::cleanInput()
{
    ui->cardNumField->clear();
    ui->pinField->clear();
}
void LoginWidget::cleanOutput()
{
    ui->infoField->clear();
}



void LoginWidget::on_loginButton_clicked()
{
    login();
}


void LoginWidget::on_privilegedButton_clicked()
{
    changePage(static_cast<int>(Widgets::MANAGER_LOGIN));
}

