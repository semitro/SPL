TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


include(deployment.pri)
qtcAddDeployment()


INCLUDEPATH += include/

HEADERS += include/*.h \
    include/connection/connection.h

SOURCES += src/main.c \
           src/connection/connection.c \
