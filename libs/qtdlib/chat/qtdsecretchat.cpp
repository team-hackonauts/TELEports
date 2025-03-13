#include "qtdsecretchat.h"
#include <QScopedPointer>
#include "chat/requests/qtdgetsecretchatrequest.h"
#include "client/qtdclient.h"

QTdSecretChat::QTdSecretChat(QObject *parent)
    : QTdChat(parent)
    , m_secretChatId(0)
    , m_userId(0)
    , m_isOutbound(false)
    , m_ttl(0)
    , m_layer(0)
    , m_state(Q_NULLPTR)
{
    connect(QTdClient::instance(), &QTdClient::secretChat, this, &QTdSecretChat::updateSecretChat);
    connect(QTdClient::instance(), &QTdClient::updateSecretChat, this, &QTdSecretChat::updateSecretChat);
    m_hashMap = new QQmlObjectListModel<QTdHashRow>(this);
}

QString QTdSecretChat::qmlSecretChatId() const
{
    return m_secretChatId.toQmlValue();
}

qint64 QTdSecretChat::secretChatId() const
{
    return m_secretChatId.value();
}

QString QTdSecretChat::qmlUserId() const
{
    return m_userId.toQmlValue();
}

qint64 QTdSecretChat::userId() const
{
    return m_userId.value();
}

bool QTdSecretChat::isOutbound() const
{
    return m_isOutbound;
}

bool QTdSecretChat::isWritable() const
{
    auto result = qobject_cast<QTdSecretChatStateReady *>(m_state);
    return result != nullptr;
}

bool QTdSecretChat::isPending() const
{
    auto result = qobject_cast<QTdSecretChatStatePending *>(m_state);
    return result != nullptr;
}

bool QTdSecretChat::isClosed() const
{
    auto result = qobject_cast<QTdSecretChatStateClosed *>(m_state);
    return result != nullptr;
}

qint32 QTdSecretChat::ttl() const
{
    return m_ttl;
}

QString QTdSecretChat::keyHashString() const
{
    QString hashString = m_keyHash.toUpper();
    hashString = hashString.left(64);
    for (int i = 62; i > 0; i-=2) {
        if (i % 16 == 0) {
            hashString = hashString.insert(i, "\n");
        } else if (i % 8 == 0) {
            hashString = hashString.insert(i, "    ");
        } else
            hashString = hashString.insert(i, " ");
    }
    return hashString;
}
QObject *QTdSecretChat::keyHashMap() const
{
    if (m_hashMap->isEmpty()) {
        for (int i = 1; i <= 12; i++) {
            QScopedPointer<QTdHashRow> hashRow(new QTdHashRow);
            bool ok;
            QByteArray stringRow = m_keyHash;
            //subdivide the QByteArray in twelve parts of 6 hex char each (3 bytes)
            stringRow.truncate(i * 6);
            stringRow = stringRow.right(6);
            //convert the QByteArray to binary (hex -> int -> binary)
            stringRow = QByteArray::number(stringRow.toInt(&ok, 16), 2);
            // prepend "0" to reach a length of 24 bits
            stringRow.prepend(24 - stringRow.length(), *"0");
            hashRow->setRow(stringRow);
            m_hashMap->append(hashRow.take());
        }
    }
    return m_hashMap;
}

qint32 QTdSecretChat::layer() const
{
    return m_layer;
}

QTdSecretChatState *QTdSecretChat::state() const
{
    return m_state;
}

void QTdSecretChat::onChatOpened()
{
    getSecretChatData();
    QTdChat::onChatOpened();
}

void QTdSecretChat::getSecretChatData()
{
    QTdChatTypeSecret *secret = qobject_cast<QTdChatTypeSecret *>(chatType());
    if (secret) {
        QScopedPointer<QTdGetSecretChatRequest> req(new QTdGetSecretChatRequest);
        req->setSecretChatId(secret->secretChatId());
        QTdClient::instance()->send(req.data());
    }
    else
        qWarning() << "Secret chat is null!";
}

void QTdSecretChat::updateSecretChat(const QJsonObject &data)
{
    QTdChatTypeSecret *secret = qobject_cast<QTdChatTypeSecret *>(chatType());
    const qint64 sid = data["id"].toVariant().toLongLong();
    if (sid != secret->secretChatId()) {
        return;
    }

    m_secretChatId = sid;
    m_userId = data["user_id"].toVariant().toLongLong();
    if (m_state) {
        delete m_state;
        m_state = nullptr;
    }
    const QJsonObject state = data["state"].toObject();
    const QString type = state["@type"].toString();
    if (type == "secretChatStateClosed") {
        m_state = new QTdSecretChatStateClosed(this);
    } else if (type == "secretChatStatePending") {
        m_state = new QTdSecretChatStatePending(this);
    } else if (type == "secretChatStateReady") {
        m_state = new QTdSecretChatStateReady(this);
    }
    if (m_state) {
        m_state->unmarshalJson(state);
        emit stateChanged(m_state);
        emit isWritableChanged();
    }
    m_isOutbound = data["is_outbound"].toBool();
    m_ttl = qint32(data["ttl"].toInt());
    m_keyHash = QByteArray::fromBase64(data["key_hash"].toString().toUtf8()).toHex();
    m_layer = qint32(data["layer"].toInt());
    emit secretChatChanged();
}

QTdHashRow::QTdHashRow(QObject *parent)
    : QTdObject(parent)
    , m_hashRow(Q_NULLPTR)
{
    m_hashRow = new QQmlObjectListModel<QTdHashPixel>(this);
}
QObject *QTdHashRow::hashRow() const
{
    return m_hashRow;
}
void QTdHashRow::setRow(QByteArray stringRow) const
{
    QVector<QColor> colors(4);
    colors[0] = QColor("#ffffffff");
    colors[1] = QColor("#ffd5e6f3");
    colors[2] = QColor("#ff2d5775");
    colors[3] = QColor("#ff2f99c9");
    for (int i = 1; i <= 3; i++) {
        QByteArray byte = stringRow;
        byte.truncate(i * 8);
        byte = byte.right(8);
        for (int j = byte.length() / 2; j > 0; j--) {
            QScopedPointer<QTdHashPixel> hashPixel(new QTdHashPixel);
            bool ok;
            // cut byte to get only 2 bits
            byte.truncate(j * 2);
            QByteArray pixel = byte.right(2);
            //convert binary value into integer
            int pixelInt = pixel.toInt(&ok, 2);
            QColor pixelColor = colors[pixelInt];
            hashPixel->setHashPixelColor(pixelColor);
            m_hashRow->append(hashPixel.take());
        }
    }
}

QTdHashPixel::QTdHashPixel(QObject *parent)
    : QTdObject(parent)
{
    m_hashPixelColor = QColor("darkCyan");
}
QColor QTdHashPixel::hashPixelColor() const
{
    return m_hashPixelColor;
}
void QTdHashPixel::setHashPixelColor(QColor hashPixelColor)
{
    if (m_hashPixelColor == hashPixelColor)
        return;

    m_hashPixelColor = hashPixelColor;
}
