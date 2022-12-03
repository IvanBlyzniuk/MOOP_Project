#ifndef DEFAULTMANAGERWIDGET_H
#define DEFAULTMANAGERWIDGET_H
#include <Enums/widgets.h>
#include "Product/Cards/icard.h"
#include <QWidget>
#include <Registrations/aregistrator.h>



namespace Ui {
class DefaultManagerWidget;
}

class AManager;
class IAdministrator;

class DefaultManagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DefaultManagerWidget(QWidget *parent = nullptr);
    ~DefaultManagerWidget();

private:
    Ui::DefaultManagerWidget *ui;
    std::shared_ptr<ARegistrator<ICard>> registrator;
    std::shared_ptr<AManager> currentManager;
    void goBack(const AManager&);
    void goBack(const IAdministrator&);


signals:
    void changePage(int);
private slots:
    void on_backButton_clicked();
    void setCurrentManager(std::shared_ptr<AManager>);
};

#endif // DEFAULTMANAGERWIDGET_H
