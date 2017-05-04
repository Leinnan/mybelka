#include <QtCore>
#include <iostream>
#include <string>
#include "account.h"
#include "transaction.h"

int main(int argc, char *argv[]){
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("my belka");
    QCoreApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("My simple accounting system, still very early version, written in C++ with QTCore");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption sourceOption(QStringList() << "s" << "source",
            QCoreApplication::translate("main", "Read from <file>."),
            QCoreApplication::translate("main", "file"));
    parser.addOption(sourceOption);


    parser.process(app);


    std::string json_path = "test.json";
    la::Account test_account;
    la::Transaction test("22.11.2014 11:14",345345,"Nowa");

    if(parser.isSet(sourceOption))
        json_path = parser.value(sourceOption).toStdString();


    test_account.readFromJson(json_path);
    test_account.sortTransactions();
    test_account.saveToJson(json_path);
    test_account.showTransactions();
    test_account.showAccountBalance();
    return 0;
}
