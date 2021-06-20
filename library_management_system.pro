#-------------------------------------------------
#
# Project created by QtCreator 2021-05-30T20:17:48
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = library_management_system
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATet_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATet_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    loginwindow.cpp \
    querybookwindow.cpp \
    queryauthorwindow.cpp \
    queryuserwindow.cpp \
    borrowbookwindow.cpp \
    returnbookwindow.cpp \
    registeruserwindow.cpp \
    deleteuserwindow.cpp \
    addbookwindow.cpp \
    delbookwindow.cpp \
    editpasswordwindow.cpp \
    editbookwindow.cpp

HEADERS += \
        mainwindow.h \
    loginwindow.h \
    querybookwindow.h \
    queryauthorwindow.h \
    queryuserwindow.h \
    borrowbookwindow.h \
    returnbookwindow.h \
    registeruserwindow.h \
    deleteuserwindow.h \
    addbookwindow.h \
    delbookwindow.h \
    editpasswordwindow.h \
    editbookwindow.h

FORMS += \
        mainwindow.ui \
    loginwindow.ui \
    querybookwindow.ui \
    queryauthorwindow.ui \
    queryuserwindow.ui \
    borrowbookwindow.ui \
    returnbookwindow.ui \
    registeruserwindow.ui \
    deleteuserwindow.ui \
    addbookwindow.ui \
    delbookwindow.ui \
    editpasswordwindow.ui \
    editbookwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
