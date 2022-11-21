#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>

namespace Ui {
class BaseWidget;
}

class BaseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BaseWidget(QWidget *parent = nullptr);
    ~BaseWidget();

private:
    Ui::BaseWidget *ui;

signals:
    void changePage(int);
};


#endif // BASEWIDGET_H
