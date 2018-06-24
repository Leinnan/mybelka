#ifndef EDITTRANSACTIONWINDOW_H
#define EDITTRANSACTIONWINDOW_H
#include "src/addtransactionwindow.h"
#include "src/transaction.h"
#include <QUuid>

namespace la {

class EditTransactionWindow : public AddTransactionWindow
{
public:
    EditTransactionWindow(const la::Transaction&);
    void FillWindowWithValues(const la::Transaction&);
    la::Transaction getTransaction();
private:
    QUuid m_transactionUid;
};

}

#endif // EDITTRANSACTIONWINDOW_H
