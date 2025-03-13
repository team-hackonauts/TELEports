#ifndef QTDKEYBOARDBUTTONTYPE_H
#define QTDKEYBOARDBUTTONTYPE_H

#include "common/qabstracttdobject.h"

/**
 * @brief The QTdKeyboardButtonType class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_keyboard_button_type.html
 */
class QTdKeyboardButtonType : public QTdObject
{
    Q_OBJECT
public:
    explicit QTdKeyboardButtonType(QObject *parent = nullptr);
};

/**
 * @brief The QTdKeyboardButtonTypeRequestLocation class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1keyboard_button_type_request_location.html
 */
class QTdKeyboardButtonTypeRequestLocation : public QTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QTdKeyboardButtonTypeRequestLocation(QObject *parent = nullptr);
};

/**
 * @brief The QTdKeyboardButtonTypeRequestPhoneNumber class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1keyboard_button_type_request_phone_number.html
 */
class QTdKeyboardButtonTypeRequestPhoneNumber : public QTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QTdKeyboardButtonTypeRequestPhoneNumber(QObject *parent = nullptr);
};

/**
 * @brief The QTdKeyboardButtonTypeRequestPoll class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1keyboard_button_type_request_poll.html
 */
class QTdKeyboardButtonTypeRequestPoll : public QTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QTdKeyboardButtonTypeRequestPoll(QObject *parent = nullptr);
};

/**
 * @brief The QTdKeyboardButtonTypeText class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1keyboard_button_type_text.html
 */
class QTdKeyboardButtonTypeText : public QTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QTdKeyboardButtonTypeText(QObject *parent = nullptr);
};

class QTdKeyboardButtonTypeWebApp: public QTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QTdKeyboardButtonTypeWebApp(QObject *parent = nullptr);
};

class QTdInlineKeyboardButtonTypeBuy : public QTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QTdInlineKeyboardButtonTypeBuy(QObject *parent = nullptr);
};

class QTdInlineKeyboardButtonTypeCallback : public QTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QTdInlineKeyboardButtonTypeCallback(QObject *parent = nullptr);
};

class QTdInlineKeyboardButtonTypeCallbackGame : public QTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QTdInlineKeyboardButtonTypeCallbackGame(QObject *parent = nullptr);
};

class QTdInlineKeyboardButtonTypeCallbackWithPassword : public QTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QTdInlineKeyboardButtonTypeCallbackWithPassword(QObject *parent = nullptr);
};

class QTdInlineKeyboardButtonTypeLoginUrl : public QTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QTdInlineKeyboardButtonTypeLoginUrl(QObject *parent = nullptr);
};

class QTdInlineKeyboardButtonTypeSwitchinline : public QTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QTdInlineKeyboardButtonTypeSwitchinline(QObject *parent = nullptr);
};

class QTdInlineKeyboardButtonTypeUrl : public QTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QTdInlineKeyboardButtonTypeUrl(QObject *parent = nullptr);
};

class QTdInlineKeyboardButtonTypeUser : public QTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QTdInlineKeyboardButtonTypeUser(QObject *parent = nullptr);
};

class QTdInlineKeyboardButtonTypeWebApp : public QTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QTdInlineKeyboardButtonTypeWebApp(QObject *parent = nullptr);
};


struct QTdKeyboardButtonTypeFactory
{
    static QTdKeyboardButtonType *create(const QJsonObject &data, QObject *parent);
};

#endif // QTDKEYBOARDBUTTONTYPE_H
