#include "qtdtextentitytype.h"

QTdTextEntityType::QTdTextEntityType(QObject *parent)
    : QTdObject(parent)
{
}

QString QTdTextEntityType::additionalInfo() const
{
    return m_additionalInfo;
}

QTdTextEntityType *QTdTextEntityFactory::create(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();
    if (type == "textEntityTypeBold") {
        return new QTdTextEntityTypeBold(parent);
    } else if (type == "textEntityTypeBotCommand") {
        return new QTdTextEntityTypeBotCommand(parent);
    } else if (type == "textEntityTypeCashtag") {
        return new QTdTextEntityTypeCashtag(parent);
    } else if (type == "textEntityTypeCode") {
        return new QTdTextEntityTypeCode(parent);
    } else if (type == "textEntityTypeEmailAddress") {
        return new QTdTextEntityTypeEmailAddress(parent);
    } else if (type == "textEntityTypeHashtag") {
        return new QTdTextEntityTypeHashtag(parent);
    } else if (type == "textEntityTypeItalic") {
        return new QTdTextEntityTypeItalic(parent);
    } else if (type == "textEntityTypeMention") {
        return new QTdTextEntityTypeMention(parent);
    } else if (type == "textEntityTypeMentionName") {
        return new QTdTextEntityTypeMentionName(parent);
    } else if (type == "textEntityTypePhoneNumber") {
        return new QTdTextEntityTypePhoneNumber(parent);
    } else if (type == "textEntityTypePre") {
        return new QTdTextEntityTypePre(parent);
    } else if (type == "textEntityTypePreCode") {
        return new QTdTextEntityTypePreCode(parent);
    } else if (type == "textEntityTypeStrikethrough") {
        return new QTdTextEntityTypeStrikethrough(parent);
    } else if (type == "textEntityTypeUnderline") {
        return new QTdTextEntityTypeUnderline(parent);
    } else if (type == "textEntityTypeTextUrl") {
        auto entityTypeTextUrl = new QTdTextEntityTypeTextUrl(parent);
        entityTypeTextUrl->unmarshalJson(json);
        return entityTypeTextUrl;
    } else if (type == "textEntityTypeUrl") {
        return new QTdTextEntityTypeUrl(parent);
    } else if (type == "textEntityTypeSpoiler") {
        return new QTdTextEntityTypeSpoiler(parent);
    }
    return new QTdTextEntityType(parent);
}
