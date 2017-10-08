#ifndef CLIMANAGER_H
#define CLIMANAGER_H
#include <src/account.h>

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
    void addTransaction();
    void showAccountBalance();

private:
    std::shared_ptr<la::Account> accountPtr;
};

}
#endif // CLIMANAGER_H
