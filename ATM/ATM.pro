QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DB/db.cpp \
    Transactions/transaction.cpp \
    Transactions/transactionmanager.cpp \
    Product/Managers/privilegedmanager.cpp \
    Product/Managers/standardmanager.cpp \
    Widgets/changepinwidget.cpp \
    Widgets/defaultmanagerwidget.cpp \
    Widgets/loginwidget.cpp \
    main.cpp \
    Widgets/mainoptionswidget.cpp \
    Widgets/mainwindow.cpp \
    Widgets/managerloginwidget.cpp \
    Widgets/privilegedmanagerwidget.cpp \
    Widgets/putwithdrawwidget.cpp \
    Widgets/transactionwidget.cpp

HEADERS += \
    DB/db.h \
    DB/iserializer.h \
    Enums/widgets.h \
    Exceptions/AlreadyExistsException.h \
    Exceptions/DoesntExistException.h \
    Exceptions/NotEnoughMoneyException.h \
    Exceptions/inputexception.h \
    Login/cardloginagent.h \
    Login/iloginagent.h \
    Login/managerloginagent.h \
    Product/Cards/creditcard.h \
    Product/DebitCard.h \
    Product/Factories/AdministratorFactory.h \
    Product/Factories/CardFactory.h \
    Product/Factories/IFactory.h \
    Product/Factories/ManagerFactory.h \
    Product/Factories/ifactory.h \
    Product/IProduct.h \
    Product/Managers/aadministrator.h \
    Product/Managers/amanager.h \
    Product/Managers/privilegedmanager.h \
    Product/Managers/standardmanager.h \
    Product/ProductInfo.h \
    Product/icard.h \
    Registrations/RegistratorTypedefs.h \
    Registrations/aregistrator.h \
    Registrations/cardregistrator.h \
    Registrations/managerregistrator.h \
    Transactions/transaction.h \
    Transactions/transactionmanager.h \
    Utils/casting.h \
    Widgets/changepinwidget.h \
    Widgets/defaultmanagerwidget.h \
    Widgets/loginwidget.h \
    Widgets/mainoptionswidget.h \
    Widgets/mainwindow.h \
    Widgets/managerloginwidget.h \
    Widgets/privilegedmanagerwidget.h \
    Widgets/putwithdrawwidget.h \
    Widgets/transactionwidget.h

FORMS += \
    Views/changepinwidget.ui \
    Views/defaultmanagerwidget.ui \
    Views/loginwidget.ui \
    Views/mainoptionswidget.ui \
    Views/mainwindow.ui \
    Views/managerloginwidget.ui \
    Views/privilegedmanagerwidget.ui \
    Views/putwithdrawwidget.ui \
    Views/transactionwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
