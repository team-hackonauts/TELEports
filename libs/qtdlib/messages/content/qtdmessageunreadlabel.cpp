#include "qtdmessageunreadlabel.h"

QTdMessageUnreadLabel::QTdMessageUnreadLabel(QObject *parent)
    : QTdMessageContent(parent)
    , m_label("")
{
    setType(MESSAGE_UNREAD_LABEL);
}

QString QTdMessageUnreadLabel::label()
{
    return m_label;
}

void QTdMessageUnreadLabel::setLabel(const QString label)
{
    m_label = label;
}
