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
    std::vector<la::Transaction>    getTransactions(){ return m_transactions; }
    int                             getBalance();
    const int                       getTransactionIndexByUid(const QUuid& uid);
    void                            replaceTransactionWithUid(const QUuid& uid, const la::Transaction& transaction);
    void                            removeTransaction(const int& index);

private:

    std::vector<la::Transaction>    m_transactions;
    int                             balance;
    bool                            compactFormat;
    QString                         fileTimestamp;
    QString                         deviceId;

};
}

#endif // ACCOUNT_H
