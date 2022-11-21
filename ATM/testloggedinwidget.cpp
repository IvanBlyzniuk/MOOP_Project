#include "testloggedinwidget.h"
#include "loginwidget.h"
#include "ui_testloggedinwidget.h"

TestLoggedInWidget::TestLoggedInWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestLoggedInWidget)
{
    ui->setupUi(this);

}

TestLoggedInWidget::~TestLoggedInWidget()
{
    delete ui;
}

void TestLoggedInWidget::setCurUser(const QString &str)
{
    curUser = str;
    ui->label->setText(curUser);
}
