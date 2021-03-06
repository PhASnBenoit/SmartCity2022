#-------------------------------------------------
#
# Project created by QtCreator 2020-12-02T21:03:24
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartCity2022
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    cplaces.cpp \
        main.cpp \
    cgestionmaquette.cpp \
    cparking.cpp \
    cintersection.cpp \
    ceclairage.cpp \
    czdc.cpp \
    ci2c.cpp \
    cecran.cpp \
    cconfig.cpp \
    capp.cpp \
    cmonserveurtcp.cpp \
    cmodbustcp.cpp \
    cgererserveur.cpp \
    cgererclient.cpp \
    cihm.cpp \
    cbdd.cpp

HEADERS += \
    cgestionmaquette.h \
    cparking.h \
    cintersection.h \
    ceclairage.h \
    cplaces.h \
    czdc.h \
    ci2c.h \
    cecran.h \
    cconfig.h \
    capp.h \
    cmonserveurtcp.h \
    cmodbustcp.h \
    cgererserveur.h \
    cgererclient.h \
    cihm.h \
    cbdd.h

FORMS += \
    cihm.ui

OTHER_FILES += \
    ../SmartCity.ini \

DISTFILES += \
    ../SmartCity.ini \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
