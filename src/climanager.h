#ifndef CLIMANAGER_H
#define CLIMANAGER_H
#include <src/account.h>
#include <src/transaction.h>

#include <QtCore>
#include <memory>

namespace la
{

class CliManager
{
public:
    CliManager();
    void applySettings( QSettings& );
    void showTransactions( bool divideByDays = false );
    void displayTransaction( la::Transaction&, bool );
    void addTransaction();
    void showAccountBalance();

private:
    std::shared_ptr<la::Account> accountPtr;
};

}
#endif // CLIMANAGER_H
