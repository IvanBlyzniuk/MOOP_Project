#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Enums/widgets.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      serializer(nullptr),
      cardLoginW(new LoginWidget(nullptr,serializer)),
      managerLoginW(new ManagerLoginWidget(serializer)),
      defaultManagerW(new DefaultManagerWidget(serializer)),
      privilegedManagerW(new PrivilegedManagerWidget),
      mainOptionsW(new MainOptionsWidget),
      putWithdrawW(new PutWithdrawWidget(serializer)),
      changePinW(new ChangePinWidget(serializer)),
      transactionW(new TransactionWidget(serializer))
{
    ui->setupUi(this);
    putWidgets();
    connectSlots();
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

void MainWindow::putWidgets()
{
    ui->stackedWidget->insertWidget(static_cast<int>(Widgets::CARD_LOGIN),cardLoginW);
    ui->stackedWidget->insertWidget(static_cast<int>(Widgets::MANAGER_LOGIN),managerLoginW);
    ui->stackedWidget->insertWidget(static_cast<int>(Widgets::DEFAULT_MANAGER),defaultManagerW);
    ui->stackedWidget->insertWidget(static_cast<int>(Widgets::PRIVILEGED_MANAGER),privilegedManagerW);
    ui->stackedWidget->insertWidget(static_cast<int>(Widgets::MAIN_OPTIONS),mainOptionsW);
    ui->stackedWidget->insertWidget(static_cast<int>(Widgets::PUT_WITHDRAW),putWithdrawW);
    ui->stackedWidget->insertWidget(static_cast<int>(Widgets::CHANGE_PIN),changePinW);
    ui->stackedWidget->insertWidget(static_cast<int>(Widgets::TRANSACTIONS),transactionW);
    ui->stackedWidget->setCurrentIndex(static_cast<int>(Widgets::CARD_LOGIN));
}
void MainWindow::connectSlots()
{
    connect(cardLoginW,SIGNAL(changePage(int)),this,SLOT(changeCurrentWidget(int)));
    connect(managerLoginW,SIGNAL(changePage(int)),this,SLOT(changeCurrentWidget(int)));
    connect(defaultManagerW,SIGNAL(changePage(int)),this,SLOT(changeCurrentWidget(int)));
    connect(mainOptionsW,SIGNAL(changePage(int)),this,SLOT(changeCurrentWidget(int)));
    connect(putWithdrawW,SIGNAL(changePage(int)),this,SLOT(changeCurrentWidget(int)));
    connect(changePinW,SIGNAL(changePage(int)),this,SLOT(changeCurrentWidget(int)));
    connect(transactionW,SIGNAL(changePage(int)),this,SLOT(changeCurrentWidget(int)));

    connect(cardLoginW,SIGNAL(setCurrentCard(std::shared_ptr<ICard>)),mainOptionsW,SLOT(setCurrentCard(std::shared_ptr<ICard>)));
    connect(cardLoginW,SIGNAL(setCurrentCard(std::shared_ptr<ICard>)),putWithdrawW,SLOT(setCurrentCard(std::shared_ptr<ICard>)));
    connect(cardLoginW,SIGNAL(setCurrentCard(std::shared_ptr<ICard>)),changePinW,SLOT(setCurrentCard(std::shared_ptr<ICard>)));
    connect(cardLoginW,SIGNAL(setCurrentCard(std::shared_ptr<ICard>)),transactionW,SLOT(setCurrentCard(std::shared_ptr<ICard>)));
}
