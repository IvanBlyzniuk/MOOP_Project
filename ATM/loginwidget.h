#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H
#include <Enums/widgets.h>
#include <QWidget>
//#include <Login/cardloginagent.h>

template<typename T>
class ILoginAgent;

class ISerializer;

class ICard;

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    //explicit LoginWidget(QWidget *parent = nullptr);
    explicit LoginWidget(QWidget *parent = nullptr,std::shared_ptr<ISerializer> = nullptr);
    ~LoginWidget();

private slots:
    void on_loginButton_clicked();

private:
    Ui::LoginWidget *ui;
    std::shared_ptr<ILoginAgent<ICard>> loginAgent;
    std::shared_ptr<ISerializer> serializer;
    void login();

signals:
    void changePage(int);
    void sendUserSignal(const QString&);

};

#endif // LOGINWIDGET_H
