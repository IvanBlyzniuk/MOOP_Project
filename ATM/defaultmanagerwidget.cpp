#include "defaultmanagerwidget.h"
#include "ui_defaultmanagerwidget.h"

DefaultManagerWidget::DefaultManagerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DefaultManagerWidget)
{
    ui->setupUi(this);
}

DefaultManagerWidget::~DefaultManagerWidget()
{
    delete ui;
}

void DefaultManagerWidget::goBack(const AManager &)
{
    emit changePage(static_cast<int>(Widgets::CARD_LOGIN));
}

void DefaultManagerWidget::goBack(const IAdministrator &)
{
    emit changePage(static_cast<int>(Widgets::PRIVILEGED_MANAGER));
}


//registerC(){
//    if(checkbox){
//        registrator = new CardRegistrator<DebitCard>(new CardFactory<DebitCard>());
//    }
//    else{
//        registrator = new CardRegistrator<CreditCard>(new CardFactory<CreditCard>());
//    }
//    registrator.
//}

void DefaultManagerWidget::on_backButton_clicked()
{

}

void DefaultManagerWidget::setCurrentManager(std::shared_ptr<AManager> manager)
{
    currentManager = manager;
}

