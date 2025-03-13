#include "qtdpolltype.h"

QTdPollType::QTdPollType(QObject *parent)
    : QTdObject(parent)
{
}

qint32 QTdPollType::correctOption() const {
    return -1;
}

QTdFormattedText *QTdPollType::explanation() const {
    return Q_NULLPTR;
}

bool QTdPollType::allowMultipleAnswers() const {
    return false;
}


QTdPollTypeQuiz::QTdPollTypeQuiz(QObject *parent)
    : QTdPollType(parent)
    , m_correctOption(-1)
    , m_explanation(new QTdFormattedText)
{
    setType(POLL_TYPE_QUIZ);
}

qint32 QTdPollTypeQuiz::correctOption() const {
    return m_correctOption;
}


QTdFormattedText *QTdPollTypeQuiz::explanation() const {
    return m_explanation.data();
}

void QTdPollTypeQuiz::unmarshalJson(const QJsonObject &json)
{
    m_correctOption = qint32(json["correct_option_id"].toInt());
    m_explanation->unmarshalJson((json["explanation"].toObject()));
}

QTdPollTypeRegular::QTdPollTypeRegular(QObject *parent)
    : QTdPollType(parent)
    , m_allowMultipleAnswers(false)
{
    setType(POLL_TYPE_REGULAR);
}

bool QTdPollTypeRegular::allowMultipleAnswers() const {
    return m_allowMultipleAnswers;
}

void QTdPollTypeRegular::unmarshalJson(const QJsonObject &json)
{
    m_allowMultipleAnswers = json["allow_multiple_answers"].toBool();
}

QTdPollType *QTdPollTypeFactory::create(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();
    // TODO: create a map of QMap<@type, QTdObject::Type> so we can do fast lookups and
    // switch on the type. Otherwise this is/elseif is going to get huge supporting all content
    // types
    QTdPollType *result;

    if (type == "pollTypeQuiz") {
        result = new QTdPollTypeQuiz(parent);
    
    } else if (type == "pollTypeRegular") {
        result = new QTdPollTypeRegular(parent);
    } else {
        qWarning() << "Received unknown poll type" << type << json;
        return new QTdPollType(parent);
    }
    result->unmarshalJson(json);
    return result;
}