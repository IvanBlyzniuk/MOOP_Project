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
class AAdministrator;
class ISerializer;

class DefaultManagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DefaultManagerWidget(std::shared_ptr<ISerializer>,QWidget *parent = nullptr);
    ~DefaultManagerWidget();

private:
    Ui::DefaultManagerWidget *ui;
    std::shared_ptr<ARegistrator<ICard>> registrator;
    std::shared_ptr<AManager> currentManager;
    void goBack(AManager&);
    //void goBack(const AAdministrator&);
    bool checkAdd();
    bool checkDelete();

signals:
    void changePage(int);
private slots:
    void on_backButton_clicked();
    void setCurrentManager(std::shared_ptr<AManager>);
    void on_deleteCardButton_clicked();
    void on_addCardButton_clicked();
};

#endif // DEFAULTMANAGERWIDGET_H
