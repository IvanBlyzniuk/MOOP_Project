#ifndef PRIVILEGEDMANAGERWIDGET_H
#define PRIVILEGEDMANAGERWIDGET_H
#include "Registrations/aregistrator.h"
#include <QWidget>

namespace Ui {
class PrivilegedManagerWidget;
}

class AManager;
class ISerializer;

class PrivilegedManagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PrivilegedManagerWidget(std::shared_ptr<ISerializer>,QWidget *parent = nullptr);
    ~PrivilegedManagerWidget();

private:
    Ui::PrivilegedManagerWidget *ui;
    std::shared_ptr<AManager> currentManager;
    std::shared_ptr<ARegistrator<AManager>> registrator;
    bool checkDelete();
    bool checkAdd();
    void cleanInput();
    void cleanOutput();
signals:
    void changePage(int);

private slots:
    void setCurrentManager(std::shared_ptr<AManager>);
    void on_deleteManagerButton_clicked();
    void on_addManagerButton_clicked();
    void on_backButton_clicked();
    void on_redactorModeButton_clicked();
};

#endif // PRIVILEGEDMANAGERWIDGET_H
