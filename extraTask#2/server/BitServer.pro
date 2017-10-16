TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


INCLUDEPATH += include/

HEADERS += include/list/*.h \
    include/server/listener.h \
    include/server/client_handler.h \
    include/server/connection.h \
    include/server/server.h

SOURCES += main.c \
    src/list/list.c \
    src/list/list_functions.c \
    src/list/list_serialize.c \
    src/server/listener.c \
    src/server/client_handler.c \
    src/server/connection.c \
    src/server/server.c


include(deployment.pri)
qtcAddDeployment()

QMAKE_CFLAGS += -Wall -Wextra -std=c99 -pedantic-errors
QMAKE_LFLAGS += -pthread

DISTFILES +=
