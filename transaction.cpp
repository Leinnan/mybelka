#include "transaction.h"

namespace la {


Transaction::Transaction(std::string m_date,TransactionType m_type, int m_amount,
                         std::string m_title, la::Category m_category){

    this->date = date.fromString(QString::fromStdString(m_date),QString("dd.MM.yyyy hh:mm"));
    this->transaction_type = m_type;
    this->amount = m_amount;
    this->title = m_title;
    this->category = m_category;

}

Transaction::Transaction(TransactionType m_type, int m_amount,
                         std::string m_title, la::Category m_category){
    this->date = date.currentDateTime();
    this->transaction_type = m_type;
    this->amount = m_amount;
    this->title = m_title;
    this->category = m_category;

}

Transaction::Transaction(int m_amount, std::string m_title)
{
    if(m_amount > 0){
        this->transaction_type = TransactionType::INCOME;
    }
    else{
        this->transaction_type = TransactionType::EXPENSE;
        m_amount *= -1;
    }
    this->amount = m_amount;
    this->title = m_title;
    this->date = date.currentDateTime();

}


Transaction::Transaction(std::string m_date,int m_amount, std::string m_title)
{
    if(m_amount > 0){
        this->transaction_type = TransactionType::INCOME;
    }
    else{
        this->transaction_type = TransactionType::EXPENSE;
        m_amount *= -1;
    }
    this->amount = m_amount;
    this->title = m_title;
    this->date = date.fromString(QString::fromStdString(m_date),QString("dd.MM.yyyy hh:mm"));

}

void Transaction::display()
{
    char sign = (this->transaction_type == TransactionType::INCOME) ? '+' : '-';
    std::string color = (this->transaction_type == TransactionType::INCOME) ? ec_green : ec_red;
    const QString date_format = "dd.MM.yyyy hh:mm";
    float m_amount = this->amount / 100.0;
    std::string m_date_title =  this->date.toString(date_format).toStdString() + " " + this->title;
    m_date_title.append(40-m_date_title.length(),' ');
    std::cout << m_date_title << '\t'
              << sign << color
              << m_amount << ec_default
              << '\n';
}


}
