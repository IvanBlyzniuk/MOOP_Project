#ifndef MANAGERLOGINWIDGET_H
#define MANAGERLOGINWIDGET_H
#include <Enums/widgets.h>
#include <QWidget>
//#include <Product/Managers/privilegedmanager.h>
namespace Ui {
class ManagerLoginWidget;
}
class AManager;
class AAdministrator;
template<typename T>
class ILoginAgent;
class StandardManager;
class PrivilegedManager;
class ISerializer;

class ManagerLoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerLoginWidget(std::shared_ptr<ISerializer>,QWidget *parent = nullptr);
    ~ManagerLoginWidget();

private:
    Ui::ManagerLoginWidget *ui;
    std::shared_ptr<ILoginAgent<AManager>> loginAgent;
    void login(AManager&);
    void makeManagerLogin();
    void cleanInput();
    void cleanOutput();
signals:
    void changePage(int);
    void sendManager(std::shared_ptr<AManager>);
private slots:
    void on_backButton_clicked();
    void on_loginButton_clicked();
};

#endif // MANAGERLOGINWIDGET_H
