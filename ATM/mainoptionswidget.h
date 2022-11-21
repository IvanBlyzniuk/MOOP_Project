#ifndef MAINOPTIONSWIDGET_H
#define MAINOPTIONSWIDGET_H

#include <QWidget>

namespace Ui {
class MainOptionsWidget;
}

class MainOptionsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainOptionsWidget(QWidget *parent = nullptr);
    ~MainOptionsWidget();

private:
    Ui::MainOptionsWidget *ui;
};

#endif // MAINOPTIONSWIDGET_H
