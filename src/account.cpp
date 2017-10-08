#include "account.h"
#include <algorithm>
#include <iomanip>

la::Account::Account() :
    balance( 0 ),
    compactFormat( false ),
    deviceId( "none" )
{

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

        if( obj.contains("currentDate") )
        {
            fileTimestamp = obj["currentDate"].toString();
            if( obj.contains( "deviceId" ) )
                deviceId = obj["deviceId"].toString();
        }
        else
        {
            la::Transaction m_transaction(obj["date"].toString().toStdString(),
                                        obj["amount"].toInt(),
                                        obj["title"].toString().toStdString());
            this->transactions.push_back(m_transaction);
        }
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


    for(la::Transaction f_transaction : transactions)
    {
        QJsonObject m_obj;
        m_obj["title"] = QString::fromStdString(f_transaction.getTitle());
        m_obj["date"] = f_transaction.getDate().toString("dd.MM.yyyy hh:mm");
        m_obj["amount"] = f_transaction.getAmount();

        if(!f_transaction.isIncome())
            m_obj["amount"] = f_transaction.getAmount() * -1;
        m_transactions.append(m_obj);
    }

    {
        QJsonObject m_settings;
        m_settings["currentDate"] = QString::number( QDateTime::currentSecsSinceEpoch() );

        if( deviceId == "none" )
        {
            QUuid m_device = QUuid::createUuid();
            m_settings["deviceId"] = m_device.toString();
        }
        else
        {
            m_settings["deviceId"] = deviceId;
        }

        m_transactions.append( m_settings );
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

void la::Account::setDeviceId(const QString &value)
{
    deviceId = value;
}

int la::Account::getBalance()
{
    updateAccountBalance();
    return balance;
}

QString la::Account::getDeviceId() const
{
    return deviceId;
}
