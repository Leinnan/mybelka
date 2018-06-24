#include "addtransactionwindow.h"

namespace la
{

    AddTransactionWindow::AddTransactionWindow()
    {
        m_buttonBox = new QDialogButtonBox( QDialogButtonBox::Ok |
                                            QDialogButtonBox::Cancel );

        setWindowTitle("Add Transaction");
        m_transactionName.first.setText( "Title" );
        m_transactionAmount.first.setText( "Amount" );
        m_transactionDate.first.setText("Date");

        m_transactionDate.second.setDateTime( QDateTime::currentDateTime() );

        m_layout.addWidget(&m_transactionName.first);
        m_layout.addWidget(&m_transactionName.second);
        m_layout.addSpacing(12);
        m_layout.addWidget(&m_transactionAmount.first);
        m_layout.addWidget(&m_transactionAmount.second);
        m_layout.addSpacing(12);
        m_layout.addWidget(&m_transactionDate.first);
        m_layout.addWidget(&m_transactionDate.second);
        m_layout.addSpacing(12);
        m_layout.addWidget(m_buttonBox);
        m_layout.setMargin(12);
        setLayout( &m_layout );

        connect(m_buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(m_buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
        //        setCentralWidget( &m_centralWidget );
    }

    Transaction AddTransactionWindow::getTransaction() const
    {
        QString amountText = m_transactionAmount.second.text().replace(",",".");

        const auto title = m_transactionName.second.text();
        const auto amount = amountText.toDouble() * 100;
        const auto date = m_transactionDate.second.dateTime();
        la::Transaction result( amount, title );
        result.setDate( date );

        return result;
    }

    void AddTransactionWindow::cleanValues()
    {
        m_transactionName.second.setText("");
        m_transactionAmount.second.setText("");
    }

    void AddTransactionWindow::setTransactionName(const QString& name)
    {
        m_transactionName.second.setText(name);
    }

    void AddTransactionWindow::setTransactionAmount(const double& amount)
    {
        m_transactionAmount.second.setText(QString::number(amount));
    }

    void AddTransactionWindow::setTransactionDate(const QDateTime& date)
    {
        m_transactionDate.second.setDateTime(date);
    }



}
