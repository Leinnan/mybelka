#include "src/uimanager.h"
#include "src/infobar.h"

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
    m_table = new QTableWidget();
    m_layout = new QVBoxLayout();
    m_bottomMenu = new QHBoxLayout();
    m_centralWidget = new QWidget();
    m_emptyTableItem = new QTableWidgetItem();
    m_accountPtr = std::make_shared<la::Account>();
    QDesktopWidget desktop; 
    QRect screenSize = desktop.availableGeometry(this);
    setFixedSize(QSize(screenSize.width() * 0.7f, screenSize.height() * 0.7f));
    
    if (objectName().isEmpty())
        setObjectName(QStringLiteral("MainWindow"));
        
    QSpacerItem *spacerBottomMenu = new QSpacerItem(20,20, QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_layout->addWidget(m_table);
    m_layout->addSpacing(12);
    m_bottomMenu->addWidget(&m_accountState);
    m_bottomMenu->addSpacerItem(spacerBottomMenu);
    m_layout->addLayout( m_bottomMenu );
    m_layout->setMargin(12);
    m_emptyTableItem->setFlags(0);

    m_button = new QPushButton("Add new transaction", this);
    m_bottomMenu->addWidget(m_button);
    
    m_table->setObjectName("DISPLAY");
    m_table->setColumnCount(3);
    m_table->setRowCount( m_accountPtr->getTransactions().size() );

    m_transactionWindow = new la::AddTransactionWindow;
    connect( m_transactionWindow, SIGNAL( accepted() ), SLOT( onDialogAccepted() ) );
    QStringList m_tableHeader;
    m_tableHeader << "Date" << "Name" << "Amount";
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setSelectionMode(QAbstractItemView::SingleSelection);
    m_table->setHorizontalHeaderLabels(m_tableHeader);
    //m_table.verticalHeader()->setVisible(false);
    m_table->horizontalHeader()->setSectionResizeMode(
        1, QHeaderView::Stretch);
    m_centralWidget->setLayout( m_layout );
    setCentralWidget( m_centralWidget );
    showTransactions();
    connect(m_button,SIGNAL(clicked()),this,SLOT(showTransactionDialog()));
}

void la::UiManager::applySettings( QSettings *settings )
{
    m_settings = settings;
    
    m_accountPtr->readFromJson();
    m_accountPtr->setCompactFormat( m_settings->value( "compactJSON", false ).toBool() );


    m_accountPtr->sortTransactions();
    m_accountPtr->saveToJson();
}

void la::UiManager::showTransactions( bool divideByDays /*= false*/ )
{
    std::vector<la::Transaction> transactions = m_accountPtr->getTransactions();

    {
        int counter = 0;
        std::cout << "There is " <<  transactions.size() << " transactions\n";
        m_table->setRowCount( transactions.size() );
        QString lastTransactionDate = "";
        QString newTransactionDate = "";
        for(la::Transaction f_transaction : transactions)
        {
            newTransactionDate = f_transaction.getDate().toString("dd.MM.yyyy");
            if(lastTransactionDate != newTransactionDate && !lastTransactionDate.isEmpty())
            {
                m_table->setRowCount( m_table->rowCount() + 1 );
                m_table->setItem(counter, 0, m_emptyTableItem );
                m_table->setSpan( counter, 0, 1, 3 );
                counter++;
            }
            m_table->setItem(counter, 0,
                            new QTableWidgetItem(
                            f_transaction.getDate().toString("dd.MM.yyyy hh:mm")
                            ));
            m_table->setItem(counter, 1,
                            new QTableWidgetItem(
                            f_transaction.getTitle().c_str()
                            ));
            char sign = (f_transaction.getTransactionType() == TransactionType::INCOME) ? '+' : '-';
            QString m_amount = sign + QString::number(f_transaction.getAmount() / 100.0);
            m_table->setItem(counter, 2,
                            new QTableWidgetItem(
                            m_amount
                            ));
            counter++;
            lastTransactionDate = newTransactionDate;
        }
    }
    {
        m_accountPtr->updateAccountBalance();
        const double m_balance = (double)m_accountPtr->getBalance() / 100.0;
        QString accountText = "<b>Account state: </b>";
        accountText += QString::number(m_balance);
        m_accountState.setText(accountText);
    }
    
}

void la::UiManager::displayTransaction( la::Transaction& transaction, bool displayFullDate )
{
}

void la::UiManager::showTransactionDialog()
{
    if( !m_transactionWindow )
    {
        m_transactionWindow = new la::AddTransactionWindow();
        connect( m_transactionWindow, SIGNAL( accepted() ), SLOT( onDialogAccepted() ) );
    }

    m_transactionWindow->show();
}

void la::UiManager::onDialogAccepted()
{
    la::Transaction newTransaction = m_transactionWindow->getTransaction();
    m_accountPtr->addTransaction( newTransaction );
    m_accountPtr->updateAccountBalance();
    m_transactionWindow->cleanValues();
    
    m_accountPtr->saveToJson();
    showTransactions();
}

void la::UiManager::showAccountBalance()
{
    m_accountPtr->updateAccountBalance();
    const double m_balance = (double)m_accountPtr->getBalance() / 100.0;
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
