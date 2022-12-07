#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H
#include <Enums/widgets.h>
#include <QWidget>

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
    explicit LoginWidget(QWidget *parent = nullptr,std::shared_ptr<ISerializer> = nullptr);
    ~LoginWidget();

private slots:
    void on_loginButton_clicked();

    void on_privilegedButton_clicked();

private:
    Ui::LoginWidget *ui;
    std::shared_ptr<ILoginAgent<ICard>> loginAgent;
    std::shared_ptr<ISerializer> serializer;
    void login();
    void cleanInput();
    void cleanOutput();

signals:
    void changePage(int);
    void sendCard(std::shared_ptr<ICard>);

};

#endif // LOGINWIDGET_H
