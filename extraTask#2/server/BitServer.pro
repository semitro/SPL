TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


INCLUDEPATH += include/

HEADERS += include/list/*.h \
    include/server/listener.h \
    include/server/client_handler.h \
    include/server/connection.h \
    include/server/server.h \
    include/list_keeper.h \
    include/execution/strange_runner.h \
    include/list/list_containing_functions.h \
    include/task_queue.h

SOURCES += main.c \
    src/list/list.c \
    src/list/list_functions.c \
    src/list/list_serialize.c \
    src/server/listener.c \
    src/server/client_handler.c \
    src/server/connection.c \
    src/server/server.c \
    src/list_keeper.c \
    src/task_queue.c \
    src/execution/strange_runner.c \





include(deployment.pri)
qtcAddDeployment()

QMAKE_CFLAGS += -Wall -Wextra -std=gnu99 -pedantic
QMAKE_LFLAGS += -pthread

DISTFILES +=
