#include "pushhelper.h"
#include "../common/auxdb/avatarmaptable.h"
#include "i18n.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QStringList>
#include <iterator>
#include <QStandardPaths>

PushHelper::PushHelper(const QString appId, const QString infile, const QString outfile, QObject *parent)
    : QObject(parent)
    , mInfile(infile)
    , mOutfile(outfile)
    , m_postalClient(new PostalClient(appId))
    , m_auxdb(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).append("/auxdb"),
              QGuiApplication::applicationDirPath().append("/assets"), this)
{
    setlocale(LC_ALL, "");
    textdomain(GETTEXT_DOMAIN.toStdString().c_str());

}

void PushHelper::process()
{
    QJsonObject pushMessage = readPushMessage(mInfile);
    mPostalMessage = pushToPostalMessage(pushMessage);
    writePostalMessage(mPostalMessage, mOutfile);
}

QJsonObject PushHelper::readPushMessage(const QString &filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QString val = file.readAll();
    file.close();
    return QJsonDocument::fromJson(val.toUtf8()).object();
}

void PushHelper::writePostalMessage(const QJsonObject &postalMessage, const QString &filename)
{
    QFile out;
    out.setFileName(filename);
    out.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);

    QTextStream(&out) << QJsonDocument(postalMessage).toJson();
    out.close();
}

