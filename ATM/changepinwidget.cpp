#include "changepinwidget.h"
#include "ui_changepinwidget.h"

ChangePinWidget::ChangePinWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePinWidget)
{
    ui->setupUi(this);
}

ChangePinWidget::~ChangePinWidget()
{
    delete ui;
}
