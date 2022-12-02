#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "changepinwidget.h"
#include "defaultmanagerwidget.h"
#include "loginwidget.h"
#include "mainoptionswidget.h"
#include "managerloginwidget.h"
#include "privilegedmanagerwidget.h"
#include "putwithdrawwidget.h"
#include "testloggedinwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void changeCurrentWidget(int page);

private:
    Ui::MainWindow *ui;
    LoginWidget* cardLoginW;
    ManagerLoginWidget* managerLoginW;
    DefaultManagerWidget* defaultManagerW;
    PrivilegedManagerWidget* privilegedManagerW;
    MainOptionsWidget* mainOptionsW;
    PutWithdrawWidget* putWithdrawW;
    ChangePinWidget* changePinW;
    TestLoggedInWidget* test;
};
#endif // MAINWINDOW_H
