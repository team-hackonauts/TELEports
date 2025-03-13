#include "qtdstickerset.h"
#include "client/qtdclient.h"

QTdStickerSet::QTdStickerSet(QObject *parent)
    : QTdObject(parent)
    , m_id(0)
    , m_title("")
    , m_name("")
    , m_thumbnail(new QTdThumbnail())
    , m_format(new QTdStickerFormat())
    , m_type(new QTdStickerType())
    , m_hasThumbnail(false)
    , m_isAnimated(false)
    , m_detailsLoaded(false)
    , m_isInstalled(false)
    , m_isArchived(false)
    , m_isOfficial(false)
{
    m_stickers.reset(new QQmlObjectListModel<QTdSticker>(this, "", "id"));
    connect(QTdClient::instance(), &QTdClient::stickerSet, this, &QTdStickerSet::handleDetails);
}

QString QTdStickerSet::title() const
{
    return m_title;
}

QString QTdStickerSet::name() const
{
    return m_name;
}

QTdThumbnail *QTdStickerSet::thumbnail() const
{
    return m_thumbnail.data();
}

bool QTdStickerSet::hasThumbnail() const
{
    return m_hasThumbnail;
}

bool QTdStickerSet::isAnimated() const
{
    return m_isAnimated;
}

QObject *QTdStickerSet::qmlModel() const
{
    return m_stickers.data();
}

void QTdStickerSet::loadDetails() const
{
    QTdClient::instance()->send(QJsonObject{
            { "@type", "getStickerSet" },
            { "set_id", m_id.toJsonValue() },
    });
}

void QTdStickerSet::handleDetails(const QJsonObject &json)
{
    if (m_detailsLoaded) {
        return;
    }
    const QJsonValue value = json["id"];
    QTdInt64 tdId;
    tdId = value;
    if (tdId.value() == m_id.value()) {
        this->unmarshalJson(json);
        m_detailsLoaded = true;
    }
}

void QTdStickerSet::unmarshalJson(const QJsonObject &json)
{
    QTdObject::unmarshalJson(json);
    m_id = json["id"];
    m_title = json["title"].toString();
    m_name = json["name"].toString();
    if (json.contains("thumbnail")) {
        m_thumbnail->unmarshalJson(json["thumbnail"].toObject());
        m_hasThumbnail = true;
    } else {
        m_hasThumbnail = false;
    }
    m_format.reset(QTdStickerFormatFactory::create(json["format"].toObject(), this));
    m_type.reset(QTdStickerTypeFactory::create(json["type"].toObject(), this));
    m_isAnimated = json["is_animated"].toBool();
    m_isInstalled = json["is_installed"].toBool();
    m_isArchived = json["is_archived"].toBool();
    m_isOfficial = json["is_official"].toBool();

    if (json.contains("covers") && !m_hasThumbnail) {
        auto coversArray = json["covers"].toArray();
        if (!coversArray.isEmpty()) {
            auto coverSticker = coversArray[0].toObject();
            m_thumbnail->unmarshalJson(coverSticker["thumbnail"].toObject());
        }
    }
    if (json.contains("stickers")) {
        auto stickersArray = json["stickers"].toArray();
        for (auto stickerJSON : stickersArray) {
            QTdSticker *sticker = new QTdSticker(this);
            sticker->unmarshalJson(stickerJSON.toObject());
            m_stickers->append(sticker);
        }
    }
    emit stickerSetChanged();
}
