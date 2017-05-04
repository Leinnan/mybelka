#include <QtCore>
#include <iostream>
#include <string>
#include "account.h"
#include "transaction.h"

namespace cmd{

    la::Transaction addTransaction(){
        std::string m_name;

        int m_amount = 0;

        std::cout << "\e[1mAdding new transaction\e[0m\n"
                  << "\nPlease input name of transaction: ";
        std::cin >> m_name;

        std::cout << "Now lets type amount: ";
        std::cin >> m_amount;
        m_amount *= 100;

        return la::Transaction(m_amount,m_name);
    }
}

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

    QCommandLineOption addOption(QStringList() << "a" << "add-new",
            QCoreApplication::translate("main", "Add new transaction."));
    parser.addOption(addOption);


    parser.process(app);


    std::string json_path = "test.json";
    la::Account test_account;

    if(parser.isSet(sourceOption))
        json_path = parser.value(sourceOption).toStdString();


    test_account.readFromJson(json_path);

    if(parser.isSet(addOption)){
        test_account.addTransaction(cmd::addTransaction());
    }


    test_account.sortTransactions();
    test_account.saveToJson(json_path);
    test_account.showTransactions();
    test_account.showAccountBalance();
    return 0;
}
