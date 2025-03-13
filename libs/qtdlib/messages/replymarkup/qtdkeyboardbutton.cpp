#include "common/qabstracttdobject.h"
#include "qtdkeyboardbutton.h"

QTdKeyboardButton::QTdKeyboardButton(QObject *parent)
    : QTdObject(parent)
    , m_type(Q_NULLPTR)
{
}

QString QTdKeyboardButton::text() const
{
    return m_text;
}

void QTdKeyboardButton::unmarshalJson(const QJsonObject &json)
{
    QTdObject::unmarshalJson(json);
    m_text = json["text"].toString();
    m_type.reset(QTdKeyboardButtonTypeFactory::create(json["type"].toObject(), this));   
}

QTdKeyboardButtonType *QTdKeyboardButton::type() const
{
    return m_type.data();
}

QTdKeyboardRow::QTdKeyboardRow(QObject *parent)
    : QTdObject(parent)
{
    m_row.reset(new QQmlObjectListModel<QTdKeyboardButton>(this));
}

QObject *QTdKeyboardRow::row() const
{
    return m_row.data();
}

void QTdKeyboardRow::unmarshalJson(const QJsonValue &json)
{
    const QJsonArray row = json.toArray();
    for (const QJsonValue &v : row) {
        QTdKeyboardButton *button = new QTdKeyboardButton;
        button->unmarshalJson(v.toObject());
        m_row->append(button);
    }
}
