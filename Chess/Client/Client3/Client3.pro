QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    main.cpp \
    mainwindow.cpp \
    gamewindow.cpp

HEADERS += \
    client.h \
    mainwindow.h \
    gamewindow.h

FORMS += \
    gamewindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Chess-Core/release/ -lChess-Core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Chess-Core/bin/ -lChess-Core

INCLUDEPATH += $$PWD/../../Chess-Core/bin
DEPENDPATH += $$PWD/../../Chess-Core/bin

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../Chess-Core/release/libChess-Core.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../Chess-Core/bin/libChess-Core.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../Chess-Core/release/Chess-Core.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../Chess-Core/bin/Chess-Core.lib
