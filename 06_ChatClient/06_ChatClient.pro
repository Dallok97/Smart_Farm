QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 06_ChatClient
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
    I2C_API.cpp \
        main.cpp \
    pca9685.c \
        widget.cpp \
    loginwidget.cpp\
    testthread.cpp

HEADERS += \
    I2C_API.h \
    pca9685.h \
        widget.h \
    loginwidget.h\
    testthread.h

FORMS += \
        widget.ui \
    loginwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../lib/release/ -lwiringPi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../lib/debug/ -lwiringPi
else:unix: LIBS += -L$$PWD/../../../../../lib/ -lwiringPi

INCLUDEPATH += $$PWD/../../../../../usr/include
DEPENDPATH += $$PWD/../../../../../usr/include

RESOURCES += \
    resource.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/lib/release/ -lwiringPi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/lib/debug/ -lwiringPi
else:unix: LIBS += -L$$PWD/../../../../../usr/lib/ -lwiringPi

INCLUDEPATH += $$PWD/../../../../../usr/include
DEPENDPATH += $$PWD/../../../../../usr/include
