QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Chess-Core/release/ -lChess-Core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Chess-Core/debug/ -lChess-Core
else:unix: LIBS += -L$$PWD/../../Chess-Core/ -lChess-Core

INCLUDEPATH += $$PWD/../../Chess-Core/src
DEPENDPATH += $$PWD/../../Chess-Core/src
INCLUDEPATH += $$PWD/../../Chess-Core/src/pieces
DEPENDPATH += $$PWD/../../Chess-Core/src/pieces
