#include "utils/i18n.h"
#include "qtduserstatus.h"

QTdUserStatus::QTdUserStatus(QObject *parent)
    : QTdObject(parent)
{
}

QTdUserStatusEmpty::QTdUserStatusEmpty(QObject *parent)
    : QTdUserStatus(parent)
{
    setType(USER_STATUS_EMPTY);
}

QString QTdUserStatusEmpty::toString() const
{
    return "";
}

QTdUserStateLastMonth::QTdUserStateLastMonth(QObject *parent)
    : QTdUserStatus(parent)
{
    setType(USER_STATUS_LAST_MONTH);
}

QString QTdUserStateLastMonth::toString() const
{
    return gettext("Last seen one month ago");
}

QTdUserStatusLastWeek::QTdUserStatusLastWeek(QObject *parent)
    : QTdUserStatus(parent)
{
    setType(USER_STATUS_LAST_WEEK);
}

QString QTdUserStatusLastWeek::toString() const
{
    return gettext("Last seen one week ago");
}

QTdUserStatusOffline::QTdUserStatusOffline(QObject *parent)
    : QTdUserStatus(parent)
{
    setType(USER_STATUS_OFFLINE);
}

QDateTime QTdUserStatusOffline::wasOnline() const
{
    return m_wasOnline;
}

QString QTdUserStatusOffline::toString() const
{
    return QString(gettext("Last seen ")) + m_wasOnline.toString(gettext("dd.MM.yy hh:mm"));
}

void QTdUserStatusOffline::unmarshalJson(const QJsonObject &json)
{
    QTdUserStatus::unmarshalJson(json);
    m_wasOnline.setTime_t(qint32(json["was_online"].toInt()));
    emit wasOnlineChanged(m_wasOnline);
}

QTdUserStatusOnline::QTdUserStatusOnline(QObject *parent)
    : QTdUserStatus(parent)
{
    setType(USER_STATUS_ONLINE);
}

QDateTime QTdUserStatusOnline::expires() const
{
    return m_expires;
}

QString QTdUserStatusOnline::toString() const
{
    return gettext("Online");
}

void QTdUserStatusOnline::unmarshalJson(const QJsonObject &json)
{
    QTdUserStatus::unmarshalJson(json);
    m_expires.setTime_t(qint32(json["expires"].toInt()));
    emit expiresChanged();
}

QTdUserStatusRecently::QTdUserStatusRecently(QObject *parent)
    : QTdUserStatus(parent)
{
    setType(USER_STATUS_RECENTLY);
}

QString QTdUserStatusRecently::toString() const
{
    return gettext("Seen recently");
}
