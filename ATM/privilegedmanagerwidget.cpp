#include "privilegedmanagerwidget.h"
#include "ui_privilegedmanagerwidget.h"
#include "Product/Factories/ManagerFactory.h"
#include "Product/Factories/AdministratorFactory.h"
#include "Product/Managers/StandardManager.h"
#include "Product/Managers/privilegedmanager.h"
#include "Exceptions/AlreadyExistsException.h"

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
        if(ui->makePrivilegedButton->isChecked())
        {
            ManagerFactory<StandardManager> factory;
            QString login = ui->loginField->text();
            QString password = ui->passwordField->text();
            factory.create_product(ProductCommonInfo<AManager>(login,password));

        }
        else
        {

        }
    }
    catch(AlreadyExistsException e)
    {
        ui->infoField->setText("Specified manager already exists.");
    }
}

