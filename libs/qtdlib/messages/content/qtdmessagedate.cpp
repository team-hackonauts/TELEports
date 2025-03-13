#include "qtdmessagedate.h"
#include "utils/i18n.h"

QTdMessageDate::QTdMessageDate(QObject *parent)
    : QTdMessageContent(parent)
    , m_date(0)
{
    setType(MESSAGE_DATE);
}

QDateTime QTdMessageDate::date() const
{
    return QDateTime::fromTime_t(m_date);
}

QString QTdMessageDate::dateString() const
{
    if (date().date() == QDate::currentDate()) {
        return gettext("Today");
    } else if (date().date() == QDate::currentDate().addDays(-1)) {
        return gettext(gettext("Yesterday"));
    } else if (date().date() > QDate::currentDate().addDays(-7)) {
        //TRANSLATORS: String in date separator label. For messages within a week: full weekday name
        return date().toString(gettext("dddd"));
    } else if (date().date().year() < QDate::currentDate().year()) {
        //TRANSLATORS: String in date separator label. For messages of pas years: date number, month name and year
        return date().toString(gettext("dd MMMM yyyy"));
    } else {
        //TRANSLATORS: String in date separator label. For messages older that a week but within the current year: date number and month name
        return date().toString(gettext("dd MMMM"));
    }
}

void QTdMessageDate::setDate(const qint32 &date)
{
    if (date == m_date) {
        return;
    }
    m_date = date;
    emit dataChanged();
}
