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
    void                            applySettings( QSettings* );
    void                            showTransactions( bool divideByDays = false );
    void                            displayTransaction( la::Transaction&, bool );
    void                            addTransaction();
    void                            showAccountBalance();
    void                            runMenu();

private:
    void                            showMenu();

    std::shared_ptr<la::Account>    accountPtr;
    QSettings                       *m_settings;
    QTextStream                     out;
};

}
#endif // CLIMANAGER_H
