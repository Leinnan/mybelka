#include "src/climanager.h"

// external
#include <iostream>

la::CliManager::CliManager()
{
    accountPtr = std::make_shared<la::Account>();
}

void la::CliManager::applySettings( QSettings& settings )
{

    std::string json_path = settings.value("json_path","test.json").toString().toStdString();

    accountPtr->readFromJson(json_path);
    accountPtr->setCompactFormat( settings.value( "compactJSON", false ).toBool() );


    accountPtr->sortTransactions();
    accountPtr->saveToJson(json_path);
//    showTransactions(true);
//    accountPtr->showAccountBalance();
}

void la::CliManager::showTransactions( bool divideByDays /*= false*/ )
{
    std::vector<la::Transaction> transactions = accountPtr->getTransactions();

    std::cout.precision( 2 );
    std::cout << std::fixed;
    if( divideByDays )
    {
        QString lastTransactionDate = "none";
        QString newTransactionDate = "none";
        for( la::Transaction &f_transaction : transactions )
        {
            newTransactionDate = f_transaction.getDate().toString("dd.MM.yyyy");
            if(lastTransactionDate != newTransactionDate)
            {
                std::cout << "\e[1m" << newTransactionDate.toStdString() << "\e[0m\n";
            }
            f_transaction.display( false );
            lastTransactionDate = newTransactionDate;
        }
    }
    else
    {
        for(la::Transaction f_transaction : transactions)
            f_transaction.display();
    }
}

void la::CliManager::addTransaction()
{

    std::string m_name;

    double m_amount = 0;

    std::cout << "\e[1mAdding new transaction\e[0m\n"
              << "\nPlease input name of transaction: ";
    std::cin >> m_name;

    std::cout << "Now lets type amount: ";
    std::cin >> m_amount;
    m_amount *= 100;

    accountPtr->addTransaction( la::Transaction((int)m_amount,m_name) );
}

void la::CliManager::showAccountBalance()
{
    accountPtr->updateAccountBalance();
    const double m_balance = (double)accountPtr->getBalance() / 100.0;
    std::cout << "\nCurrent Accounting balance: \e[1m" << m_balance << "\e[0m\n";
}
