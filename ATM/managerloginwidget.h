#ifndef MANAGERLOGINWIDGET_H
#define MANAGERLOGINWIDGET_H
#include <Enums/widgets.h>
#include <QWidget>

namespace Ui {
class ManagerLoginWidget;
}
class AManager;
class AAdministrator;
template<typename T>
class ILoginAgent;

class ISerializer;

class ManagerLoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerLoginWidget(QWidget *parent = nullptr);
    ~ManagerLoginWidget();

private:
    Ui::ManagerLoginWidget *ui;
    std::shared_ptr<ILoginAgent<AManager>> loginAgent;
    std::shared_ptr<ISerializer> serializer;
    void login(std::shared_ptr<AManager>);
    void login(std::shared_ptr<AAdministrator>);
    void makeManagerLogin();
signals:
    void changePage(int);
    void sendManager(std::shared_ptr<AManager>);
private slots:
    void on_backButton_clicked();
};

#endif // MANAGERLOGINWIDGET_H
