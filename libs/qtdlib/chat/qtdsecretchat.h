#ifndef QTDSECRETCHAT_H
#define QTDSECRETCHAT_H

#include <QObject>
#include <QPointer>
#include "qtdchat.h"
#include "qtdsecretchatstate.h"
#include <QColor>

class QTdHashPixel : public QTdObject
{
   Q_OBJECT
   Q_DISABLE_COPY(QTdHashPixel)
   Q_PROPERTY(QColor hashPixelColor READ hashPixelColor NOTIFY hashPixelChanged)
public:
   explicit QTdHashPixel(QObject *parent = nullptr);
   QColor hashPixelColor() const;
   void setHashPixelColor(QColor hashPixelColor);
signals:
   void hashPixelChanged();

private:
   QColor m_hashPixelColor;
};

class QTdHashRow : public QTdObject
{
   Q_OBJECT
   Q_DISABLE_COPY(QTdHashRow)
   Q_PROPERTY(QObject *hashRow READ hashRow NOTIFY hashRowChanged)
public:
   explicit QTdHashRow(QObject *parent = nullptr);
   QObject *hashRow() const;
   void setRow(QByteArray stringRow) const;
signals:
   void hashRowChanged();

private:
   QPointer<QQmlObjectListModel<QTdHashPixel>> m_hashRow;
};


class QTdSecretChat : public QTdChat
{
    Q_OBJECT
    Q_PROPERTY(QString secretChatId READ qmlSecretChatId NOTIFY secretChatChanged)
    Q_PROPERTY(QString userId READ qmlUserId NOTIFY secretChatChanged)
    Q_PROPERTY(QTdSecretChatState *state READ state NOTIFY stateChanged)
    Q_PROPERTY(bool isOutbound READ isOutbound NOTIFY secretChatChanged)
    Q_PROPERTY(qint32 ttl READ ttl NOTIFY secretChatChanged)
    Q_PROPERTY(QString keyHashString READ keyHashString NOTIFY secretChatChanged)
    Q_PROPERTY(QObject *keyHashMap READ keyHashMap NOTIFY secretChatChanged)
    Q_PROPERTY(qint32 layer READ layer NOTIFY secretChatChanged)
    Q_PROPERTY(bool isPending READ isPending NOTIFY stateChanged)
    Q_PROPERTY(bool isClosed READ isClosed NOTIFY stateChanged)

public:
    explicit QTdSecretChat(QObject *parent = nullptr);

    QString qmlSecretChatId() const;
    qint64 secretChatId() const;
    QString qmlUserId() const;
    qint64 userId() const;
    bool isOutbound() const;
    bool isWritable() const override;
    bool isPending() const;
    bool isClosed() const;
    qint32 ttl() const;
    QString keyHashString() const;
    QObject *keyHashMap() const;
    qint32 layer() const;

    QTdSecretChatState *state() const;

    void getSecretChatData();

signals:
    void secretChatChanged();
    void stateChanged(QTdSecretChatState *state);

private:
    virtual void onChatOpened();

private slots:
    void updateSecretChat(const QJsonObject &data);

private:
    QTdInt64 m_secretChatId;
    QTdInt64 m_userId;
    bool m_isOutbound;
    qint32 m_ttl;
    QByteArray m_keyHash;
    QPointer<QQmlObjectListModel<QTdHashRow>> m_hashMap;
    qint32 m_layer;
    QPointer<QTdSecretChatState> m_state;
};

#endif // QTDSECRETCHAT_H
