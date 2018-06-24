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
    Transaction(std::string,TransactionType,int,std::string,la::Category);
    Transaction(TransactionType,int,std::string,la::Category);
    Transaction(int,std::string);
    Transaction(std::string,int,std::string);
    bool isIncome(){return transactionType == TransactionType::INCOME;}
    int getAmount(){return this->amount;}
    QDateTime getDate() const;
    std::string getTitle() const;
    void setTitle(const std::string &value);

    TransactionType getTransactionType() const;
    void setDate(const QDateTime &value);

private:
    void generateUID();

    QDateTime date;
    TransactionType transactionType;
    int amount;// w groszach
    std::string title;
    la::Category category;
    QUuid uid;
};

}

#endif // TRANSACTION_H
