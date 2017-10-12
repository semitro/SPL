TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += include/

HEADERS += include/list/*.h

SOURCES += main.c \
    src/list/list.c \
    src/list/list_functions.c \
    src/list/list_serialize.c


include(deployment.pri)
qtcAddDeployment()

