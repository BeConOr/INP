QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Struck.cpp \
    arc.cpp \
    arc_wid.cpp \
    bound.cpp \
    circ_wid.cpp \
    circle.cpp \
    creategroup.cpp \
    currtask.cpp \
    data.cpp \
    elip_wid.cpp \
    ellipse.cpp \
    figure.cpp \
    geometry.cpp \
    line.cpp \
    main.cpp \
    mainwindow.cpp \
    mesh.cpp \
    paintscene.cpp \
    rec_wid.cpp \
    units.cpp \
    view.cpp

HEADERS += \
    Struck.h \
    arc.h \
    arc_wid.h \
    bound.h \
    circ_wid.h \
    circle.h \
    creategroup.h \
    currtask.h \
    data.h \
    elip_wid.h \
    ellipse.h \
    figure.h \
    geometry.h \
    line.h \
    mainwindow.h \
    mesh.h \
    paintscene.h \
    rec_wid.h \
    units.h \
    view.h

FORMS += \
    arc_wid.ui \
    bound.ui \
    circ_wid.ui \
    creategroup.ui \
    data.ui \
    elip_wid.ui \
    geometry.ui \
    mainwindow.ui \
    mesh.ui \
    rec_wid.ui \
    units.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/copy.png \
    images/cut.png \
    images/new.png \
    images/open.png \
    images/paste.png \
    images/save.png

RESOURCES += \
    GUI_PSN.qrc