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
