#ifndef CHANGEPINWIDGET_H
#define CHANGEPINWIDGET_H

#include <QWidget>

namespace Ui {
class ChangePinWidget;
}

class ChangePinWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePinWidget(QWidget *parent = nullptr);
    ~ChangePinWidget();

private:
    Ui::ChangePinWidget *ui;
};

#endif // CHANGEPINWIDGET_H
