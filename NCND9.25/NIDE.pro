#-------------------------------------------------
#
# Project created by QtCreator 2020-09-18T19:45:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NIDE
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    replace.cpp \
    highlighter.cpp \
    debugdialog.cpp \
    debugthread.cpp \
    foundline.cpp

HEADERS  += mainwindow.h \
    replace.h \
    highlighter.h \
    debugdialog.h \
    debugthread.h \
    foundline.h

FORMS    += mainwindow.ui \
    replace.ui \
    foundline.ui



RESOURCES += \
    IDEicon.qrc






win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../QScintilla-2.11.5/QScintilla-2.11.5/build-qscintilla-Desktop_Qt_5_12_9_MinGW_32_bit-Debug/release/ -lqscintilla2_qt5d
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../QScintilla-2.11.5/QScintilla-2.11.5/build-qscintilla-Desktop_Qt_5_12_9_MinGW_32_bit-Debug/debug/ -lqscintilla2_qt5d
else:unix: LIBS += -L$$PWD/../../QScintilla-2.11.5/QScintilla-2.11.5/build-qscintilla-Desktop_Qt_5_12_9_MinGW_32_bit-Debug/ -lqscintilla2_qt5d

INCLUDEPATH += $$PWD/../../QScintilla-2.11.5/QScintilla-2.11.5/build-qscintilla-Desktop_Qt_5_12_9_MinGW_32_bit-Debug/debug
DEPENDPATH += $$PWD/../../QScintilla-2.11.5/QScintilla-2.11.5/build-qscintilla-Desktop_Qt_5_12_9_MinGW_32_bit-Debug/debug
INCLUDEPATH += $$PWD/../../QScintilla-2.11.5/QScintilla-2.11.5/Qt4Qt5/
