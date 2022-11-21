#include "privilegedmanagerwidget.h"
#include "ui_privilegedmanagerwidget.h"

PrivilegedManagerWidget::PrivilegedManagerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrivilegedManagerWidget)
{
    ui->setupUi(this);
}

PrivilegedManagerWidget::~PrivilegedManagerWidget()
{
    delete ui;
}
