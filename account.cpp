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

bool isDateLater(const la::Transaction& lhs, const la::Transaction& rhs){
    return lhs.getDate() < rhs.getDate();
}

void la::Account::sortTransactions()
{
    std::sort(std::begin(this->transactions),std::end(this->transactions),
              //[&](const la::Transaction& lhs, const la::Transaction& rhs){ lhs.getDate() < rhs.getDate();});
                isDateLater);
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

void la::Account::readFromJson(std::string m_path)
{
    QFile m_file(QString::fromStdString(m_path));
    if (!m_file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
    QByteArray m_json_data = m_file.readAll();
    QJsonParseError *m_err = new QJsonParseError();
    QJsonDocument m_document = QJsonDocument::fromJson(m_json_data, m_err);
    QJsonObject m_object = m_document.object();
    QJsonArray m_json_array = m_object["transactions"].toArray();

    for (const QJsonValue & m_value : m_json_array) {
        QJsonObject obj = m_value.toObject();
        la::Transaction m_transaction(obj["date"].toString().toStdString(),
                                    obj["amount"].toInt(),
                                    obj["title"].toString().toStdString());
        this->transactions.push_back(m_transaction);
    }

    this->sortTransactions();

}


void la::Account::showAccountBalance()
{
    this->updateAccountBalance();
    float m_balance = balance / 100.0;
    std::cout << "\nCurrent Accounting balance: \e[1m" << m_balance << "\e[0m\n";
}
