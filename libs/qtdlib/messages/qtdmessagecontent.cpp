#include "qtdmessagecontent.h"
#include <libintl.h>
#include "utils/i18n.h"

QTdMessageContent::QTdMessageContent(QObject *parent)
    : QTdObject(parent),
    m_infoText(""),
    m_typeText(""),
    m_isSecret(false),
    m_infoImageUrl(QUrl())
{
}

QString QTdMessageContent::infoText() const
{
    return m_infoText;
}

QString QTdMessageContent::typeText() const
{
    return m_typeText;
}

QUrl QTdMessageContent::infoImageUrl() const
{
    return m_infoImageUrl;
}

bool QTdMessageContent::isSecret() const
{
    return m_isSecret;
}

void QTdMessageContent::setInfoText(const QString &infoText)
{
    m_infoText = infoText;
}

void QTdMessageContent::setTypeText(const QString &typeText)
{
    m_typeText = typeText;
}

QTdMessageAction::QTdMessageAction(QObject *parent)
    : QTdMessageContent(parent)
{
    setType(MESSAGE_ACTION);
}

QTdMessageHidden::QTdMessageHidden(QObject *parent)
    : QTdMessageContent(parent)
{
    setType(MESSAGE_HIDDEN);
}
