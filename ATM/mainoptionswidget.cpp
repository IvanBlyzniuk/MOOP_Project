#include "mainoptionswidget.h"
#include "ui_mainoptionswidget.h"


MainOptionsWidget::MainOptionsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainOptionsWidget)
{
    ui->setupUi(this);
}

MainOptionsWidget::~MainOptionsWidget()
{
    delete ui;
}

void MainOptionsWidget::on_exitButton_clicked()
{
    changePage(static_cast<int>(Widgets::CARD_LOGIN));
}

