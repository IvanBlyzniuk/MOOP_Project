#ifndef DEFAULTMANAGERWIDGET_H
#define DEFAULTMANAGERWIDGET_H

#include <QWidget>

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
};

#endif // DEFAULTMANAGERWIDGET_H
