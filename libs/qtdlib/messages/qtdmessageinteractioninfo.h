#ifndef QTDMESSAGEINTERACTIONINFO_H
#define QTDMESSAGEINTERACTIONINFO_H

#include <QObject>
#include "common/qabstracttdobject.h"
#include "common/qtdint.h"

/**
 * @brief The QTdMessageInteractionInfo
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_interaction_info.html
 */
class QTdMessageInteractionInfo : public QTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString viewCount READ qmlViewCount NOTIFY interactionInfoChanged)
    Q_PROPERTY(QString forwardCount READ qmlForwardCount NOTIFY interactionInfoChanged)
    // TODO: add QTdMessageReplyInfo
public:
    explicit QTdMessageInteractionInfo(QObject *parent = nullptr);

    qint32 viewCount() const;
    QString qmlViewCount() const;
    qint32 forwardCount() const;
    QString qmlForwardCount() const;

    void unmarshalJson(const QJsonObject &json) override;
signals:
    void interactionInfoChanged();

private:
    Q_DISABLE_COPY(QTdMessageInteractionInfo)

    QTdInt32 m_viewCount;
    QTdInt32 m_forwardCount;
};

#endif // QTDMESSAGEINTERACTIONINFO_H
