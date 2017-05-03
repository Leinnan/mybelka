#include <QtCore>
#include <iostream>
#include "account.h"
#include "transaction.h"

int main(int argc, char *argv[]){
    la::Account test_account;
    la::Transaction tran_first(-299999,"Flat");
    la::Transaction tran_second(20051,"Old laptop");
    la::Transaction tran_third("21.09.2016 17:23",450000,"Job");

    test_account.addTransaction(tran_first);
    test_account.addTransaction(tran_second);
    test_account.addTransaction(tran_third);

    test_account.showTransactions();
    test_account.showAccountBalance();
    return 0;
}
