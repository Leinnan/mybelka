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
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QDesktopWidget>

la::UiManager::UiManager(QWidget *parent) :
    QMainWindow(parent),
    m_splitByDays(true)
{
    QSettings settings;
    restoreGeometry(settings.value("mainWindowGeometry").toByteArray());
    m_table = new QTableWidget();
    m_layout = new QHBoxLayout();
    m_sideBar = new QVBoxLayout();
    m_centralWidget = new QWidget();
    m_accountPtr = std::make_shared<la::Account>();

    if (objectName().isEmpty())
        setObjectName(QStringLiteral("MainWindow"));

    m_layout->addWidget(m_table,1);
    m_layout->addSpacing(12);
    m_sideBar->addWidget(&m_accountState);
    m_sideBar->addStretch(1);
    m_sideBar->setMargin(12);
    m_layout->addLayout( m_sideBar );
    m_layout->setMargin(12);

    m_removeTransactionBtn = new QPushButton(tr("Remove transaction"), this);
    m_editTransactionBtn = new QPushButton(tr("Edit transaction"), this);
    m_addTransactionBtn = new QPushButton(tr("Add new transaction"), this);

    m_removeTransactionBtn->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    m_editTransactionBtn->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
    m_addTransactionBtn->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
        
    m_sideBar->addWidget(m_removeTransactionBtn);
    m_sideBar->addWidget(m_editTransactionBtn);
    m_sideBar->addWidget(m_addTransactionBtn);
    
    m_table->setObjectName("DISPLAY");
    m_table->setColumnCount(3);
    m_table->setRowCount( m_accountPtr->getTransactions().size() );

    QStringList m_tableHeader;
    m_tableHeader << "Date" << "Name" << "Amount";
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setSelectionMode(QAbstractItemView::SingleSelection);
    m_table->setHorizontalHeaderLabels(m_tableHeader);

    m_table->horizontalHeader()->setSectionResizeMode(
        1, QHeaderView::Stretch);
    m_centralWidget->setLayout( m_layout );
    setCentralWidget( m_centralWidget );
    showTransactions();
    connect(m_addTransactionBtn,SIGNAL(clicked()),this,SLOT(showTransactionDialog()));
    connect(m_editTransactionBtn,SIGNAL(clicked()),this,SLOT(showEditTransactionDialog()));
    connect(m_removeTransactionBtn,SIGNAL(clicked()),this,SLOT(handleRemoveTransactionDialog()));
}

void la::UiManager::applySettings( QSettings *settings )
{
    m_settings = settings;

    restoreState(m_settings->value("mainWindowState").toByteArray());

    m_accountPtr->readFromJson();
    m_accountPtr->setCompactFormat( m_settings->value( "compactJSON", false ).toBool() );

    m_accountPtr->sortTransactions();
    m_accountPtr->saveToJson();
}

void la::UiManager::showTransactions( bool divideByDays /*= false*/ )
{
    std::vector<la::Transaction> transactions = m_accountPtr->getTransactions();
    int counter = 0;

    std::cout << "There is " <<  transactions.size() << " transactions\n";
    m_table->setRowCount( transactions.size() );
    QString lastTransactionDate = "";
    QString newTransactionDate = "";
    m_emptyTableItems.clear();
    for(la::Transaction f_transaction : transactions)
    {
        newTransactionDate = f_transaction.getDate().toString("dd.MM.yyyy");
        if(m_splitByDays && lastTransactionDate != newTransactionDate)
        {
            m_table->setRowCount( m_table->rowCount() + 1 );
            m_emptyTableItems.push_back( { new QTableWidgetItem(), counter } );
            m_emptyTableItems.back().first->setFlags(0);
            m_emptyTableItems.back().first->setText(newTransactionDate);
            m_table->setItem(counter, 0, m_emptyTableItems.back().first );
            m_table->setSpan( counter, 0, 1, 3 );
            counter++;
        }
        m_table->setItem(counter, 0,
                        new QTableWidgetItem(
                        f_transaction.getDate().toString(m_splitByDays ? "hh:mm" : "dd.MM.yyyy hh:mm")
                        ));
        m_table->setItem(counter, 1,
                        new QTableWidgetItem(
                        f_transaction.getTitle()
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

    m_accountPtr->updateAccountBalance();
    const double m_balance = (double)m_accountPtr->getBalance() / 100.0;
    QString accountText = "<b>Current account state: </b><br><span style=\"font-size: 25pt\">";
    accountText += QString::number(m_balance);
    accountText += "</span>";
    m_accountState.setText(accountText);
}

void la::UiManager::displayTransaction( la::Transaction& transaction, bool displayFullDate )
{
}

void la::UiManager::showTransactionDialog()
{
    m_addTransactionWindow = new la::AddTransactionWindow();
    connect( m_addTransactionWindow, SIGNAL( accepted() ), SLOT( onDialogAccepted() ) );

    m_addTransactionWindow->show();
}

void la::UiManager::showEditTransactionDialog()
{
    const auto& transactionIndex = getSelectedTransactionIndexFromTable();

    if( transactionIndex < 0 )
        return;

    la::Transaction transaction = m_accountPtr->getTransactions()[transactionIndex];

    m_editTransactionWindow = new la::EditTransactionWindow(transaction);
    connect( m_editTransactionWindow, SIGNAL( accepted() ), SLOT( onEditDialogAccepted() ) );

    m_editTransactionWindow->show();
}

void la::UiManager::onDialogAccepted()
{
    la::Transaction newTransaction = m_addTransactionWindow->getTransaction();
    m_accountPtr->addTransaction( newTransaction );
    m_accountPtr->updateAccountBalance();
    m_addTransactionWindow->cleanValues();

    m_accountPtr->sortTransactions();
    m_accountPtr->saveToJson();
    showTransactions();
}

void la::UiManager::onEditDialogAccepted()
{
    const auto& editedTransaction = m_editTransactionWindow->getTransaction();
    const auto& transactionUid = editedTransaction.getUid();
    if( m_accountPtr->getTransactionIndexByUid( transactionUid ) > -1 )
    {
            m_accountPtr->replaceTransactionWithUid(transactionUid, editedTransaction);
            m_accountPtr->updateAccountBalance();

            m_accountPtr->sortTransactions();
            m_accountPtr->saveToJson();
            showTransactions();
    }
    m_editTransactionWindow->cleanValues();
}

void la::UiManager::handleRemoveTransactionDialog()
{
    const int transactionIndex = getSelectedTransactionIndexFromTable();
    if(transactionIndex < 0)
        return;

    const auto result = QMessageBox::warning(this, tr("Delete transaction"),
                                             tr("Are you sure that you want to delete this transaction?"),
                                             QMessageBox::Yes | QMessageBox::Cancel );
    if(result == QMessageBox::Yes)
    {
        m_accountPtr->removeTransaction(transactionIndex);
        showTransactions();
    }

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

void la::UiManager::closeEvent(QCloseEvent *event)
{
    QSettings settings;
    settings.setValue("mainWindowGeometry", saveGeometry());
    settings.setValue("mainWindowState", saveState());
}

void la::UiManager::showMenu()
{
    show();
}

const int la::UiManager::getSelectedTransactionIndexFromTable()
{
    const auto& selectedItemsInTable = m_table->selectedItems();

    if(selectedItemsInTable.empty())
        return -1;

    const int tableRow = selectedItemsInTable[0]->row();
    // remember about empty lines!
    const int emptyLines = std::count_if(m_emptyTableItems.begin(),m_emptyTableItems.end(),
                                         [&tableRow](TableItem& tableItem){ return tableItem.second < tableRow; });

    return (tableRow - emptyLines);

}
