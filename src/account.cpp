#include "account.h"
#include <algorithm>

la::Account::Account()
{

}

void la::Account::showTransactions( bool divideByDays /*= false*/ )
{
//    .toString(date_format).toStdString()
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

void la::Account::addTransaction(la::Transaction m_transaction)
{
    transactions.push_back(m_transaction);
    this->updateAccountBalance();
}

void la::Account::sortTransactions()
{
    std::sort(std::begin(this->transactions),std::end(this->transactions),
              [](const la::Transaction& lhs, const la::Transaction& rhs){ return lhs.getDate() < rhs.getDate();});
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
    
    m_file.close();
}

void la::Account::saveToJson(std::string m_path)
{
    QFile m_file(QString::fromStdString(m_path));
    if (!m_file.open(QFile::WriteOnly))
            return;

    QJsonObject m_root;//root object
    QJsonArray m_transactions;//(2)


    for(la::Transaction f_transaction : transactions){
        QJsonObject m_obj;
        m_obj["title"] = QString::fromStdString(f_transaction.getTitle());
        m_obj["date"] = f_transaction.getDate().toString("dd.MM.yyyy hh:mm");
        m_obj["amount"] = f_transaction.getAmount();

        if(!f_transaction.isIncome())
            m_obj["amount"] = f_transaction.getAmount() * -1;
        m_transactions.append(m_obj);
    }

    m_root["transactions"] = m_transactions;//(6)
    QJsonDocument::JsonFormat jsonFormat = compactFormat ? QJsonDocument::Compact : QJsonDocument::Indented;
    m_file.write(QJsonDocument(m_root).toJson(jsonFormat));
    m_file.close();
}

void la::Account::setCompactFormat(bool value)
{
    compactFormat = value;
}

void la::Account::showAccountBalance()
{
    this->updateAccountBalance();
    std::cout << "\nCurrent Accounting balance: \e[1m" << (float)(balance / 100.0) << "\e[0m\n";
}
