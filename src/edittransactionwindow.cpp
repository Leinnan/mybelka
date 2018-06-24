#include "edittransactionwindow.h"

la::EditTransactionWindow::EditTransactionWindow(const la::Transaction& transaction)
{
    FillWindowWithValues(transaction);
}

void la::EditTransactionWindow::FillWindowWithValues(const la::Transaction& transaction)
{
    this->m_transactionUid = transaction.getUid();
    setTransactionName(QString::fromStdString(transaction.getTitle()));
    setTransactionAmount(transaction.getAmount());
    setTransactionDate(transaction.getDate());
}

la::Transaction la::EditTransactionWindow::getTransaction()
{
    la::Transaction result = AddTransactionWindow::getTransaction();
    //result.setUid(m_transactionUid);

    return result;
}
