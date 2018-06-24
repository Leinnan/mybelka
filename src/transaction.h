#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>
#include <iostream>
#include <QDateTime>
#include <QUuid>
#include "category.h"

namespace la {

const std::string ec_reset = "\e[0m";
const std::string ec_default = "\e[39m";
const std::string ec_black = "\e[30m";
const std::string ec_red = "\e[31m";
const std::string ec_green = "\e[32m";

enum class TransactionType { INCOME, EXPENSE };

class Transaction
{
public:
    Transaction(std::string,TransactionType,int,QString,la::Category);
    Transaction(TransactionType,int,QString,la::Category);
    Transaction(int,QString);
    Transaction(std::string,int,QString);
    bool isIncome(){return transactionType == TransactionType::INCOME;}
    const int getAmount() const {return this->amount;}
    QDateTime getDate() const;
    QString getTitle() const;
    void setTitle(const QString &value);

    TransactionType getTransactionType() const;
    void setDate(const QDateTime &value);

    QUuid getUid() const;

    void setUid(const QUuid &value);

private:
    void generateUID();

    QDateTime date;
    TransactionType transactionType;
    int amount;// w groszach
    QString title;
    la::Category category;
    QUuid uid;
};

}

#endif // TRANSACTION_H
