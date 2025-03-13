#include "qtdusernames.h"

#include <QJsonObject>
#include <QJsonArray>

QTdUsernames::QTdUsernames(QObject *parent)
    : QTdObject(parent)
{
}

QTdUsernames::QTdUsernames(QObject *parent, QList<QString> activeUsernames_, QList<QString> disabledUsernames_, QString editableUsername_)
    :         m_activeUsernames(activeUsernames_),
        m_disabledUsernames(disabledUsernames_),
        m_editableUsername(editableUsername_) {
}

QList<QString> QTdUsernames::activeUsernames() const {
    return m_activeUsernames;
}

void QTdUsernames::setActiveUsernames(QList<QString> value) {
    if (m_activeUsernames != value) {
        m_activeUsernames = value;
        emit dataChanged();
    }
}

QList<QString> QTdUsernames::disabledUsernames() const {
    return m_disabledUsernames;
}

void QTdUsernames::setDisabledUsernames(QList<QString> value) {
    if (m_disabledUsernames != value) {
        m_disabledUsernames = value;
        emit dataChanged();
    }
}

QString QTdUsernames::editableUsername() const {
    return m_editableUsername;
}

void QTdUsernames::setEditableUsername(QString value) {
    if (m_editableUsername != value) {
        m_editableUsername = value;
        emit dataChanged();
    }
}

void QTdUsernames::unmarshalJson(const QJsonObject &json) {
    QJsonObject jsonObj;
    QJsonArray jsonArray;

    QTdObject::unmarshalJson(json);
    jsonArray = json["active_usernames"].toArray();
    for (const QJsonValue &jsonValue : jsonArray) {
        m_activeUsernames << jsonValue.toString();
    }
    jsonArray = json["disabled_usernames"].toArray();
    for (const QJsonValue &jsonValue : jsonArray) {
        m_disabledUsernames << jsonValue.toString();
    }
    m_editableUsername = json["editable_username"].toString();

    emit dataChanged();
}
