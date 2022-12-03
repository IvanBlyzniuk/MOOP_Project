#include "managerloginwidget.h"
#include "ui_managerloginwidget.h"

ManagerLoginWidget::ManagerLoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerLoginWidget)
{
    ui->setupUi(this);
}

ManagerLoginWidget::~ManagerLoginWidget()
{
    delete ui;
}

void ManagerLoginWidget::on_backButton_clicked()
{
    emit changePage(static_cast<int>(Widgets::CARD_LOGIN));
}

