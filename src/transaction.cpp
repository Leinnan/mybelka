#include "transaction.h"

namespace la {


Transaction::Transaction(std::string m_date,TransactionType m_type, int m_amount,
                         QString m_title, la::Category m_category){

    this->date = date.fromString(QString::fromStdString(m_date),QString("dd.MM.yyyy hh:mm"));
    this->transactionType = m_type;
    this->amount = m_amount;
    this->title = m_title;
    this->category = m_category;
    this->uid = QUuid::createUuid();
}

Transaction::Transaction(TransactionType m_type, int m_amount,
                         QString m_title, la::Category m_category){
    this->date = date.currentDateTime();
    this->transactionType = m_type;
    this->amount = m_amount;
    this->title = m_title;
    this->category = m_category;
    this->uid = QUuid::createUuid();
}

Transaction::Transaction(int m_amount, QString m_title)
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
    this->uid = QUuid::createUuid();
}


Transaction::Transaction(std::string m_date,int m_amount, QString m_title)
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
    this->uid = QUuid::createUuid();
}

QDateTime Transaction::getDate() const
{
    return date;
}

QString Transaction::getTitle() const
{
    return title;
}

void Transaction::setTitle(const QString &value)
{
    title = value;
}

TransactionType Transaction::getTransactionType() const
{
    return transactionType;
}

void Transaction::setDate(const QDateTime &value)
{
    date = value;
}

QUuid Transaction::getUid() const
{
    return uid;
}

void Transaction::setUid(const QUuid &value)
{
    uid = value;
}

}
