#ifndef PRIVILEGEDMANAGERWIDGET_H
#define PRIVILEGEDMANAGERWIDGET_H

#include <QWidget>

namespace Ui {
class PrivilegedManagerWidget;
}

class AManager;

class PrivilegedManagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PrivilegedManagerWidget(QWidget *parent = nullptr);
    ~PrivilegedManagerWidget();

private:
    Ui::PrivilegedManagerWidget *ui;
    std::shared_ptr<AManager> currentManager;
signals:
    void changePage(int);

private slots:
    void setCurrentManager(std::shared_ptr<AManager>);
};

#endif // PRIVILEGEDMANAGERWIDGET_H
