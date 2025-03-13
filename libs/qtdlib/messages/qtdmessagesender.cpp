#include "qtdmessagesender.h"

#include "common/qtdhelpers.h"

#include "qtdmessagesenderuser.h"
#include "qtdmessagesenderchat.h"

QTdMessageSender::QTdMessageSender(QObject *parent)
    : QAbstractInt64Id(parent)
{
}

QString QTdMessageSender::avatarColor() const
{
    return QTdHelpers::avatarColor(id());
}

QTdMessageSenderUnimplemented::QTdMessageSenderUnimplemented(QObject *parent)
    : QTdMessageSender(parent)
{
}

QString QTdMessageSenderUnimplemented::displayName() const
{
    return QString("unimplemented");
}

QString QTdMessageSenderUnimplemented::fullName() const
{
    return QString("unimplemented");
}

QTdPhoto *QTdMessageSenderUnimplemented::photo() const
{
    return nullptr;
}

QString QTdMessageSenderUnimplemented::initials() const
{
    return "";
}

QTdMessageSender *QTdMessageSenderFactory::create(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();
    QTdMessageSender *result = Q_NULLPTR;

    if (type == "messageSenderUser") {
        result = new QTdMessageSenderUser(parent);
    } else if (type == "messageSenderChat") {
        result = new QTdMessageSenderChat(parent);
    } else {
        result = new QTdMessageSenderUnimplemented(parent);
    }
    result->unmarshalJson(json);
    return result; 
}
