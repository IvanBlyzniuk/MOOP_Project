#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <Login/cardloginagent.h>




namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

private slots:
    void on_loginButton_clicked();

private:
    Ui::LoginWidget *ui;
    std::shared_ptr<ILoginAgent<ICard>> loginAgent;
    std::shared_ptr<ISerializer> serializer;
    void login();

signals:
    void sendUserSignal(const QString&);
    void changePage(int);
};

#endif // LOGINWIDGET_H
