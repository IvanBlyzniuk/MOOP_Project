#ifndef MANAGERLOGINWIDGET_H
#define MANAGERLOGINWIDGET_H
#include <Enums/widgets.h>
#include <QWidget>

namespace Ui {
class ManagerLoginWidget;
}
class AManager;
class IAdministrator;

class ManagerLoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerLoginWidget(QWidget *parent = nullptr);
    ~ManagerLoginWidget();

private:
    Ui::ManagerLoginWidget *ui;
    void login(const AManager&);
    void login(const IAdministrator&);
signals:
    void changePage(int);
    void sendManager(std::shared_ptr<AManager>);
private slots:
    void on_backButton_clicked();
};

#endif // MANAGERLOGINWIDGET_H
