#include "infobar.h"

InfoBar::InfoBar(QWidget *parent) : QFrame(parent)
{
    m_title = new QLabel();
    m_button = new QPushButton();
    m_layout = new QHBoxLayout();
    m_spacer = new QSpacerItem(20,20, QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_title->setText("New transaction added");
    m_layout->setSpacing(12);
    m_layout->addWidget(m_title);
    m_layout->addSpacerItem(m_spacer);
    m_layout->addWidget(m_button);

    setStyleSheet("background-color: red; color: white;");
    setLayout(m_layout);
}
