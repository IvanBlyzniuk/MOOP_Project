#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <IScreenChangeable.h>
#include <QWidget>

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
    void login();

signals:
    void sendUserSignal(const QString&);
    void changePage(int);
};

#endif // LOGINWIDGET_H
