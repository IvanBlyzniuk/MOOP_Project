#include "managerloginwidget.h"
#include "ui_managerloginwidget.h"

#include <Login/managerloginagent.h>

#include <Product/Managers/amanager.h>

ManagerLoginWidget::ManagerLoginWidget(std::shared_ptr<ISerializer> serializer,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerLoginWidget)
{
    ui->setupUi(this);
    ui->loginField->setEchoMode(QLineEdit::Password);
    loginAgent = std::make_shared<ManagerLoginAgent>(serializer);
}

ManagerLoginWidget::~ManagerLoginWidget()
{
    delete ui;
}

void ManagerLoginWidget::login(const AManager&)
{
    emit changePage(static_cast<int>(Widgets::DEFAULT_MANAGER));
}

void ManagerLoginWidget::login(const AAdministrator&)
{
    emit changePage(static_cast<int>(Widgets::PRIVILEGED_MANAGER));
}

void ManagerLoginWidget::makeManagerLogin()
{
    if(!ui->loginField->text().isEmpty() && !ui->passwordField->text().isEmpty())
    {
    try
    {
    //    loginAgent -> login({ui->cardNumField->text(),ui->pinField->text()});
        std::shared_ptr<AManager> manager = loginAgent -> login({ui->loginField->text(),ui->passwordField->text()});
        emit sendManager(manager);
        login(*manager.get());
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

void ManagerLoginWidget::on_backButton_clicked()
{
    emit changePage(static_cast<int>(Widgets::CARD_LOGIN));
}


void ManagerLoginWidget::on_loginButton_clicked()
{
    makeManagerLogin();
}