QJsonObject PushHelper::pushToPostalMessage(const QJsonObject &push)
{
    /**
    * Only show a simple notification bubble.
    * TODO: Add more information about the notification
    */

    QString summary = "";
    QString body = "";
    QJsonObject message = push["message"].toObject();
    QJsonObject custom = message["custom"].toObject();

    QString key = "";
    if (message.keys().contains("loc_key")) {
        key = message["loc_key"].toString(); // no-i18n
    }

    QJsonArray args;
    if (message.keys().contains("loc_args")) {
        args = message["loc_args"].toArray(); // no-i18n
    }

    qint64 chatId = 0;
    QString tag;
    if (custom.keys().contains("from_id")) {
        tag = custom["from_id"].toString();
        chatId = tag.toLong();
    } else if (custom.keys().contains("chat_id")) {
        tag = custom["chat_id"].toString();
        chatId = tag.toLong() * -1;
    } else if (custom.keys().contains("channel_id")) {
        tag = custom["channel_id"].toString();
        chatId = (tag.toLong() + 1000000000000) * -1;
    }

    //Display emblem counter correctly for unread messages
    qint32 count = 0;
    if (message.keys().contains("badge")) {
        count = message["badge"].toInt(); // no-i18n
    } else if (push.keys().contains("notification")) {
        // Legacy. Notification section is only used to retrieve the unread count.
        count = push["notification"] // no-i18n
                        .toObject()["emblem-counter"] // no-i18n
                        .toObject()["count"] // no-i18n
                        .toInt();
    }
    qint64 totalCount = 0;
    if (m_auxdb.getAvatarMapTable()) {
        m_auxdb.getAvatarMapTable()->setUnreadMapEntry(chatId, count);
        totalCount = m_auxdb.getAvatarMapTable()->getTotalUnread();
    }
    m_postalClient->setCount(totalCount);
    m_postalClient->clearPersistent(QStringList(QString::number(chatId)));

    //Early bail-out: Telegram server just removes notification, message has been read elsewhere
    if (key == "" || key == "READ_HISTORY") {
        return QJsonObject();
    }

    // TRANSLATORS: Application name.
    QString tg = QString(N_("TELEports")); // no-i18n

    summary = args[0].toString();

    if (key == "MESSAGE_TEXT" || key == "CHANNEL_MESSAGE_TEXT") { // no-i18n

        body = args[1].toString();

    } else if (key == "MESSAGE_NOTEXT" || key == "CHANNEL_MESSAGE_NOTEXT") { // no-i18n

        body = N_("sent you a message");

    } else if (key == "MESSAGE_PHOTO" || key == "CHANNEL_MESSAGE_PHOTO") { // no-i18n

        body = N_("sent you a photo");

    } else if (key == "MESSAGE_STICKER" || key == "CHANNEL_MESSAGE_STICKER") { // no-i18n

        body = N_("sent you a sticker");

    } else if (key == "MESSAGE_VIDEO" || key == "CHANNEL_MESSAGE_VIDEO") { // no-i18n

        body = N_("sent you a video");

    } else if (key == "MESSAGE_DOC" || key == "CHANNEL_MESSAGE_DOC") { // no-i18n

        body = N_("sent you a document");

    } else if (key == "MESSAGE_AUDIO" || key == "CHANNEL_MESSAGE_AUDIO") { // no-i18n

        body = N_("sent you an audio message");

    } else if (key == "MESSAGE_VOICE_NOTE" || key == "CHANNEL_MESSAGE_VOICE_NOTE") { // no-i18n

        body = N_("sent you a voice message");

    } else if (key == "MESSAGE_CONTACT" || key == "CHANNEL_MESSAGE_CONTACT") { // no-i18n

        body = N_("shared a contact with you");

    } else if (key == "MESSAGE_GEO" || key == "CHANNEL_MESSAGE_GEO") { // no-i18n

        body = N_("sent you a map");

    } else if (key == "CHAT_MESSAGE_TEXT") { // no-i18n

        summary = args[1].toString();
        body = QString(N_("%1: %2")).arg(args[0].toString()).arg(args[2].toString()); // no-i18n

    } else if (key == "CHAT_MESSAGE_NOTEXT") { // no-i18n

        summary = args[1].toString();
        body = QString(N_("%1 sent a message to the group")).arg(args[0].toString());

    } else if (key == "CHAT_MESSAGE_PHOTO") { // no-i18n

        summary = args[1].toString();
        body = QString(N_("%1 sent a photo to the group")).arg(args[0].toString());

    } else if (key == "CHAT_MESSAGE_STICKER") { // no-i18n

        summary = args[1].toString();
        body = QString(N_("%1 sent a sticker to the group")).arg(args[0].toString());

    } else if (key == "CHAT_MESSAGE_VIDEO") { // no-i18n

        summary = args[1].toString();
        body = QString(N_("%1 sent a video to the group")).arg(args[0].toString());

    } else if (key == "CHAT_MESSAGE_DOC") { // no-i18n

        summary = args[1].toString();
        body = QString(N_("%1 sent a document to the group")).arg(args[0].toString());

    } else if (key == "CHAT_MESSAGE_AUDIO") { // no-i18n

        summary = args[1].toString();
        body = QString(N_("%1 sent a voice message to the group")).arg(args[0].toString());

    } else if (key == "CHAT_MESSAGE_GIF") { // no-i18n

        summary = tg;
        body = QString(N_("%1 sent a GIF to the group")).arg(args[0].toString());

    } else if (key == "CHAT_MESSAGE_CONTACT") { // no-i18n

        summary = args[1].toString();
        body = QString(N_("%1 sent a contact to the group")).arg(args[0].toString());

    } else if (key == "CHAT_MESSAGE_GEO") { // no-i18n

        summary = args[1].toString();
        body = QString(N_("%1 sent a map to the group")).arg(args[0].toString());

    } else if (key == "CHAT_CREATED") { // no-i18n

        summary = args[1].toString();
        body = QString(N_("%1 invited you to the group")).arg(args[0].toString());

    } else if (key == "CHAT_TITLE_EDITED") { // no-i18n

        summary = args[1].toString();
        body = QString(N_("%1 changed group name")).arg(args[0].toString());

    } else if (key == "CHAT_PHOTO_EDITED") { // no-i18n

        summary = args[1].toString();
        body = QString(N_("%1 changed group photo")).arg(args[0].toString());

    } else if (key == "CHAT_ADD_MEMBER") { // no-i18n

        summary = args[1].toString();
        // TRANSLATORS: Notification message saying: person A invited person B (to a group)
        body = QString(N_("%1 invited %2")).arg(args[0].toString()).arg(args[2].toString());

    } else if (key == "CHAT_ADD_YOU") { // no-i18n

        summary = args[1].toString();
        body = QString(N_("%1 invited you to the group")).arg(args[0].toString());

    } else if (key == "CHAT_DELETE_MEMBER") { // no-i18n

        summary = args[1].toString();
        // TRANSLATORS: Notification message saying: person A removed person B (from a group)
        body = QString(N_("%1 removed %2")).arg(args[0].toString()).arg(args[2].toString());

    } else if (key == "CHAT_DELETE_YOU") { // no-i18n

        summary = args[1].toString();
        body = QString(N_("%1 removed you from the group")).arg(args[0].toString());

    } else if (key == "CHAT_LEFT") { // no-i18n

        summary = args[1].toString();
        body = QString(N_("%1 has left the group")).arg(args[0].toString());

    } else if (key == "CHAT_RETURNED") { // no-i18n

        summary = args[1].toString();
        body = QString(N_("%1 has returned to the group")).arg(args[0].toString());

    } else if (key == "GEOCHAT_CHECKIN") { // no-i18n

        // TRANSLATORS: This format string tells location, like: @ McDonals, New York
        summary = QString(N_("@ %1")).arg(args[1].toString());
        // TRANSLATORS: This format string tells who has checked in (in a geographical location).
        body = QString(N_("%1 has checked-in")).arg(args[0].toString());

    } else if (key == "CONTACT_JOINED") { // no-i18n

        summary = tg;
        // TRANSLATORS: This format string tells who has just joined Telegram.
        body = QString(N_("%1 joined Telegram!")).arg(args[0].toString());

    } else if (key == "AUTH_UNKNOWN") { // no-i18n

        summary = args[0].toString();
        body = N_("New login from unrecognized device");

    } else if (key == "AUTH_REGION") { // no-i18n

        // TRANSLATORS: This format string indicates new login of: (device name) at (location).
        summary = QString(N_("%1 @ %2")).arg(args[0].toString()).arg(args[1].toString());
        body = N_("New login from unrecognized device");

    } else if (key == "CONTACT_PHOTO") { // no-i18n

        body = N_("updated profile photo");

    } else if (key == "ENCRYPTION_REQUEST") { // no-i18n

        summary = tg;
        body = N_("You have a new message");

    } else if (key == "ENCRYPTION_ACCEPT") { // no-i18n

        summary = tg;
        body = N_("You have a new message");

    } else if (key == "ENCRYPTED_MESSAGE") { // no-i18n

        summary = tg;
        body = N_("You have a new message");

    } else if (key == "PINNED_TEXT") { // no-i18n

        summary = tg;
        body = QString(N_("%1 pinned a message")).arg(args[0].toString());

    } else {
        qDebug() << "Unhandled push type: " << key; // no-i18n
        return QJsonObject();
    }

    //Prepare action URL to open app
    QJsonArray actions = QJsonArray();
    QString actionUri = QString("teleports://chat/%1").arg(chatId);
    actions.append(actionUri);

    //Load the correct avatar
    QString avatar = QString("telegram-symbolic");
    if (m_auxdb.getAvatarMapTable()) {
        QString avatarPath = m_auxdb.getAvatarMapTable()->getAvatarPathbyId(chatId);
        if (avatarPath != "") {
            avatar = QString("file://").append(avatarPath);
        }
    }

    QJsonObject notification{
        { "card", QJsonObject{
                          { "summary", summary },
                          { "body", body },
                          { "popup", true },
                          { "persist", true },
                          { "actions", actions },
                          { "icon", avatar },
                  } },
        { "sound", true },
        { "tag", QString::number(chatId) },
        { "vibrate", true }
    };
    return QJsonObject{
        { "notification", notification }
    };
}
