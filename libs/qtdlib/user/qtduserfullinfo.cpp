#include "qtduserfullinfo.h"
#include "qtduserstatusfactory.h"
#include "common/qtdhelpers.h"
#include "client/qtdclient.h"

QTdUserFullInfo::QTdUserFullInfo(QObject *parent)
    : m_isBlocked(false)
    , m_canBeCalled(false)
    , m_hasPrivateCalls(false)
    , m_bio(QString())
    , m_shareText(QString())
    , m_groupInCommonCount(0)
{
    setType(USER_FULL_INFO);
}

void QTdUserFullInfo::unmarshalJson(const QJsonObject &json)
{
    QTdObject::unmarshalJson(json);
    m_isBlocked = json["is_blocked"].toBool();
    m_canBeCalled = json["can_be_called"].toBool();
    m_hasPrivateCalls = json["has_private_calls"].toBool();
    m_bio = json["bio"].toString();
    m_shareText = json["share_text"].toString();
    m_groupInCommonCount = json["group_in_common_count"].toInt();

    emit userFullInfoChanged();
}

bool QTdUserFullInfo::isBlocked() const
{
    return m_isBlocked;
}

bool QTdUserFullInfo::canBeCalled() const
{
    return m_canBeCalled;
}

bool QTdUserFullInfo::hasPrivateCalls() const
{
    return m_hasPrivateCalls;
}

QString QTdUserFullInfo::bio() const
{
    return m_bio;
}

QString QTdUserFullInfo::shareText() const
{
    return m_shareText;
}

qint32 QTdUserFullInfo::groupInCommonCount() const
{
    return m_groupInCommonCount;
}
