#include <QtCore>
#include <QUuid>
#include <iostream>
#include <string>
#include "account.h"
#include "transaction.h"
#include "src/climanager.h"

int main(int argc, char *argv[]){
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("my belka");
    QCoreApplication::setApplicationVersion("0.1");
    QCoreApplication::setOrganizationName("Leinnan");

    QSettings settings("MyBelka","Leinnan");
    la::CliManager logicManager;

//    QString settings_file = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);

//    std::cout << settings_file.toStdString();
    QCommandLineParser parser;
    parser.setApplicationDescription("My simple accounting system, still very early version, written in C++ with QTCore");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption sourceOption(QStringList() << "s" << "source",
            QCoreApplication::translate("main", "Read from <file>."),
            QCoreApplication::translate("main", "file"));
    parser.addOption(sourceOption);

    QCommandLineOption addOption(QStringList() << "a" << "add-new",
            QCoreApplication::translate("main", "Add new transaction."));
    parser.addOption(addOption);

    QCommandLineOption compactOption(QStringList() << "c" << "compact",
            QCoreApplication::translate("main", "Set JSON file to be more compact."));
    parser.addOption(compactOption);

    QCommandLineOption intendedOption(QStringList() << "r" << "readable",
            QCoreApplication::translate("main", "Set JSON file to be more readable."));
    parser.addOption(intendedOption);


    parser.process(app);
    logicManager.applySettings( settings );

    if(parser.isSet(sourceOption)){
        settings.setValue("json_path",parser.value(sourceOption));
    }

    if(parser.isSet(addOption)){
        logicManager.addTransaction();
    }

    if( parser.isSet( intendedOption ) && parser.isSet( compactOption ))
    {
        std::cout << "You have choose both readable and compact.\nYou can too choose only one, aborting" << std::endl;
        return 0;
    }
    else
    {
        if( parser.isSet( compactOption ) )
            settings.setValue("compactJSON", true);

        if( parser.isSet( intendedOption ) )
            settings.setValue("compactJSON", false);
    }

    logicManager.showTransactions( true );
    logicManager.showAccountBalance();

    return 0;
}
