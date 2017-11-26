#ifndef ADDTRANSACTIONWINDOW_H
#define ADDTRANSACTIONWINDOW_H

#include <QtCore>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialogButtonBox>

#include "src/transaction.h"

namespace la
{

class AddTransactionWindow: public QDialog
{
    Q_OBJECT
public:
    AddTransactionWindow();
    ~AddTransactionWindow(){}
    la::Transaction getTransaction() const;
    void cleanValues();

private:
    QVBoxLayout                         m_layout;
    std::pair< QLabel, QLineEdit >      m_transactionName;
    std::pair< QLabel, QLineEdit >      m_transactionAmount;
    std::pair< QLabel, QDateTimeEdit >  m_transactionDate;
    QDialogButtonBox*                   m_buttonBox;
};

}
#endif // ADDTRANSACTIONWINDOW_H
