#ifndef MAINOPTIONSWIDGET_H
#define MAINOPTIONSWIDGET_H
#include <Enums/widgets.h>
#include <QWidget>

namespace Ui {
class MainOptionsWidget;
}
class ICard;


class MainOptionsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainOptionsWidget(QWidget *parent = nullptr);
    ~MainOptionsWidget();

private:
    Ui::MainOptionsWidget *ui;
    std::shared_ptr<ICard> currentCard;
    void cleanOutput();

signals:
    void changePage(int);
private slots:
    void on_exitButton_clicked();
    void setCurrentCard(std::shared_ptr<ICard>);
    void on_withdrawPutButton_clicked();
    void on_sendMoneyButton_clicked();
    void on_changePinButton_clicked();
    void on_checkBalanceButton_clicked();
};

#endif // MAINOPTIONSWIDGET_H
