#ifndef MANAGERLOGINWIDGET_H
#define MANAGERLOGINWIDGET_H

#include <QWidget>

namespace Ui {
class ManagerLoginWidget;
}

class ManagerLoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerLoginWidget(QWidget *parent = nullptr);
    ~ManagerLoginWidget();

private:
    Ui::ManagerLoginWidget *ui;
};

#endif // MANAGERLOGINWIDGET_H
