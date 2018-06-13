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
    void                            addTransaction(la::Transaction);
    void                            sortTransactions();

    void                            updateAccountBalance();

    void                            readFromJson();
    void                            saveToJson();

    void                            setCompactFormat(bool value = true);
    QString                         getDeviceId() const;
    void                            setDeviceId(const QString &value);
    std::vector<la::Transaction>    getTransactions(){ return transactions; };
    int                             getBalance();

private:

    std::vector<la::Transaction>    transactions;
    int                             balance;
    bool                            compactFormat;
    QString                         fileTimestamp;
    QString                         deviceId;

};
}

#endif // ACCOUNT_H
