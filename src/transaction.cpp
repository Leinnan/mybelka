#include "transaction.h"

namespace la {


Transaction::Transaction(std::string m_date,TransactionType m_type, int m_amount,
                         std::string m_title, la::Category m_category){

    this->date = date.fromString(QString::fromStdString(m_date),QString("dd.MM.yyyy hh:mm"));
    this->transactionType = m_type;
    this->amount = m_amount;
    this->title = m_title;
    this->category = m_category;

}

Transaction::Transaction(TransactionType m_type, int m_amount,
                         std::string m_title, la::Category m_category){
    this->date = date.currentDateTime();
    this->transactionType = m_type;
    this->amount = m_amount;
    this->title = m_title;
    this->category = m_category;

}

Transaction::Transaction(int m_amount, std::string m_title)
{
    if(m_amount > 0){
        this->transactionType = TransactionType::INCOME;
    }
    else{
        this->transactionType = TransactionType::EXPENSE;
        m_amount *= -1;
    }
    this->amount = m_amount;
    this->title = m_title;
    this->date = date.currentDateTime();

}


Transaction::Transaction(std::string m_date,int m_amount, std::string m_title)
{
    if(m_amount > 0){
        this->transactionType = TransactionType::INCOME;
    }
    else{
        this->transactionType = TransactionType::EXPENSE;
        m_amount *= -1;
    }
    this->amount = m_amount;
    this->title = m_title;
    this->date = date.fromString(QString::fromStdString(m_date),QString("dd.MM.yyyy hh:mm"));

}

void Transaction::display( bool displayFullDate /*= true*/ )
{
    char sign = (this->transactionType == TransactionType::INCOME) ? '+' : '-';
    std::string color = (this->transactionType == TransactionType::INCOME) ? ec_green : ec_red;
    const QString date_format = displayFullDate ? "dd.MM.yyyy hh:mm" : "\thh:mm";
    float m_amount = this->amount / 100.0;
    std::string m_date_title =  this->date.toString(date_format).toStdString() + " " + this->title;
    m_date_title.append(40-m_date_title.length(),' ');
    std::cout << m_date_title << '\t'
              << sign << color
              << m_amount << ec_default
              << '\n';
}

QDateTime Transaction::getDate() const
{
    return date;
}

std::string Transaction::getTitle() const
{
    return title;
}

void Transaction::setTitle(const std::string &value)
{
    title = value;
}

TransactionType Transaction::getTransactionType() const
{
    return transactionType;
}


}
