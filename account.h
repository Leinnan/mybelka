#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "transaction.h"
#include "category.h"
#include <vector>
#include <QDateTime>
#include <QtCore>
#include <string>

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
    void readFromJson(std::string);
    void saveToJson(std::string);
    void setCompactFormat(bool value = true);

private:

    std::vector<la::Transaction> transactions;
    int balance = 0;
    bool compactFormat;

};
}

#endif // ACCOUNT_H
