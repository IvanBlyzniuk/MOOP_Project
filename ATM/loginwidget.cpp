#include "loginwidget.h"
#include "ui_loginwidget.h"
#include <QRegularExpressionValidator>

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    ui->pinField->setEchoMode(QLineEdit::Password);
    ui->cardNumField->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->pinField->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->infoField->setReadOnly(true);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::login()
{
    QString toSend = ui->cardNumField->text();
    //loginClickedL(1);
    changePage(1);
    qDebug()<<toSend;
    sendUserSignal(toSend);
}




void LoginWidget::on_loginButton_clicked()
{
    login();
}

