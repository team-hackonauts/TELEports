#ifndef QTDKEYBOARDBUTTON_H
#define QTDKEYBOARDBUTTON_H

#include "common/qabstracttdobject.h"
#include "qtdkeyboardbuttontype.h"
#include "models/QmlObjectListModel.h"
#include <QScopedPointer>
#include <QJsonArray>

/**
 * @brief The QTdKeyboardButton class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1keyboard_button.html
 */
class QTdKeyboardButton : public QTdObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdKeyboardButton)
    Q_PROPERTY(QString text READ text NOTIFY textChanged)
    Q_PROPERTY(QTdKeyboardButtonType *type READ type NOTIFY typeChanged)
public:
    explicit QTdKeyboardButton(QObject *parent = nullptr);

    QString text() const;
    QTdKeyboardButtonType *type() const;
    void unmarshalJson(const QJsonObject &json) override;

signals:
    void textChanged();
    void typeChanged();

private:
    QString m_text;
    QScopedPointer<QTdKeyboardButtonType> m_type;
};

/**
 * @brief The QTdKeyboardRow class
 *
 * not present in telegram docs, to abstact easier the array of array of (pointers to) QTdKeyboardButton
 */
class QTdKeyboardRow : public QTdObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdKeyboardRow)
    Q_PROPERTY(QObject *row READ row NOTIFY rowChanged)
public:
    explicit QTdKeyboardRow(QObject *parent = nullptr);
    QObject *row() const;
    void unmarshalJson(const QJsonValue &json);

signals:
    void rowChanged();

private:
    QScopedPointer<QQmlObjectListModel<QTdKeyboardButton>> m_row;
};

#endif // QTDKEYBOARDBUTTON_H
