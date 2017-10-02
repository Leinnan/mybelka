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
    void                            showTransactions( bool divideByDays );
    void                            addTransaction(la::Transaction);
    void                            sortTransactions();

    void                            showAccountBalance();
    void                            updateAccountBalance();

    void                            readFromJson(std::string);
    void                            saveToJson(std::string);

    void                            setCompactFormat(bool value = true);
    QString                         getDeviceId() const;
    void                            setDeviceId(const QString &value);

private:

    std::vector<la::Transaction>    transactions;
    int                             balance;
    bool                            compactFormat;
    QString                         fileTimestamp;
    QString                         deviceId;

};
}

#endif // ACCOUNT_H
