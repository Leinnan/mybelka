QT += core

CONFIG += c++11 ui_gfx

DESTDIR=build #Target file directory
OBJECTS_DIR=build/generated #Intermediate object files directory
MOC_DIR=build/generated #Intermediate moc files directory

TEMPLATE = app

SOURCES += src/main.cpp \
    src/category.cpp \
    src/transaction.cpp \
    src/account.cpp \
    src/addtransactionwindow.cpp


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    src/category.h \
    src/transaction.h \
    src/account.h \
    src/climanager.h \
    src/addtransactionwindow.h

ui_gfx {
    QT += gui
    CONFIG -= ui_cli
    DEFINES += GUI_MODE
    QT += widgets
    target = mybelka_ui
    SOURCES += src/uimanager.cpp
    HEADERS += src/uimanager.h
}

ui_cli {
    CONFIG += console
    CONFIG -= app_bundle ui_gfx
    TARGET = mybelka
    SOURCES += src/climanager.cpp
    HEADERS += src/climanager.h
}
