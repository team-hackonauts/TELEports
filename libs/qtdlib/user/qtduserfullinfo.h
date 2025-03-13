#ifndef QTDUSERFULLINFO_H
#define QTDUSERFULLINFO_H

#include <QObject>
#include <QList>
#include "qtduserstatus.h"
#include "qtdprofilephoto.h"
#include "qtdusertype.h"

/**
 * @brief The QTdUserFullInfo class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1user_full_info.html
 */
class QTdUserFullInfo : public QTdObject
{
    Q_OBJECT
    Q_PROPERTY(bool isBlocked READ isBlocked NOTIFY userFullInfoChanged)
    Q_PROPERTY(bool canBeCalled READ canBeCalled NOTIFY userFullInfoChanged)
    Q_PROPERTY(bool hasPrivateCalls READ hasPrivateCalls NOTIFY userFullInfoChanged)
    Q_PROPERTY(QString bio READ bio NOTIFY userFullInfoChanged)
    Q_PROPERTY(QString shareText READ shareText NOTIFY userFullInfoChanged)
    Q_PROPERTY(qint32 groupInCommonCount READ groupInCommonCount NOTIFY userFullInfoChanged)

    //TODO Implement botInfo
    //Q_PROPERTY(QTdBotInfo *botInfo...)

public:
    explicit QTdUserFullInfo(QObject *parent = nullptr);

    bool isBlocked() const;
    bool canBeCalled() const;
    bool hasPrivateCalls() const;
    QString bio() const;
    QString shareText() const;
    qint32 groupInCommonCount() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void userFullInfoChanged();

private:
    Q_DISABLE_COPY(QTdUserFullInfo)
    bool m_isBlocked;
    bool m_canBeCalled;
    bool m_hasPrivateCalls;
    QString m_bio;
    QString m_shareText;
    qint32 m_groupInCommonCount;
};

#endif // QTDUSERFULLINFO_H
