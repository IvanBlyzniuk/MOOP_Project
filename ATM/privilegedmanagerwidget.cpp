#include "privilegedmanagerwidget.h"
#include "ui_privilegedmanagerwidget.h"
#include "Product/Factories/ManagerFactory.h"
#include "Product/Factories/AdministratorFactory.h"
#include "Product/Managers/StandardManager.h"
#include "Product/Managers/privilegedmanager.h"
#include "Exceptions/AlreadyExistsException.h"
#include "Exceptions/DoesntExistException.h"
#include "Enums/widgets.h"
#include "Registrations/managerregistrator.h"

PrivilegedManagerWidget::PrivilegedManagerWidget(std::shared_ptr<ISerializer> serializer,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrivilegedManagerWidget),
    registrator(std::make_shared<ManagerRegistrator<AManager>>(serializer))
{
    ui->setupUi(this);
    ui->passwordField->setEchoMode(QLineEdit::Password);
    ui->infoField->setReadOnly(true);
}

PrivilegedManagerWidget::~PrivilegedManagerWidget()
{
    delete ui;
}

bool PrivilegedManagerWidget::checkDelete()
{
    if(ui->loginField->text().isEmpty())
    {
        ui->infoField->setText("Please fill in login.");
        return false;
    }
    if(currentManager->login() == ui->loginField->text())
    {
        ui->infoField->setText("You cannot delete yourself.");
        return false;
    }
    return true;
}

bool PrivilegedManagerWidget::checkAdd()
{
    if(ui->loginField->text().isEmpty() || ui->passwordField->text().isEmpty())
    {
        ui->infoField->setText("Please fill in all fields.");
        return false;
    }
    if(!registrator->can_be_registered(ui->loginField->text()))
    {
        ui->infoField->setText("Specified manager already exists.");
        return false;
    }
    return true;
}

void PrivilegedManagerWidget::cleanInput()
{
    ui->loginField->clear();
    ui->passwordField->clear();
}
void PrivilegedManagerWidget::cleanOutput()
{
    ui->infoField->clear();
}

void PrivilegedManagerWidget::setCurrentManager(std::shared_ptr<AManager> manager)
{
    currentManager = manager;
}

void PrivilegedManagerWidget::on_deleteManagerButton_clicked()
{
    if(!checkDelete())
        return;
    try
    {
        registrator->remove_registration(ui->loginField->text());
        cleanInput();
        ui->infoField->setText("Manager deleted successfully.");
    }
    catch(const DoesntExistException&)
    {
        ui->infoField->setText("Specified manager doesn't exist.");
    }
}


void PrivilegedManagerWidget::on_addManagerButton_clicked()
{
    if(!checkAdd())
        return;
    try
    {
        std::shared_ptr<AManager> newManager;
        if(!ui->makePrivilegedButton->isChecked())
        {
            ManagerFactory<StandardManager> factory;
            QString login = ui->loginField->text();
            QString password = ui->passwordField->text();
            newManager = factory.create_product(ProductCommonInfo<AManager>(login,password));
        }
        else
        {
            AdministratorFactory<PrivilegedManager> factory;
            QString login = ui->loginField->text();
            QString password = ui->passwordField->text();
            newManager = factory.create_product(ProductCommonInfo<AAdministrator>(login,password));
        }
        registrator->make_registration(newManager);
        cleanInput();
        ui->infoField->setText("Manager added successfully.");
    }
    catch(const AlreadyExistsException&)
    {
        ui->infoField->setText("Specified manager already exists.");
    }
}


void PrivilegedManagerWidget::on_backButton_clicked()
{
    cleanInput();
    cleanOutput();
    emit changePage(static_cast<int>(Widgets::MANAGER_LOGIN));
}


void PrivilegedManagerWidget::on_redactorModeButton_clicked()
{
    cleanInput();
    cleanOutput();
    emit changePage(static_cast<int>(Widgets::DEFAULT_MANAGER));
}

