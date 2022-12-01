#ifndef DEFAULTMANAGERWIDGET_H
#define DEFAULTMANAGERWIDGET_H

#include "Product/Cards/icard.h"
#include <QWidget>

#include <Registrations/aregistrator.h>s

namespace Ui {
class DefaultManagerWidget;
}

class DefaultManagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DefaultManagerWidget(QWidget *parent = nullptr);
    ~DefaultManagerWidget();

private:
    Ui::DefaultManagerWidget *ui;
    std::shared_ptr<ARegistrator<typename ICard>> registrator;
};

#endif // DEFAULTMANAGERWIDGET_H
