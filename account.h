#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "transaction.h"
#include "category.h"
#include <vector>
#include <QDateTime>

namespace la {

class Account
{
public:
    Account();
    void showTransactions();
    void addTransaction(la::Transaction);
    void sortTransactions();
    void showAccountBalance();
    void updateAccountBalance();
private:
    std::vector<la::Transaction> transactions;
    int balance = 0;

};
}

#endif // ACCOUNT_H
