#ifndef MAINOPTIONSWIDGET_H
#define MAINOPTIONSWIDGET_H
#include <Enums/widgets.h>
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
signals:
    void changePage(int);
private slots:
    void on_exitButton_clicked();
};

#endif // MAINOPTIONSWIDGET_H
