QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    colnumber.cpp \
    color.cpp \
    colorform.cpp \
    database.cpp \
    high_cost.cpp \
    knife.cpp \
    knifeform.cpp \
    main.cpp \
    mainwindow.cpp \
    order.cpp

HEADERS += \
    colnumber.h \
    color.h \
    colorform.h \
    database.h \
    high_cost.h \
    knife.h \
    knifeform.h \
    mainwindow.h \
    order.h

FORMS += \
    colnumber.ui \
    color.ui \
    colorform.ui \
    high_cost.ui \
    knife.ui \
    knifeform.ui \
    mainwindow.ui \
    order.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Images.qrc

DISTFILES +=
