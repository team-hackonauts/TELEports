#include "qtdpolloption.h"

QTdPollOption::QTdPollOption(QObject *parent)
    : QTdObject(parent)
    , m_text("")
    , m_votes(0)
    , m_percentage(0)
    , m_isChosen(false)
    , m_isBeingChosen(false)

{
    setType(POLL_OPTION);
}

QString QTdPollOption::text() {
    return m_text;
}

qint32 QTdPollOption::votes() {
    return m_votes;
}

qint32 QTdPollOption::percentage() {
    return m_percentage;
}

bool QTdPollOption::isChosen() {
    return m_isChosen;
}

bool QTdPollOption::isBeingChosen() {
    return m_isBeingChosen;
}

void QTdPollOption::setIsBeingChosen(bool value) {
    m_isBeingChosen = value;
    emit dataChanged();
}

int QTdPollOption::optionIndex() const {
    return m_optionIndex;
}

void QTdPollOption::setOptionIndex(int value) {
    m_optionIndex = value;
}

void QTdPollOption::unmarshalJson(const QJsonObject &json)
{
    m_text = json["text"].toString();
    m_votes = qint32(json["voter_count"].toInt());
    m_percentage = qint32(json["vote_percentage"].toInt());
    m_isChosen = json["is_chosen"].toBool();
    m_isBeingChosen = json["is_being_chosen"].toBool();

    emit dataChanged();
}

