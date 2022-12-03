#ifndef TRANSACTIONWIDGET_H
#define TRANSACTIONWIDGET_H
#include <Enums/widgets.h>
#include <QWidget>

namespace Ui {
class TransactionWidget;
}
class TransactionManager;

class ISerializer;

class ICard;

class TransactionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TransactionWidget(std::shared_ptr<ISerializer>,QWidget *parent = nullptr);
    ~TransactionWidget();

private:
    Ui::TransactionWidget *ui;
    std::shared_ptr<ICard> currentCard;
    std::shared_ptr<ISerializer> serializer;

signals:
    void changePage(int);
private slots:
    void setCurrentCard(std::shared_ptr<ICard>);
    void on_backButton_clicked();
    void on_sendTransactionButton_clicked();

private:
    bool check();
};

#endif // TRANSACTIONWIDGET_H
