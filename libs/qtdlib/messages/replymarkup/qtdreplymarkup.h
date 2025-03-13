#ifndef QTDREPLYMARKUP_H
#define QTDREPLYMARKUP_H

#include "common/qabstracttdobject.h"
#include "qtdkeyboardbutton.h"
#include "models/QmlObjectListModel.h"
#include <QPointer>

/**
 * @brief The QTdReplyMarkup class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_reply_markup.html
 */
class QTdReplyMarkup : public QTdObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdReplyMarkup)
public:
    explicit QTdReplyMarkup(QObject *parent = nullptr);

};

/**
 * @brief The QTdReplyMarkupForceReply class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1reply_markup_force_reply.html
 */
class QTdReplyMarkupForceReply : public QTdReplyMarkup
{
    Q_OBJECT
    Q_PROPERTY(bool isPersonal READ isPersonal NOTIFY isPersonalChanged)
public:
    explicit QTdReplyMarkupForceReply(QObject *parent = nullptr);
    bool isPersonal() const;

    void unmarshalJson(const QJsonObject &json) override;
signals:
    void isPersonalChanged();

private:
    bool m_isPersonal;
};

/**
 * @brief The QTdReplyMarkupInlineKeyboard class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1reply_markup_inline_keyboard.html
 */
class QTdReplyMarkupInlineKeyboard : public QTdReplyMarkup
{
    Q_OBJECT
    Q_PROPERTY(QObject *rows READ rows NOTIFY rowsChanged)
public:
    explicit QTdReplyMarkupInlineKeyboard(QObject *parent = nullptr);
    QObject *rows();

    void unmarshalJson(const QJsonObject &json) override;
signals:
    void rowsChanged();

private:
    QPointer<QQmlObjectListModel<QTdKeyboardRow>> m_rows;
};

/**
 * @brief The QTdReplyMarkupRemoveKeyboard class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1reply_markup_remove_keyboard.html
 */
class QTdReplyMarkupRemoveKeyboard : public QTdReplyMarkup
{
    Q_OBJECT
    Q_PROPERTY(bool isPersonal READ isPersonal NOTIFY isPersonalChanged)
public:
    explicit QTdReplyMarkupRemoveKeyboard(QObject *parent = nullptr);
    bool isPersonal() const;

    void unmarshalJson(const QJsonObject &json) override;
signals:
    void isPersonalChanged();

private:
    bool m_isPersonal;
};

/**
 * @brief The QTdReplyMarkupShowKeyboard class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1reply_markup_show_keyboard.html
 */
class QTdReplyMarkupShowKeyboard : public QTdReplyMarkup
{
    Q_OBJECT
    Q_PROPERTY(QObject *rows READ rows NOTIFY markupChanged)
    Q_PROPERTY(bool resizeKeyboard READ resizeKeyboard NOTIFY markupChanged)
    Q_PROPERTY(bool oneTime READ oneTime NOTIFY markupChanged)
    Q_PROPERTY(bool isPersonal READ isPersonal NOTIFY markupChanged)
public:
    explicit QTdReplyMarkupShowKeyboard(QObject *parent = nullptr);

    QObject *rows() const;
    bool resizeKeyboard() const;
    bool oneTime() const;
    bool isPersonal() const;

    void unmarshalJson(const QJsonObject &json) override;
signals:
    void markupChanged();

private:
    QPointer<QQmlObjectListModel<QTdKeyboardRow>> m_rows;
    bool m_resizeKeyboard;
    bool m_oneTime;
    bool m_isPersonal;
};

struct QTdReplyMarkupFactory
{
    static QTdReplyMarkup *create(const QJsonObject &data, QObject *parent);
};
#endif // QTDREPLYMARKUP_H
