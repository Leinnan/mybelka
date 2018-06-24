#include "edittransactionwindow.h"

la::EditTransactionWindow::EditTransactionWindow(const la::Transaction& transaction)
{
    FillWindowWithValues(transaction);
}

void la::EditTransactionWindow::FillWindowWithValues(const la::Transaction& transaction)
{
    this->m_transactionUid = transaction.getUid();
    const int modifier = (transaction.getTransactionType() == TransactionType::INCOME) ? 1 : -1;
    setTransactionName(transaction.getTitle());
    setTransactionAmount(static_cast<double>(transaction.getAmount()) / 100.0f);
    setTransactionDate(transaction.getDate());
}

la::Transaction la::EditTransactionWindow::getTransaction()
{
    la::Transaction result = AddTransactionWindow::getTransaction();
    result.setUid(m_transactionUid);

    return result;
}
