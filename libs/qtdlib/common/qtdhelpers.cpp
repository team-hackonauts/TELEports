#include "qtdhelpers.h"
#include "client/qtdclient.h"
#include <QJsonArray>

QString QTdHelpers::formatDate(const QDateTime &dt)
{
    const QDateTime now = QDateTime::currentDateTimeUtc().toLocalTime();
    const QDateTime localdt = dt.toLocalTime();
    auto daysDiff = now.daysTo(localdt);
    if (daysDiff == 0) {
        return localdt.toString("hh:mm");
    } else if (daysDiff > -7) {
        return localdt.toString("ddd hh:mm");
    } else
        return localdt.toString("dd.MM.yy hh:mm");
}

QStringList QTdHelpers::colorPalette = {
    "#a93226",
    "#cb4335",
    "#884ea0",
    "#7d3c98",
    "#2471a3",
    "#2e86c1",
    "#17a589",
    "#138d75",
    "#229954",
    "#28b463",
    "#d4ac0d",
    "#d68910",
    "#ca6f1e",
    "#ba4a00",
    "#839192",
    "#707b7c"
};

QString QTdHelpers::avatarColor(qint64 userId)
{
    return colorPalette.at(abs((int)(userId % colorPalette.size())));
}

QString QTdHelpers::selfColor()
{
    return "#65aadd";
}

QRegExp QTdHelpers::rxEntity;
QRegExp QTdHelpers::rxLinebreaks;

void QTdHelpers::getEntitiesFromMessage(const QString &messageText, QString &plainText, QJsonArray &entities)
{
    if (rxEntity.isEmpty()) {
        rxEntity = QRegExp("\\*\\*.+\\*\\*|__.+__|```[^`].+```|`[^`\\n\\r]+`");
        rxEntity.setMinimal(true);
        rxLinebreaks = QRegExp("\\n|\\r");
    }
    int offsetCorrection = 0;
    int pos = 0;
    int actualPos = pos - offsetCorrection;
    plainText = messageText;
    while ((pos = rxEntity.indexIn(messageText, pos)) != -1) {
        auto match = rxEntity.cap(0);
        QJsonObject entity;
        entity["@type"] = "textEntity";
        actualPos = pos - offsetCorrection;
        entity["offset"] = actualPos;
        QJsonObject entityType;
        if (match.startsWith("*")) {
            int contentLength = rxEntity.matchedLength() - 4;
            entityType["@type"] = "textEntityTypeBold";
            entity["length"] = contentLength;
            plainText = plainText.replace(actualPos, 2, "");
            plainText = plainText.replace(actualPos + contentLength, 2, "");
            offsetCorrection += 4;
        } else if (match.startsWith("_")) {
            int contentLength = rxEntity.matchedLength() - 4;
            entityType["@type"] = "textEntityTypeItalic";
            entity["length"] = contentLength;
            plainText = plainText.replace(actualPos, 2, "");
            plainText = plainText.replace(actualPos + contentLength, 2, "");
            offsetCorrection += 4;
        } else if (match.startsWith("```")) {
            if (messageText.at(pos - 1) == "`") {
                pos += rxEntity.matchedLength();
                continue;
            }
            qDebug() << "rxEntity.matchedLength()" << rxEntity.matchedLength();
            int contentLength = rxEntity.matchedLength() - 6;
            entityType["@type"] = "textEntityTypePre";
            entity["length"] = contentLength;
            plainText = plainText.replace(actualPos, 3, "");
            if (plainText.at(actualPos - 1) != "\n") {
                plainText = plainText.insert(actualPos, "\n");
                entity["offset"] = actualPos + 1;
                offsetCorrection--;
            }
            actualPos = pos - offsetCorrection;
            plainText = plainText.replace(actualPos + contentLength, 3, "");
            if (plainText.at(actualPos + contentLength) != "\n") {
                plainText = plainText.insert(actualPos + contentLength, "\n");
                offsetCorrection--;
            }
            offsetCorrection += 6;
        } else if (match.startsWith("`")) {
            if (messageText.at(pos - 1) == "`") {
                pos += rxEntity.matchedLength();
                continue;
            }
            qDebug() << (messageText.at(pos-1) != "`");
            int contentLength = rxEntity.matchedLength() - 2;
            entityType["@type"] = "textEntityTypeCode";
            entity["length"] = contentLength;
            plainText = plainText.replace(actualPos, 1, "");
            plainText = plainText.replace(actualPos + contentLength, 1, "");
            offsetCorrection += 2;
        }
        entity["type"] = entityType;
        entities << entity;
        pos += rxEntity.matchedLength();
    }
}

QJsonArray QTdHelpers::formatPlainTextMessage(const QString &message, QString &plainText)
{
    //First call tdlib to markup all complex entities
    auto parseRequest = QJsonObject{
        { "@type", "getTextEntities" },
        { "text", message }
    };
    auto result = QTdClient::instance()->exec(parseRequest);
    result.waitForFinished();

    QJsonArray entities = result.result()["entities"].toArray();

    //Then do the text formatting
    QTdHelpers::getEntitiesFromMessage(message, plainText, entities);

    return entities;
}

QString QTdHelpers::initials(const QString &title)
{
    if (title != "") {
        QString initials = "";
        QStringList parts = title.trimmed().split(" ", QString::SkipEmptyParts);
        for (int i = 0; i < parts.size(); i++) {
            initials += parts[i][0].toUpper();
            if (initials.length() >= 2) {
                break;
            }
        }
        if (initials.length() < 2) {
            initials = title.trimmed().left(2).toUpper();
        }
        return initials;
    }
    return "";
}
