#include "qtdmessagecustomserviceaction.h"
#include "chat/requests/qtdgetsupergrouprequest.h"
#include "utils/await.h"

QTdMessageCustomServiceAction::QTdMessageCustomServiceAction(QObject *parent)
    : QTdMessageContent(parent)
{
    setType(MESSAGE_CUSTOM_SERVICE_ACTION);
}

QString QTdMessageCustomServiceAction::text() const
{
    return m_text;
}

void QTdMessageCustomServiceAction::unmarshalJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }
    
    QTdMessageContent::unmarshalJson(json);
    m_text = json["text"].toString();
    m_typeText = m_text;
    emit contentChanged();
}
