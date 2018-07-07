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
    m_transactions.push_back(m_transaction);
    this->updateAccountBalance();
}

void la::Account::sortTransactions()
{
    std::sort(std::begin(this->m_transactions),std::end(this->m_transactions),
              [](const la::Transaction& lhs, const la::Transaction& rhs){ return lhs.getDate() < rhs.getDate();});
}

void la::Account::updateAccountBalance()
{
    balance = 0;

    for(la::Transaction f_transaction : m_transactions){
        if(f_transaction.isIncome()){
            balance += f_transaction.getAmount();
        }
        else{
            balance -= f_transaction.getAmount();
        }
    }
}

void la::Account::readFromJson()
{
    const QString downloadsFolder = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/transactions.json";
    std::clog << "Read transactions from " << downloadsFolder.toStdString() << '\n';
    QFile m_file(downloadsFolder);
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
                                        obj["title"].toString());
            this->m_transactions.push_back(m_transaction);
        }
    }

    this->sortTransactions();
    
    m_file.close();
}

void la::Account::saveToJson()
{
    const QString folder = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir;
    const QString fileToSave = folder + "/transactions.json";
    QFile m_file( fileToSave );

    if(!dir.exists(folder))
        dir.mkpath(folder);

    if (!m_file.open(QFile::WriteOnly))
        return;

    QJsonObject m_root;//root object
    QJsonArray transactionsJson;//(2)


    for(la::Transaction f_transaction : m_transactions)
    {
        QJsonObject m_obj;
        m_obj["title"] = f_transaction.getTitle();
        m_obj["date"] = f_transaction.getDate().toString("dd.MM.yyyy hh:mm");
        m_obj["amount"] = f_transaction.getAmount();

        if(!f_transaction.isIncome())
            m_obj["amount"] = f_transaction.getAmount() * -1;
        transactionsJson.append(m_obj);
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

        transactionsJson.append( m_settings );
    }

    m_root["transactions"] = transactionsJson;//(6)
    const QJsonDocument::JsonFormat jsonFormat = compactFormat ? QJsonDocument::Compact : QJsonDocument::Indented;
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

std::vector<la::Transaction> la::Account::getTransactionsContaining(const QString& text)
{
    std::vector<la::Transaction> result;
    
    for(const auto& transaction : m_transactions)
    {
        if(transaction.getTitle().contains(text, Qt::CaseInsensitive))
            result.push_back(transaction);
    }
    return result;
}

int la::Account::getBalance()
{
    updateAccountBalance();
    return balance;
}

const int la::Account::getTransactionIndexByUid(const QUuid &uid)
{
    int index = -1;
    const int isAny = std::any_of(m_transactions.begin(),m_transactions.end(),[&uid,&index](la::Transaction& transaction){
        index++;
        return transaction.getUid() == uid;
    });
    return isAny ? index : -1;
}

void la::Account::replaceTransactionWithUid(const QUuid &uid, const la::Transaction &transaction)
{
    std::replace_if(m_transactions.begin(),m_transactions.end(),[&uid](la::Transaction& transaction){
            return transaction.getUid() == uid;
    }, transaction);
}

void la::Account::removeTransaction(const int &index)
{
    m_transactions.erase(m_transactions.begin()+index);

    updateAccountBalance();
    sortTransactions();
    saveToJson();
}

QString la::Account::getDeviceId() const
{
    return deviceId;
}
