#ifndef UIMANAGER_H
#define UIMANAGER_H
#include <src/account.h>
#include <src/transaction.h>
#include <src/addtransactionwindow.h>

#include <QtCore>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <memory>

namespace la
{

class UiManager: public QMainWindow
{
    Q_OBJECT
public:
    UiManager( QWidget *parent = 0 );
    ~UiManager(){};
    void                            applySettings( QSettings& );
    void                            showTransactions( bool divideByDays = false );
    void                            displayTransaction( la::Transaction&, bool );
    void                            addTransaction(){};
    void                            showAccountBalance();
    void                            runMenu();
protected:
    void changeEvent(QEvent *e){};
private slots:
    void                            showTransactionDialog();
    void                            onDialogAccepted();
private:
    void                            showMenu();

    std::shared_ptr<la::Account>    m_accountPtr;
    QTableWidget                    m_table;
    QVBoxLayout                     m_layout;
    QHBoxLayout                     m_bottomMenu;
    QWidget                         m_centralWidget;
    QLabel                          m_accountState;
    QPushButton                     *m_button;
    la::AddTransactionWindow        *m_transactionWindow;
};

}
#endif // UIMANAGER_H
