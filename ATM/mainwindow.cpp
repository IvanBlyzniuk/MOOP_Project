#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Enums/widgets.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      cardLoginW(new LoginWidget),
      managerLoginW(new ManagerLoginWidget),
      defaultManagerW(new DefaultManagerWidget),
      privilegedManagerW(new PrivilegedManagerWidget),
      mainOptionsW(new MainOptionsWidget),
      putWithdrawW(new PutWithdrawWidget),
      changePinW(new ChangePinWidget)
{
    ui->setupUi(this);
    ui->stackedWidget->insertWidget(static_cast<int>(Widgets::CARD_LOGIN),cardLoginW);
    ui->stackedWidget->insertWidget(static_cast<int>(Widgets::MANAGER_LOGIN),managerLoginW);
    ui->stackedWidget->insertWidget(static_cast<int>(Widgets::DEFAULT_MANAGER),defaultManagerW);
    ui->stackedWidget->insertWidget(static_cast<int>(Widgets::PRIVILEGED_MANAGER),privilegedManagerW);
    ui->stackedWidget->insertWidget(static_cast<int>(Widgets::MAIN_OPTIONS),mainOptionsW);
    ui->stackedWidget->insertWidget(static_cast<int>(Widgets::PUT_WITHDRAW),putWithdrawW);
    ui->stackedWidget->insertWidget(static_cast<int>(Widgets::CHANGE_PIN),changePinW);
    ui->stackedWidget->setCurrentIndex(static_cast<int>(Widgets::CARD_LOGIN));

    connect(cardLoginW,SIGNAL(changePage(int)),this,SLOT(changeCurrentWidget(int)));
    connect(managerLoginW,SIGNAL(changePage(int)),this,SLOT(changeCurrentWidget(int)));
    connect(defaultManagerW,SIGNAL(changePage(int)),this,SLOT(changeCurrentWidget(int)));
    connect(mainOptionsW,SIGNAL(changePage(int)),this,SLOT(changeCurrentWidget(int)));
    connect(putWithdrawW,SIGNAL(changePage(int)),this,SLOT(changeCurrentWidget(int)));
    connect(changePinW,SIGNAL(changePage(int)),this,SLOT(changeCurrentWidget(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete cardLoginW; cardLoginW = nullptr;

}

void MainWindow::changeCurrentWidget(int page)
{
    ui->stackedWidget->setCurrentIndex(page);
}

