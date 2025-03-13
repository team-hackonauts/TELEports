#include "qtdkeyboardbuttontype.h"

#include <QDebug>
#include "common/qabstracttdobject.h"

QTdKeyboardButtonType::QTdKeyboardButtonType(QObject *parent)
    : QTdObject(parent)
{
}

QTdKeyboardButtonTypeRequestLocation::QTdKeyboardButtonTypeRequestLocation(QObject *parent)
    : QTdKeyboardButtonType(parent)
{
}

QTdKeyboardButtonTypeRequestPhoneNumber::QTdKeyboardButtonTypeRequestPhoneNumber(QObject *parent)
    : QTdKeyboardButtonType(parent)
{
}

QTdKeyboardButtonTypeRequestPoll::QTdKeyboardButtonTypeRequestPoll(QObject *parent)
    : QTdKeyboardButtonType(parent)
{
}

QTdKeyboardButtonTypeText::QTdKeyboardButtonTypeText(QObject *parent)
    : QTdKeyboardButtonType(parent)
{
}

QTdKeyboardButtonTypeWebApp::QTdKeyboardButtonTypeWebApp(QObject *parent)
    : QTdKeyboardButtonType(parent)
{
}

QTdInlineKeyboardButtonTypeBuy::QTdInlineKeyboardButtonTypeBuy(QObject *parent)
    : QTdKeyboardButtonType(parent)
{
}

QTdInlineKeyboardButtonTypeCallback::QTdInlineKeyboardButtonTypeCallback(QObject *parent)
    : QTdKeyboardButtonType(parent)
{
}

QTdInlineKeyboardButtonTypeCallbackGame::QTdInlineKeyboardButtonTypeCallbackGame(QObject *parent)
    : QTdKeyboardButtonType(parent)
{
}

QTdInlineKeyboardButtonTypeCallbackWithPassword::QTdInlineKeyboardButtonTypeCallbackWithPassword(QObject *parent)
    : QTdKeyboardButtonType(parent)
{
}

QTdInlineKeyboardButtonTypeLoginUrl::QTdInlineKeyboardButtonTypeLoginUrl(QObject *parent)
    : QTdKeyboardButtonType(parent)
{
}

QTdInlineKeyboardButtonTypeSwitchinline::QTdInlineKeyboardButtonTypeSwitchinline(QObject *parent)
    : QTdKeyboardButtonType(parent)
{
}

QTdInlineKeyboardButtonTypeUrl::QTdInlineKeyboardButtonTypeUrl(QObject *parent)
    : QTdKeyboardButtonType(parent)
{
}

QTdInlineKeyboardButtonTypeUser::QTdInlineKeyboardButtonTypeUser(QObject *parent)
    : QTdKeyboardButtonType(parent)
{
}

QTdInlineKeyboardButtonTypeWebApp::QTdInlineKeyboardButtonTypeWebApp(QObject *parent)
    : QTdKeyboardButtonType(parent)
{
}

QTdKeyboardButtonType *QTdKeyboardButtonTypeFactory::create(const QJsonObject &data, QObject *parent)
{
    const QString type = data["@type"].toString();
    QTdKeyboardButtonType *result = Q_NULLPTR;

    if (type == "keyboardButtonTypeRequestLocation") {
        result = new QTdKeyboardButtonTypeRequestLocation(parent);
    } else if (type == "keyboardButtonTypeRequestPhoneNumber") {
        result = new QTdKeyboardButtonTypeRequestPhoneNumber(parent);
    } else if (type == "keyboardButtonTypeRequestPoll") {
        result = new QTdKeyboardButtonTypeRequestPoll(parent);
    } else if (type == "keyboardButtonTypeText") {
        result = new QTdKeyboardButtonTypeText(parent);
    } else if (type == "keyboardButtonTypeWebApp") {
        result = new QTdKeyboardButtonTypeWebApp(parent);
    } else if (type == "inlineKeyboardButtonTypeBuy") {
        result = new QTdInlineKeyboardButtonTypeBuy(parent);
    } else if (type == "inlineKeyboardButtonTypeCallback") {
        result = new QTdInlineKeyboardButtonTypeCallback(parent);
    } else if (type == "inlineKeyboardButtonTypeCallbackGame") {
        result = new QTdInlineKeyboardButtonTypeCallbackGame(parent);
    } else if (type == "inlineKeyboardButtonTypeCallbackWithPassword") {
        result = new QTdInlineKeyboardButtonTypeCallbackWithPassword(parent);
    } else if (type == "inlineKeyboardButtonTypeLoginUrl") {
        result = new QTdInlineKeyboardButtonTypeLoginUrl(parent);
    } else if (type == "inlineKeyboardButtonTypeSwitchinline") {
        result = new QTdInlineKeyboardButtonTypeSwitchinline(parent);
    } else if (type == "inlineKeyboardButtonTypeUrl") {
        result = new QTdInlineKeyboardButtonTypeUrl(parent);
    } else if (type == "inlineKeyboardButtonTypeUser") {
        result = new QTdInlineKeyboardButtonTypeUser(parent);
    } else if (type == "inlineKeyboardButtonTypeWebApp") {
        result = new QTdInlineKeyboardButtonTypeWebApp(parent);
    } else {
        qWarning() << "Unknown keyboard button type:" << type;
    }

    if (result) {
        result->unmarshalJson(data);
    }

    return result;
}