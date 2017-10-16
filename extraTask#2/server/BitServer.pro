TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


INCLUDEPATH += include/

HEADERS += include/list/*.h \
    include/server/listener.h

SOURCES += main.c \
    src/list/list.c \
    src/list/list_functions.c \
    src/list/list_serialize.c \
    src/server/listener.c


include(deployment.pri)
qtcAddDeployment()

QMAKE_CFLAGS += -Wall -Wextra -std=c99 -pedantic-errors -lpthread
