#ifndef CHANGEPINWIDGET_H
#define CHANGEPINWIDGET_H
#include <Enums/widgets.h>
#include <QWidget>

namespace Ui {
class ChangePinWidget;
}

class ICard;

class ISerializer;

class ChangePinWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePinWidget(std::shared_ptr<ISerializer>,QWidget *parent = nullptr);
    ~ChangePinWidget();

private:
    Ui::ChangePinWidget *ui;
    std::shared_ptr<ICard> currentCard;
    std::shared_ptr<ISerializer> serializer;
    bool check();
    void cleanInput();
    void cleanOutput();
signals:
    void changePage(int);
private slots:
    void setCurrentCard(std::shared_ptr<ICard>);
    void on_goBackButton_clicked();
    void on_changePinButton_clicked();
};

#endif // CHANGEPINWIDGET_H
