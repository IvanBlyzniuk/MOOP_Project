#include "managerloginwidget.h"
#include "ui_managerloginwidget.h"

#include <Login/managerloginagent.h>
#include <Product/Managers/privilegedmanager.h>
#include <Product/Managers/amanager.h>
#include <Product/Managers/standardmanager.h>

ManagerLoginWidget::ManagerLoginWidget(std::shared_ptr<ISerializer> serializer,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerLoginWidget),
    loginAgent(std::make_shared<ManagerLoginAgent>(serializer))
{
    ui->setupUi(this);
    ui->passwordField->setEchoMode(QLineEdit::Password);
    ui->infoField->setReadOnly(true);
}

ManagerLoginWidget::~ManagerLoginWidget()
{
    delete ui;
}

void ManagerLoginWidget::login(AManager& manager)
{
    try
    {
        [[maybe_unused]] auto ptr = dynamic_cast<PrivilegedManager&>(manager);
        emit changePage(static_cast<int>(Widgets::PRIVILEGED_MANAGER));
    }
    catch (const std::bad_cast&)
    {
        emit changePage(static_cast<int>(Widgets::DEFAULT_MANAGER));
    }
}

void ManagerLoginWidget::makeManagerLogin()
{
    if(!ui->loginField->text().isEmpty() && !ui->passwordField->text().isEmpty())
    {
    try
    {
        std::shared_ptr<AManager> manager = loginAgent -> login({ui->loginField->text(),ui->passwordField->text()});
        emit sendManager(manager);
        cleanInput();
        cleanOutput();
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

void ManagerLoginWidget::cleanInput()
{
    ui->loginField->clear();
    ui->passwordField->clear();
}
void ManagerLoginWidget::cleanOutput()
{
    ui->infoField->clear();
}

void ManagerLoginWidget::on_backButton_clicked()
{
    cleanInput();
    cleanOutput();
    emit changePage(static_cast<int>(Widgets::CARD_LOGIN));
}


void ManagerLoginWidget::on_loginButton_clicked()
{
    makeManagerLogin();
}

