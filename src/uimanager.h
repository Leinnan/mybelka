#ifndef UIMANAGER_H
#define UIMANAGER_H
#include <src/account.h>
#include <src/transaction.h>

#include <QtCore>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QLabel>
#include <QLayout>
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
    void                            addTransaction();
    void                            showAccountBalance();
    void                            runMenu();
protected:
    void changeEvent(QEvent *e){};
private:
    void                            showMenu();

    std::shared_ptr<la::Account>    accountPtr;
    QWidget *centralWidget;
    QLabel m_label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar   *statusBar;
    QTableWidget m_table;
    QVBoxLayout *m_layout;
    QWidget     m_centralWidget;
};

}
#endif // UIMANAGER_H
