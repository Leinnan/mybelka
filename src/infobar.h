#ifndef INFOBAR_H
#define INFOBAR_H

#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFrame>

class InfoBar : public QFrame
{
    Q_OBJECT
public:
    explicit InfoBar(QWidget *parent = nullptr);

signals:

public slots:

private:
    QLabel      *m_title;
    QPushButton *m_button;
    QHBoxLayout *m_layout;
    QSpacerItem *m_spacer;
};

#endif // INFOBAR_H
