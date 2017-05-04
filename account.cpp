#include "account.h"
#include <algorithm>

la::Account::Account()
{

}

void la::Account::showTransactions()
{
    for(la::Transaction f_transaction : transactions){
        f_transaction.display();
//        std::cout << "______________________________\n";
    }
}

void la::Account::addTransaction(la::Transaction m_transaction)
{
    transactions.push_back(m_transaction);
    this->updateAccountBalance();
}

void la::Account::sortTransactions()
{
    std::sort(std::begin(this->transactions),std::end(this->transactions),
              [&](const la::Transaction& lhs, const la::Transaction& rhs){ lhs.getDate() < rhs.getDate();});
}

void la::Account::updateAccountBalance()
{
    balance = 0;

    for(la::Transaction f_transaction : transactions){
        if(f_transaction.isIncome()){
            balance += f_transaction.getAmount();
        }
        else{
            balance -= f_transaction.getAmount();
        }
    }
}


void la::Account::showAccountBalance()
{
    this->updateAccountBalance();
    float m_balance = balance / 100.0;
    std::cout << "\nCurrent Accounting balance: \e[1m" << m_balance << "\e[0m\n";
}
