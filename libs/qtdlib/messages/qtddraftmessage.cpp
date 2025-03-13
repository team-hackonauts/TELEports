#include "qtddraftmessage.h"
#include "requests/content/qtdinputmessagetext.h"
#include <QJsonObject>

QTdDraftMessage::QTdDraftMessage(QObject *parent)
    : QTdObject(parent)
    , m_replyToMessageId(0)
    , m_inputMessageText(new QTdInputMessageText)
{
}

QString QTdDraftMessage::qmlReplyToMessageId() const
{
    return m_replyToMessageId.toQmlValue();
}
qint64 QTdDraftMessage::replyToMessageId() const
{
    return m_replyToMessageId.value();
}

QTdInputMessageText *QTdDraftMessage::inputMessageText() const
{
    return m_inputMessageText.data();
}

void QTdDraftMessage::unmarshalJson(const QJsonObject &json)
{
    QTdObject::unmarshalJson(json);
    if (!json.isEmpty()) {
        m_replyToMessageId = json["reply_to_message_id"].toVariant().toLongLong();
        emit replyToMessageIdChanged();
        const QJsonObject inputMessageText = json["input_message_text"].toObject();
        if (inputMessageText.isEmpty()) {
            m_inputMessageText.reset(new QTdInputMessageText);
            emit inputMessageTextChanged();
        } else {
            const QString inputMessageTextType = inputMessageText["@type"].toString();
            //this should always be of type inputMessageText.
            if (inputMessageTextType == "inputMessageText") {
                m_inputMessageText->unmarshalJson(inputMessageText);
                emit inputMessageTextChanged();
            }
        }
    }
}

void QTdDraftMessage::setReplyToMessageId(const qint64 &replyToMessageId)
{
    m_replyToMessageId = replyToMessageId;
    emit replyToMessageIdChanged();
}
void QTdDraftMessage::setInputMessageText(QTdInputMessageText *inputMessageText)
{
    m_inputMessageText.reset(inputMessageText);
    emit inputMessageTextChanged();
}
QJsonObject QTdDraftMessage::marshalJson()
{

    return QJsonObject {
        { "@type", "draftMessage" },
        { "input_message_text", m_inputMessageText->marshalJson() },
        { "reply_to_message_id", replyToMessageId() }
    };
}
