#include <QtCore>
#include <iostream>
#include "account.h"
#include "transaction.h"

int main(int argc, char *argv[]){
    la::Account test_account;


    test_account.readFromJson("test.json");
    test_account.showTransactions();
    test_account.showAccountBalance();
    return 0;
}
