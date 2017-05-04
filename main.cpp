#include <QtCore>
#include <iostream>
#include "account.h"
#include "transaction.h"

int main(int argc, char *argv[]){
    la::Account test_account;
    la::Transaction test("22.11.2014 11:14",345345,"Nowa");

    test_account.readFromJson("test.json");

    test_account.addTransaction(test);
    test_account.saveToJson("test_2.json");
    test_account.showTransactions();
    test_account.showAccountBalance();
    return 0;
}
