#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->insertWidget(0,&login);
    ui->stackedWidget->insertWidget(1,&test);
    ui->stackedWidget->setCurrentIndex(0);

    connect(&login,SIGNAL(changePage(int)),this,SLOT(loginClicked(int)));
    connect(&login,SIGNAL(sendUserSignal(QString)),&test,SLOT(setCurUser(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::loginClicked(int page)
{
    ui->stackedWidget->setCurrentIndex(page);
}

