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
    src/addtransactionwindow.cpp \
    src/infobar.cpp

DEFINES += QT_DEPRECATED_WARNINGS

unix {
    isEmpty(PREFIX) {
        PREFIX = /usr/local
    }

    target.path = $$PREFIX/bin

    shortcutfiles.files = misc/mybelka.desktop
    shortcutfiles.path = $$PREFIX/share/applications/
    data.files += misc/mybelka.xpm
    data.path = $$PREFIX/share/pixmaps/

    INSTALLS += shortcutfiles
    INSTALLS += data
}

INSTALLS += target

HEADERS += \
    src/category.h \
    src/transaction.h \
    src/account.h \
    src/climanager.h \
    src/addtransactionwindow.h \
    src/infobar.h

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
