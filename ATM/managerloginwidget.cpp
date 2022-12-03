#include "managerloginwidget.h"
#include "ui_managerloginwidget.h"

#include <Login/managerloginagent.h>

ManagerLoginWidget::ManagerLoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerLoginWidget)
{
    ui->loginField->setEchoMode(QLineEdit::Password);
    ui->setupUi(this);
    loginAgent = std::make_shared<ManagerLoginAgent>(serializer);
}

ManagerLoginWidget::~ManagerLoginWidget()
{
    delete ui;
}

void ManagerLoginWidget::login(std::shared_ptr<AManager>)
{
    emit changePage(static_cast<int>(Widgets::DEFAULT_MANAGER));
}

void ManagerLoginWidget::login(std::shared_ptr<AAdministrator>)
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
        login(manager);
    }
    catch(...)
    {
        ui->infoField->setText("Login data is incorrect!");
    }
    }
}

void ManagerLoginWidget::on_backButton_clicked()
{
    emit changePage(static_cast<int>(Widgets::CARD_LOGIN));
}

