#include "qtdmessagecontentfactory.h"
#include <QDebug> // TEMP
#include "content/qtdmessageanimation.h"
#include "content/qtdmessageaudio.h"
#include "content/qtdmessagebasicgroupchatcreate.h"
#include "content/qtdmessagecall.h"
#include "content/qtdmessagechataddmembers.h"
#include "content/qtdmessagechatchangephoto.h"
#include "content/qtdmessagechatchangetitle.h"
#include "content/qtdmessagechatdeletemember.h"
#include "content/qtdmessagechatdeletephoto.h"
#include "content/qtdmessagechatjoinbylink.h"
#include "content/qtdmessagechatsetmessageautodeletetime.h"
#include "content/qtdmessagepinmessage.h"
#include "content/qtdmessagechatupgradefrom.h"
#include "content/qtdmessagechatupgradeto.h"
#include "content/qtdmessagescreenshottaken.h"
#include "content/qtdmessagedocument.h"
#include "content/qtdmessagelocation.h"
#include "content/qtdmessagephoto.h"
#include "content/qtdmessagesticker.h"
#include "content/qtdmessagesupergroupchatcreate.h"
#include "content/qtdmessagetext.h"
#include "content/qtdmessagevideo.h"
#include "content/qtdmessagevideonote.h"
#include "content/qtdmessagevoicenote.h"
#include "content/qtdmessagecustomserviceaction.h"
#include "content/qtdmessagecontactregistered.h"
#include "content/qtdmessagecontact.h"
#include "content/qtdmessagepoll.h"
#include "content/qtdmessageunsupported.h"
#include "utils/i18n.h"

QTdMessageContent *QTdMessageContentFactory::create(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();
    // TODO: create a map of QMap<@type, QTdObject::Type> so we can do fast lookups and
    // switch on the type. Otherwise this is/elseif is going to get huge supporting all content
    // types
    if (type == "messageText") {
        return new QTdMessageText(parent);
    } else if (type == "messageSticker" || type == "messageAnimatedEmoji") {
        return new QTdMessageSticker(parent);
    } else if (type == "messagePhoto") {
        return new QTdMessagePhoto(parent);
    } else if (type == "messageAnimation") {
        return new QTdMessageAnimation(parent);
    } else if (type == "messageAudio") {
        return new QTdMessageAudio(parent);
    } else if (type == "messageDocument") {
        return new QTdMessageDocument(parent);
    } else if (type == "messageLocation") {
        return new QTdMessageLocation(parent);
    } else if (type == "messageVideo") {
        return new QTdMessageVideo(parent);
    } else if (type == "messageVideoNote") {
        return new QTdMessageVideoNote(parent);
    } else if (type == "messageVoiceNote") {
        return new QTdMessageVoiceNote(parent);
    } else if (type == "messageChatJoinByLink") {
        return new QTdMessageChatJoinByLink(parent);
    } else if (type == "messageBasicGroupChatCreate") {
        return new QTdMessageBasicGroupChatCreate(parent);
    } else if (type == "messageCall") {
        return new QTdMessageCall(parent);
    } else if (type == "messageScreenshotTaken") {
        return new QTdMessageScreenshotTaken(parent);
    } else if (type == "messageChatAddMembers") {
        return new QTdMessageChatAddMembers(parent);
    } else if (type == "messageChatChangePhoto") {
        return new QTdMessageChatChangePhoto(parent);
    } else if (type == "messageChatChangeTitle") {
        return new QTdMessageChatChangeTitle(parent);
    } else if (type == "messageChatDeleteMember") {
        return new QTdMessageChatDeleteMember(parent);
    } else if (type == "messageChatDeletePhoto") {
        return new QTdMessageChatDeletePhoto(parent);
    } else if (type == "messageChatSetMessageAutoDeleteTime") {
        return new QTdMessageChatSetMessageAutoDeleteTime(parent);
    } else if (type == "messageChatUpgradeFrom") {
        return new QTdMessageChatUpgradeFrom(parent);
    } else if (type == "messageChatUpgradeTo") {
        return new QTdMessageChatUpgradeTo(parent);
    } else if (type == "messageCustomServiceAction") {
        return new QTdMessageCustomServiceAction(parent);
    } else if (type == "messageContactRegistered") {
        return new QTdMessageContactRegistered(parent);
    } else if (type == "messageUnsupported") {
        return new QTdMessageUnsupported(parent);
    } else if (type == "messageSupergroupChatCreate") {
        return new QTdMessageSuperGroupChatCreate(parent);
    } else if (type == "messagePinMessage") {
        return new QTdMessagePinMessage(parent);
    } else if (type == "messagePoll") {
        return new QTdMessagePoll(parent);
    } else if (type == "messageContact") {
        return new QTdMessageContact(parent);
/*
      else if (type == "messageWebsiteConnected") {
        return new QTdMessageWebsiteConnected(parent);
    } else if (type == "messageVenue") {
        return new QTdMessageVenue(parent);
    } else if (type == "messagePassportDataReceived") {
        return new QTdMessagePassportDataReceived(parent);
    } else if (type == "messagePassportDataSent") {
        return new QTdMessagePassportDataSent(parent);
    } else if (type == "messagePaymentSuccessful") {
        return new QTdMessagePaymentSuccesssful(parent);
    } else if (type == "messagePaymentSuccessfulBot") {
        return new QTdMessagePaymentSuccessfulBot"(parent);
    } else if (type == "messageLinkInfo") {
        return new QTdMessageLinkInfo(parent);
    } else if (type == "messageInvoice") {
        return new QTdMessageInvoice(parent);
    } else if (type == "messageGame") {
        return new QTdMessageGame(parent);
    } else if (type == "messageGameScore") {
        return new QTdMessageGameScore(parent);
    } else if (type == "message") {
        return new QTdMessage(parent);
    } else if (type == "message") {
        return new QTdMessage(parent);
    } else if (type == "message") {
        return new QTdMessage(parent);
    } else if (type == "message") {
        return new QTdMessage(parent);
    }

*/
    }

    qWarning() << "Received unknown message type" << type << json;
    QScopedPointer<QTdMessageContent> uknMSg(new QTdMessageContent(parent));
    uknMSg->setTypeText(gettext("Unimplemented:"));
    uknMSg->setInfoText(type);
    return uknMSg.take();
}
