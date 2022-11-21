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
