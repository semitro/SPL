TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    image_loader.c \
    transform.c \
    main_window.c

INCLUDEPATH += include/

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    image.h \
    image_loader.h \
    transform.h \
    main_window.h


QMAKE_CFLAGS += -Wall -Wextra -std=gnu99 -pedantic
LIBS += -lX11

QMAKE_CC = gcc
DISTFILES +=

