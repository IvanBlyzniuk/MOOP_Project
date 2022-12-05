#ifndef PUTWITHDRAWWIDGET_H
#define PUTWITHDRAWWIDGET_H
#include <Enums/widgets.h>
#include <QWidget>

namespace Ui {
class PutWithdrawWidget;
}
class TransactionManager;

class ISerializer;

class ICard;

class PutWithdrawWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PutWithdrawWidget(std::shared_ptr<ISerializer>,QWidget *parent = nullptr);
    ~PutWithdrawWidget();

private:
    Ui::PutWithdrawWidget *ui;
    std::shared_ptr<ICard> currentCard;
    std::shared_ptr<ISerializer> serializer;
    bool check();
    void cleanInput();
    void cleanOutput();
signals:
    void changePage(int);
private slots:
    void setCurrentCard(std::shared_ptr<ICard>);
    void on_backButton_clicked();
    void on_putMoneyButton_clicked();
    void on_withdrawMoneyButton_clicked();
};

#endif // PUTWITHDRAWWIDGET_H
