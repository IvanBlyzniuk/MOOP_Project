#include "putwithdrawwidget.h"
#include "ui_putwithdrawwidget.h"

PutWithdrawWidget::PutWithdrawWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PutWithdrawWidget)
{
    ui->setupUi(this);
}

PutWithdrawWidget::~PutWithdrawWidget()
{
    delete ui;
}
