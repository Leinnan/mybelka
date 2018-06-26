QT += core

CONFIG += c++11 

DESTDIR=build #Target file directory
OBJECTS_DIR=build/generated #Intermediate object files directory
MOC_DIR=build/generated #Intermediate moc files directory

TEMPLATE = app

TRANSLATIONS += misc/translation_pl.ts

SOURCES += src/main.cpp \
    src/category.cpp \
    src/transaction.cpp \
    src/account.cpp \
    src/edittransactionwindow.cpp

DEFINES += QT_DEPRECATED_WARNINGS

target.path = $$PREFIX/bin

unix {
    isEmpty(PREFIX) {
        PREFIX = /usr/local
    }

    target.path = $$PREFIX/bin

    shortcutfiles.files = misc/mybelka.desktop
    shortcutfiles.path = $$PREFIX/share/applications/
    data.files += misc/mybelka.xpm
    data.files += misc/translation_pl.qm
    data.path = $$PREFIX/share/pixmaps/

    INSTALLS += shortcutfiles
    INSTALLS += data
}

INSTALLS += target

HEADERS += \
    src/category.h \
    src/transaction.h \
    src/account.h \
    src/edittransactionwindow.h

ui_gfx {
    QT += gui
    CONFIG -= ui_cli
    DEFINES += GUI_MODE
    QT += widgets
    SOURCES += src/uimanager.cpp \
               src/addtransactionwindow.cpp \
               src/infobar.cpp
    HEADERS += src/uimanager.h \
               src/infobar.h \
               src/addtransactionwindow.h 
}

ui_cli {
    CONFIG += console
    CONFIG -= app_bundle ui_gfx
    TARGET = mybelka
    SOURCES += src/climanager.cpp
    HEADERS += src/climanager.h 
}
