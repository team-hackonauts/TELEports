#ifndef QTDMESSAGEFORWARDINFO_H
#define QTDMESSAGEFORWARDINFO_H

#include "common/qabstractint64id.h"
#include <QDateTime>
#include <QScopedPointer>
#include "qtdmessageforwardorigin.h"

/**
 * @brief The QTdMessageForwardInfo class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_forward_info.html
 */
class QTdMessageForwardInfo : public QTdObject
{
    Q_OBJECT
    Q_PROPERTY(QTdMessageForwardOrigin *origin READ origin NOTIFY forwardInfoChanged)
    Q_PROPERTY(QDateTime date READ qmlDate NOTIFY forwardInfoChanged)
    Q_PROPERTY(QString fromChatId READ qmlFromChatId NOTIFY forwardInfoChanged)
    Q_PROPERTY(QString fromMessageId READ qmlFromMessageId NOTIFY forwardInfoChanged)
    // These aren't original properties of the tdlib message class but we can
    // can make life easier for use in QML.
    Q_PROPERTY(QString displayedName READ displayedName NOTIFY forwardInfoChanged)
public:
    explicit QTdMessageForwardInfo(QObject *parent = nullptr);

    QTdMessageForwardOrigin *origin() const;
    QDateTime qmlDate() const;
    qint32 date() const;
    QString qmlFromChatId() const;
    qint64 fromChatId() const;
    QString qmlFromMessageId() const;
    qint64 fromMessageId() const;
    QString displayedName() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void forwardInfoChanged();

private:
    QScopedPointer<QTdMessageForwardOrigin> m_origin;
    qint32 m_date;
    QTdInt64 m_fromChatId;
    QTdInt64 m_fromMessageId;
    QString m_displayedName;
};

#endif // QTDMESSAGEFORWARDINFO_H
