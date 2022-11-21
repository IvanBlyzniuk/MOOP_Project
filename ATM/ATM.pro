QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    changepinwidget.cpp \
    defaultmanagerwidget.cpp \
    loginwidget.cpp \
    main.cpp \
    mainoptionswidget.cpp \
    mainwindow.cpp \
    managerloginwidget.cpp \
    privilegedmanagerwidget.cpp \
    putwithdrawwidget.cpp \
    testloggedinwidget.cpp \
    transactionwidget.cpp

HEADERS += \
    changepinwidget.h \
    defaultmanagerwidget.h \
    loginwidget.h \
    mainoptionswidget.h \
    mainwindow.h \
    managerloginwidget.h \
    privilegedmanagerwidget.h \
    putwithdrawwidget.h \
    testloggedinwidget.h \
    transactionwidget.h

FORMS += \
    changepinwidget.ui \
    defaultmanagerwidget.ui \
    loginwidget.ui \
    mainoptionswidget.ui \
    mainwindow.ui \
    managerloginwidget.ui \
    privilegedmanagerwidget.ui \
    putwithdrawwidget.ui \
    testloggedinwidget.ui \
    transactionwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target