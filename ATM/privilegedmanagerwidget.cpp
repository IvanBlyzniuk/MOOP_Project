#include "privilegedmanagerwidget.h"
#include "ui_privilegedmanagerwidget.h"
#include "Product/Factories/ManagerFactory.h"
#include "Product/Factories/AdministratorFactory.h"
#include "Product/Managers/StandardManager.h"
#include "Product/Managers/privilegedmanager.h"
#include "Exceptions/AlreadyExistsException.h"
#include "Exceptions/DoesntExistException.h"
#include "Enums/widgets.h"

PrivilegedManagerWidget::PrivilegedManagerWidget(std::shared_ptr<ISerializer> serializer,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrivilegedManagerWidget)
{
    ui->setupUi(this);
    ui->passwordField->setEchoMode(QLineEdit::Password);
    //registrator = std::make_shared<Mana
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
    return true;
}

bool PrivilegedManagerWidget::checkAdd()
{
    if(ui->loginField->text().isEmpty() || ui->passwordField->text().isEmpty())
    {
        ui->infoField->setText("Please fill in all fields.");
        return false;
    }
    return true;
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
        //registrator->remove_registration(ui->loginField->text());
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
        AManager* newManager;
        if(ui->makePrivilegedButton->isChecked())
        {
            ManagerFactory<StandardManager> factory;
            QString login = ui->loginField->text();
            QString password = ui->passwordField->text();
            newManager = factory.create_product(ProductCommonInfo<AManager>(login,password)).release();
        }
        else
        {
            AdministratorFactory<PrivilegedManager> factory;
            QString login = ui->loginField->text();
            QString password = ui->passwordField->text();
            std::unique_ptr<AAdministrator> uptr = factory.create_product(ProductCommonInfo<AAdministrator>(login,password));
            newManager = dynamic_cast<AManager*>(uptr.release());
            //return std::unique_ptr<AManager>(dynamic_cast<AManager*>(uptr.release()));
        }
        //registrator->make_registration(*newManager);
    }
    catch(const AlreadyExistsException&)
    {
        ui->infoField->setText("Specified manager already exists.");
    }
}


void PrivilegedManagerWidget::on_backButton_clicked()
{
    emit changePage(static_cast<int>(Widgets::MANAGER_LOGIN));
}


void PrivilegedManagerWidget::on_redactorModeButton_clicked()
{
    emit changePage(static_cast<int>(Widgets::DEFAULT_MANAGER));
}

