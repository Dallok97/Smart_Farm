
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChatServer
TEMPLATE = app

SOURCES += main.cpp\
    I2C_API.cpp \
    pca9685.c \
        widget.cpp \
    chatServer.cpp\
    GPIO_PWM_API.cpp

HEADERS  += widget.h \
    I2C_API.h \
    chatserver.h\
    GPIO_PWM_API.h\
    pca9685.h

FORMS    += widget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/lib/release/ -lwiringPi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/lib/debug/ -lwiringPi
else:unix: LIBS += -L$$PWD/../../../../../usr/lib/ -lwiringPi

INCLUDEPATH += $$PWD/../../../../../usr/include
DEPENDPATH += $$PWD/../../../../../usr/include
