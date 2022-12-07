#include "defaultmanagerwidget.h"
#include "ui_defaultmanagerwidget.h"
#include "Exceptions/AlreadyExistsException.h"
#include "Exceptions/DoesntExistException.h"
#include <QRegularExpressionValidator>
#include "Product/Factories/CardFactory.h"
#include "Registrations/cardregistrator.h"
#include "Product/Managers/privilegedmanager.h"

DefaultManagerWidget::DefaultManagerWidget(std::shared_ptr<ISerializer> serializer,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DefaultManagerWidget),
    registrator(std::make_shared<CardRegistrator<ICard>>(serializer))
{
    ui->setupUi(this);
    ui->pinInputField->setEchoMode(QLineEdit::Password);
    ui->pinInputField->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->cardNumInputField->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->creditLimitInputField->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9]{0,6}(\\.[0-9]{1,2})?$ ")));
    ui->infoField->setReadOnly(true);
}

DefaultManagerWidget::~DefaultManagerWidget()
{
    delete ui;
}

void DefaultManagerWidget::goBack(AManager& manager)
{
    try
    {
        [[maybe_unused]] auto ptr = dynamic_cast<PrivilegedManager&>(manager);
        emit changePage(static_cast<int>(Widgets::PRIVILEGED_MANAGER));
    }
    catch (const std::bad_cast&)
    {
        emit changePage(static_cast<int>(Widgets::MANAGER_LOGIN));
    }
}

bool DefaultManagerWidget::checkAdd()
{
    if(ui->cardNumInputField->text().isEmpty() || ui->pinInputField->text().isEmpty()
            || ui->firstNameInputField->text().isEmpty() || ui->lastNameInputField->text().isEmpty())
    {
        ui->infoField->setText("Please, fill in all fields.");
        return false;
    }
    if(ui->cardNumInputField->text().size() != 16)
    {
        ui->infoField->setText("Card number should consist of 16 digits.");
        return false;
    }
    if(ui->pinInputField->text().size() != 4)
    {
        ui->infoField->setText("Pin should consist of 4 digits.");
        return false;
    }
    if(!registrator->can_be_registered(ui->cardNumInputField->text()))
    {
        ui->infoField->setText("Specified card already exists.");
        return false;
    }
    return true;
}

bool DefaultManagerWidget::checkDelete()
{
    if(ui->cardNumInputField->text().isEmpty())
    {
        ui->infoField->setText("Please, fill in all fields.");
        return false;
    }
    return true;
}

void DefaultManagerWidget::cleanInput()
{
    ui->cardNumInputField->clear();
    ui->pinInputField->clear();
    ui->firstNameInputField->clear();
    ui->lastNameInputField->clear();
    ui->creditLimitInputField->clear();
}
void DefaultManagerWidget::cleanOutput()
{
    ui->infoField->clear();
}

void DefaultManagerWidget::on_backButton_clicked()
{
    cleanInput();
    cleanOutput();
    goBack(*currentManager.get());
}

void DefaultManagerWidget::setCurrentManager(std::shared_ptr<AManager> manager)
{
    currentManager = manager;
}

void DefaultManagerWidget::on_deleteCardButton_clicked()
{
    if(!checkDelete())
        return;
    try
    {
        registrator->remove_registration({ui->cardNumInputField->text()});
        ui->infoField->setText("Card deleted successfully.");
        cleanInput();
    }
    catch(const DoesntExistException&)
    {
        ui->infoField->setText("Specified card doesn't exist.");
    }
}


void DefaultManagerWidget::on_addCardButton_clicked()
{
    if(!checkAdd())
        return;
    try
    {
        ICard* new_card;
        if(ui->creditLimitInputField->text().isEmpty() || ui->creditLimitInputField->text().toFloat() == 0)
        {
            CardFactory<DebitCard> factory;
            QString number = ui->cardNumInputField->text();
            QString pin = ui->pinInputField->text();
            QString first_name = ui->firstNameInputField->text();
            QString last_name = ui->lastNameInputField->text();
            float balance = 0;
            new_card = factory.create_product(ProductCommonInfo<ICard>(number,pin,first_name,last_name,balance)).release();
        }
        else
        {
            CardFactory<CreditCard> factory;
            QString number = ui->cardNumInputField->text();
            QString pin = ui->pinInputField->text();
            QString first_name = ui->firstNameInputField->text();
            QString last_name = ui->lastNameInputField->text();
            float balance = 0;
            float credit_limit = ui->creditLimitInputField->text().toFloat();
            std::unique_ptr<ICard> card = factory.create_product(ProductCommonInfo<ICard>(number,pin,first_name,last_name,balance));
            CreditCard* credit_card = dynamic_cast<CreditCard*>(card.release());
            credit_card->set_credit_limit(credit_limit);
            new_card = credit_card;
        }
        registrator->make_registration(std::shared_ptr<ICard>(new_card));
        ui->infoField->setText("Card added successfully.");
        cleanInput();
    }
    catch (const AlreadyExistsException&)
    {
        ui->infoField->setText("Specified card alredy exist.");
    }
}

