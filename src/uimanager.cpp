#include "src/uimanager.h"

// external
#include <iostream>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QDesktopWidget>

la::UiManager::UiManager(QWidget *parent) :
    QMainWindow(parent)
{
    accountPtr = std::make_shared<la::Account>();
    
    if (objectName().isEmpty())
        setObjectName(QStringLiteral("MainWindow"));
        
    m_label.setText("MyBelka");
    m_layout = new QVBoxLayout();
    m_layout->addWidget(&m_label);
    m_layout->addSpacing(12);
    m_layout->addWidget(&m_table);
    m_layout->setMargin(12);

    m_table.setObjectName("DISPLAY");
    m_table.setColumnCount(3);
    m_table.setRowCount( accountPtr->getTransactions().size() );
    
    QStringList m_tableHeader;
    m_tableHeader << "Date" << "Name" << "Amount";
    m_table.setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table.setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table.setSelectionMode(QAbstractItemView::SingleSelection);
    m_table.setHorizontalHeaderLabels(m_tableHeader);
    //m_table.verticalHeader()->setVisible(false);
    m_table.setGeometry(QApplication::desktop()->screenGeometry());
    m_centralWidget.setLayout(m_layout);
    setCentralWidget( &m_centralWidget );
/*    menuBar = new QMenuBar(this);
    menuBar->setObjectName(QStringLiteral("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 706, 22));
    setMenuBar(menuBar);
    mainToolBar = new QToolBar( this );
    mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
    addToolBar(Qt::TopToolBarArea, mainToolBar);
    statusBar = new QStatusBar( this );
    statusBar->setObjectName(QStringLiteral("statusBar"));
    setStatusBar(statusBar);
    QMetaObject::connectSlotsByName( this );*/
    showTransactions();
}

void la::UiManager::applySettings( QSettings& settings )
{

    std::string json_path = settings.value("json_path","test.json").toString().toStdString();

    accountPtr->readFromJson(json_path);
    accountPtr->setCompactFormat( settings.value( "compactJSON", false ).toBool() );


    accountPtr->sortTransactions();
    accountPtr->saveToJson(json_path);
//    showTransactions(true);
//    accountPtr->showAccountBalance();
}

void la::UiManager::showTransactions( bool divideByDays /*= false*/ )
{
    std::vector<la::Transaction> transactions = accountPtr->getTransactions();

    {
        int counter = 0;
        std::cout << "There is " <<  transactions.size() << " transactions\n";
        m_table.setRowCount( transactions.size() );
        for(la::Transaction f_transaction : transactions)
        {
            m_table.setItem(counter, 0, 
                            new QTableWidgetItem(
                            f_transaction.getDate().toString("dd.MM.yyyy hh:mm")
                            ));
            m_table.setItem(counter, 1, 
                            new QTableWidgetItem(
                            f_transaction.getTitle().c_str()
                            ));
            QString m_amount = QString::number(f_transaction.getAmount() / 100.0);
            m_table.setItem(counter, 2, 
                            new QTableWidgetItem(
                            m_amount
                            ));
            counter++;
        }
    }
}

void la::UiManager::displayTransaction( la::Transaction& transaction, bool displayFullDate )
{
    char sign = (transaction.getTransactionType() == TransactionType::INCOME) ? '+' : '-';
    std::string color = (transaction.getTransactionType() == TransactionType::INCOME) ? ec_green : ec_red;
    const QString date_format = displayFullDate ? "dd.MM.yyyy hh:mm" : "\thh:mm";
    float m_amount = transaction.getAmount() / 100.0;
    std::string m_date_title =  transaction.getDate().toString(date_format).toStdString()
            + " " + transaction.getTitle();
    m_date_title.append(40-m_date_title.length(),' ');
    std::cout << m_date_title << '\t'
              << sign << color
              << m_amount << ec_default
              << '\n';
}

void la::UiManager::addTransaction()
{

    std::string m_name;

    double m_amount = 0;

    std::cout << "\e[1mAdding new transaction\e[0m\n"
              << "\nPlease input name of transaction: ";
    std::cin >> m_name;

    std::cout << "Now lets type amount: ";
    std::cin >> m_amount;
    m_amount *= 100;

    accountPtr->addTransaction( la::Transaction((int)m_amount,m_name) );
}

void la::UiManager::showAccountBalance()
{
    accountPtr->updateAccountBalance();
    const double m_balance = (double)accountPtr->getBalance() / 100.0;
    std::cout << "\nCurrent Accounting balance: \e[1m" << m_balance << "\e[0m\n";
}

void la::UiManager::runMenu()
{
    showMenu();
}

void la::UiManager::showMenu()
{
    show();
}
