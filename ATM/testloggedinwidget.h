#ifndef TESTLOGGEDINWIDGET_H
#define TESTLOGGEDINWIDGET_H


#include <IScreenChangeable.h>
#include <QWidget>

namespace Ui {
class TestLoggedInWidget;
}

class TestLoggedInWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TestLoggedInWidget(QWidget *parent = nullptr);
    ~TestLoggedInWidget();

private:
    QString curUser;
    Ui::TestLoggedInWidget *ui;
public slots:
    void setCurUser(const QString& QString);
};

#endif // TESTLOGGEDINWIDGET_H
