TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c
INCLUDEPATH += include/

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    image.h \
    image_loader.h

