#include "qtdmessagecontactregistered.h"
#include "utils/await.h"
#include "utils/i18n.h"

QTdMessageContactRegistered::QTdMessageContactRegistered(QObject *parent)
    : QTdMessageContent(parent)
{
    setType(MESSAGE_CONTACT_REGISTERED);
    m_typeText = gettext("has joined Telegram!");
}
