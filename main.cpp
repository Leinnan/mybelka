#include <QtCore>
#include <iostream>
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

    parser.process(app);



    la::Account test_account;
    la::Transaction test("22.11.2014 11:14",345345,"Nowa");

    test_account.readFromJson("test.json");

    test_account.addTransaction(test);
    test_account.saveToJson("test_2.json");
    test_account.showTransactions();
    test_account.showAccountBalance();
    return 0;
}
