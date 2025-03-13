#ifndef QTDMESSAGELINK_H
#define QTDMESSAGELINK_H

#include <QObject>
#include "common/qabstracttdobject.h"

/**
 * @brief The QTdMessageLink class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_link.html
 */
class QTdMessageLink : public QTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString link READ link NOTIFY messageLinkChanged)
    Q_PROPERTY(bool isPublic READ isPublic NOTIFY messageLinkChanged)

public:
    explicit QTdMessageLink(QObject *parent = nullptr);

    QString link() const;
    bool isPublic() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void messageLinkChanged();

private:
    QString m_link { "" };
    bool m_is_public { false };

};

#endif // QTDMESSAGELINK_H