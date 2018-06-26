#ifndef UIMANAGER_H
#define UIMANAGER_H
#include "src/account.h"
#include "src/transaction.h"
#include "src/edittransactionwindow.h"

#include <QtCore>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <memory>
#include <vector>
#include <utility>

namespace la
{
using TableItem = std::pair<QTableWidgetItem*,int>;// element, index
using TableItems = std::vector<TableItem>;

class UiManager: public QMainWindow
{
    Q_OBJECT
public:
    UiManager( QWidget *parent = 0 );
    ~UiManager(){}
    void                            applySettings( QSettings* );
    void                            showTransactions( bool divideByDays = false );
    void                            displayTransaction( la::Transaction&, bool );
    void                            addTransaction(){}
    void                            showAccountBalance();
    void                            runMenu();
protected:
    void changeEvent(QEvent *e){};
    void closeEvent(QCloseEvent *event);
private slots:
    void                            showTransactionDialog();
    void                            showEditTransactionDialog();
    void                            onDialogAccepted();
    void                            onEditDialogAccepted();
    void                            handleRemoveTransactionDialog();
private:
    void                            showMenu();
    const int                       getSelectedTransactionIndexFromTable();

    std::shared_ptr<la::Account>    m_accountPtr;
    QTableWidget                    *m_table;
    QHBoxLayout                     *m_layout;
    QVBoxLayout                     *m_sideBar;
    QWidget                         *m_centralWidget;
    TableItems                      m_emptyTableItems;
    QLabel                          m_accountState;
    QPushButton                     *m_removeTransactionBtn;
    QPushButton                     *m_addTransactionBtn;
    QPushButton                     *m_editTransactionBtn;
    la::AddTransactionWindow        *m_addTransactionWindow;
    la::EditTransactionWindow       *m_editTransactionWindow;
    QString                         m_jsonPath;
    QSettings                       *m_settings;
    bool                            m_splitByDays;
};

}
#endif // UIMANAGER_H
