#ifndef PRIVILEGEDMANAGERWIDGET_H
#define PRIVILEGEDMANAGERWIDGET_H

#include <QWidget>

namespace Ui {
class PrivilegedManagerWidget;
}

class PrivilegedManagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PrivilegedManagerWidget(QWidget *parent = nullptr);
    ~PrivilegedManagerWidget();

private:
    Ui::PrivilegedManagerWidget *ui;
};

#endif // PRIVILEGEDMANAGERWIDGET_H
