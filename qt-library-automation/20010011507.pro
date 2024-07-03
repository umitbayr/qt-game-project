# ÜMİT BAYRAM 20010011507

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    books_action.cpp \
    main.cpp \
    mainwindow.cpp \
    member.cpp \
    oduncalma.cpp \
    teslim.cpp

HEADERS += \
    books_action.h \
    mainwindow.h \
    member.h \
    oduncalma.h \
    teslim.h

FORMS += \
    books_action.ui \
    mainwindow.ui \
    member.ui \
    oduncalma.ui \
    teslim.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc





