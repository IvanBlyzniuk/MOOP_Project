#include "loginwidget.h"
#include "ui_loginwidget.h"
#include <QRegularExpressionValidator>


LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    ui->pinField->setEchoMode(QLineEdit::Password);
    ui->cardNumField->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->pinField->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->infoField->setReadOnly(true);
    //loginAgent = std::make_shared<CardLoginAgent>(serializer);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::login()
{
    try
    {
    //    loginAgent -> login({ui->cardNumField->text(),ui->pinField->text()});
        changePage(static_cast<int>(Widgets::MAIN_OPTIONS));
    }
    catch(...)
    {
        ui->infoField->setText("Login data is incorrect!");
    }
}




void LoginWidget::on_loginButton_clicked()
{
    login();
}

