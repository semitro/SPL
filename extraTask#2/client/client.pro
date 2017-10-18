TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


include(deployment.pri)
qtcAddDeployment()


INCLUDEPATH += include/

HEADERS += include/*.h \
    include/connection/connection.h \
    include/list/*.h \

SOURCES += src/main.c \
           src/connection/connection.c \
           src/list/list.c \
           src/list/list_functions.c \
           src/list/list_serialize.c \