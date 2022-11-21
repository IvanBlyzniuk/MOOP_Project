#ifndef PUTWITHDRAWWIDGET_H
#define PUTWITHDRAWWIDGET_H

#include <QWidget>

namespace Ui {
class PutWithdrawWidget;
}

class PutWithdrawWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PutWithdrawWidget(QWidget *parent = nullptr);
    ~PutWithdrawWidget();

private:
    Ui::PutWithdrawWidget *ui;
};

#endif // PUTWITHDRAWWIDGET_H
