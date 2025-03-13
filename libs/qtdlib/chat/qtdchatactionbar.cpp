#include "qtdchatactionbar.h"
#include "utils/i18n.h"

QTdChatActionBar::QTdChatActionBar(QObject *parent)
    : QTdObject(parent)
{

}

QTdChatActionBarAddContact::QTdChatActionBarAddContact(QObject *parent)
    : QTdChatActionBar(parent)
{
    setType(CHAT_ACTIONBAR_ADDCONTACT);
}

QTdChatActionBarInviteMembers::QTdChatActionBarInviteMembers(QObject *parent)
    : QTdChatActionBar(parent)
{
    setType(CHAT_ACTIONBAR_INVITEMEMBERS);
}

QTdChatActionBarJoinRequest::QTdChatActionBarJoinRequest(QObject *parent)
    : QTdChatActionBar(parent)
{
    setType(CHAT_ACTIONBAR_JOINREQUEST);
}

void QTdChatActionBarJoinRequest::unmarshalJson(const QJsonObject &json)
{
    QTdChatActionBar::unmarshalJson(json);
    m_title = json["title"].toString();
    m_isChannel = json["is_channel"].toBool();
    m_requestDate = json["request_date"].toInt();
}

QString QTdChatActionBarJoinRequest::title() {
    return m_title;
}

bool QTdChatActionBarJoinRequest::isChannel() {
    return m_isChannel;
}

qint32 QTdChatActionBarJoinRequest::requestDate() {
    return m_requestDate;
}

QTdChatActionBarReportAddBlock::QTdChatActionBarReportAddBlock(QObject *parent)
    : QTdChatActionBar(parent)
{
    setType(CHAT_ACTIONBAR_REPORTADDBLOCK);
}

void QTdChatActionBarReportAddBlock::unmarshalJson(const QJsonObject &json)
{
    QTdChatActionBar::unmarshalJson(json);
    m_canUnarchive = json["can_unarchive"].toBool();
    m_distance = json["distance"].toInt();
}

bool QTdChatActionBarReportAddBlock::canUnarchive() {
    return m_canUnarchive;
}

qint32 QTdChatActionBarReportAddBlock::distance() {
    return m_distance;
}

QTdChatActionBarReportSpam::QTdChatActionBarReportSpam(QObject *parent)
    : QTdChatActionBar(parent)
{
    setType(CHAT_ACTIONBAR_REPORTSPAM);
}

bool QTdChatActionBarReportSpam::canUnarchive() {
    return m_canUnarchive;
}

void QTdChatActionBarReportSpam::unmarshalJson(const QJsonObject &json)
{
    QTdChatActionBar::unmarshalJson(json);
    m_canUnarchive = json["can_unarchive"].toBool();
}

QTdChatActionBarReportUnrelatedLocation::QTdChatActionBarReportUnrelatedLocation(QObject *parent)
    : QTdChatActionBar(parent)
{
    setType(CHAT_ACTIONBAR_REPORTUNRELATEDLOCATION);
}

QTdChatActionBarSharePhoneNumber::QTdChatActionBarSharePhoneNumber(QObject *parent)
    : QTdChatActionBar(parent)
{
    setType(CHAT_ACTIONBAR_SHAREPHONENUMBER);
}

QTdChatActionBar *QTdChatActionBarFactory::create(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();
    QTdChatActionBar *chatActionBar = Q_NULLPTR;
    if (type == "chatActionBarAddContact") {
        chatActionBar = new QTdChatActionBarAddContact(parent);
    } else if (type == "chatActionBarInviteMembers") {
        chatActionBar = new QTdChatActionBarInviteMembers(parent);
    } else if (type == "chatActionBarJoinRequest") {
        chatActionBar = new QTdChatActionBarJoinRequest(parent);
    } else if (type == "chatActionBarReportAddBlock") {
        chatActionBar = new QTdChatActionBarReportAddBlock(parent);
    } else if (type == "chatActionBarReportSpam") {
        chatActionBar = new QTdChatActionBarReportSpam(parent);
    } else if (type == "chatActionBarReportUnrelatedLocation") {
        chatActionBar = new QTdChatActionBarReportUnrelatedLocation(parent);
    } else if (type == "chatActionBarSharePhoneNumber") {
        chatActionBar = new QTdChatActionBarSharePhoneNumber(parent);
    }
    if (chatActionBar) {
        chatActionBar->unmarshalJson(json);
    }
    return chatActionBar;
}
