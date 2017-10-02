#include <QtCore>
#include <iostream>
#include <string>
#include "account.h"
#include "transaction.h"

namespace cmd{

    la::Transaction addTransaction(){
        std::string m_name;

        double m_amount = 0;

        std::cout << "\e[1mAdding new transaction\e[0m\n"
                  << "\nPlease input name of transaction: ";
        std::cin >> m_name;

        std::cout << "Now lets type amount: ";
        std::cin >> m_amount;
        m_amount *= 100;

        return la::Transaction((int)m_amount,m_name);
    }
}

int main(int argc, char *argv[]){
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("my belka");
    QCoreApplication::setApplicationVersion("0.1");
    QCoreApplication::setOrganizationName("Leinnan");

    QSettings settings("MyBelka","Leinnan");

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


    la::Account test_account;

    if(parser.isSet(sourceOption)){
        settings.setValue("json_path",parser.value(sourceOption));
    }
    std::string json_path = settings.value("json_path","test.json").toString().toStdString();

    test_account.readFromJson(json_path);

    if(parser.isSet(addOption)){
        test_account.addTransaction(cmd::addTransaction());
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

    test_account.setCompactFormat( settings.value( "compactJSON", false ).toBool() );


    test_account.sortTransactions();
    test_account.saveToJson(json_path);
    test_account.showTransactions(true);
    test_account.showAccountBalance();
    return 0;
}
