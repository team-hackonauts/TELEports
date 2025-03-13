#ifndef QTDDRAFTMESSAGE_H
#define QTDDRAFTMESSAGE_H

#include "requests/content/qtdinputmessagetext.h"
#include "common/qtdint.h"
#include <QScopedPointer>

/**
 * @brief The QTdDraftMessage class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1draft_message.html
 */
class QTdDraftMessage : public QTdObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdDraftMessage)
    Q_PROPERTY(QString replyToMessageId READ qmlReplyToMessageId NOTIFY replyToMessageIdChanged)
    Q_PROPERTY(QTdInputMessageText *inputMessageText READ inputMessageText NOTIFY inputMessageTextChanged)
public:
    explicit QTdDraftMessage(QObject *parent = nullptr);

    QString qmlReplyToMessageId() const;
    qint64 replyToMessageId() const;
    QTdInputMessageText *inputMessageText() const;
    void unmarshalJson(const QJsonObject &json) override;
    void setReplyToMessageId(const qint64 &replyToMessageId);
    void setInputMessageText(QTdInputMessageText *inputMessageText);
    QJsonObject marshalJson();

signals:
    void replyToMessageIdChanged();
    void inputMessageTextChanged();

private:
    QTdInt64 m_replyToMessageId;
    QScopedPointer<QTdInputMessageText> m_inputMessageText;
};

#endif // QTDDRAFTMESSAGE_H
