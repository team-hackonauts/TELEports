#include "common/qabstracttdobject.h"
#include <QJsonValue>
#include <QDateTime>
#include "qtdmessageforwardinfo.h"
#include "qtdmessageforwardoriginfactory.h"
#include "common/qtdhelpers.h"
#include "user/requests/qtdgetuserrequest.h"
#include "chat/requests/qtdgetchatrequest.h"
#include "chat/qtdchat.h"
#include "utils/await.h"
#include "user/qtdusers.h"
#include "utils/i18n.h"

QTdMessageForwardInfo::QTdMessageForwardInfo(QObject *parent)
    : QTdObject(parent)
    , m_origin(Q_NULLPTR)
    , m_date(0)
    , m_fromChatId(0)
    , m_fromMessageId(0)
{
}

QTdMessageForwardOrigin *QTdMessageForwardInfo::origin() const
{
    return m_origin.data();
}

QDateTime QTdMessageForwardInfo::qmlDate() const
{
    return QDateTime::fromTime_t(m_date);
}
qint32 QTdMessageForwardInfo::date() const
{
    return m_date;
}

QString QTdMessageForwardInfo::qmlFromChatId() const
{
    return m_fromChatId.toQmlValue();
}
qint64 QTdMessageForwardInfo::fromChatId() const
{
    return m_fromChatId.value();
}

QString QTdMessageForwardInfo::qmlFromMessageId() const
{
    return m_fromMessageId.toQmlValue();
}
qint64 QTdMessageForwardInfo::fromMessageId() const
{
    return m_fromMessageId.value();
}

QString QTdMessageForwardInfo::displayedName() const
{
    if (m_origin)
    {
        return m_origin->originSummary();
    }
    return gettext("Unknown origin");

}

void QTdMessageForwardInfo::unmarshalJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }
    QTdObject::unmarshalJson(json);
    const QJsonObject origin = json["origin"].toObject();
    m_origin.reset(QTdMessageForwardOriginFactory::create(origin, this));
    connect(m_origin.data(), &QTdMessageForwardOrigin::forwardOriginChanged, this, &QTdMessageForwardInfo::forwardInfoChanged);
    m_date = json["date"].toInt();
    m_fromChatId = json["forwarded_from_chat_id"].toVariant().toLongLong();
    m_fromMessageId = json["forwarded_from_message_id"].toVariant().toLongLong();
    emit forwardInfoChanged();
}
