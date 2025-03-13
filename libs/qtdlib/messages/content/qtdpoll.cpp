#include "qtdpoll.h"

QTdPoll::QTdPoll(QObject *parent)
    : QTdObject(parent)
    , m_id(0)
    , m_question("")
    , m_options(new QQmlObjectListModel<QTdPollOption>)
    , m_totalVoters(0)
    , m_isAnonymous(false)
    , m_pollType(Q_NULLPTR)
    , m_openPeriod(0)
    , m_closeDate(0)
    , m_isClosed(false)
{
    setType(POLL);
}

QString QTdPoll::question() const {
    return m_question;
}

QQmlObjectListModel<QTdPollOption> *QTdPoll::options() const {
    return m_options.data();
}

bool QTdPoll::userHasChosen() const {
    for( auto i = 0; i < m_options.data()->count(); i++ ) {
        auto option = static_cast<QTdPollOption *>(m_options.data()->get(i));
        if (option->isChosen())
            return true;
    }
    return false;
}

qint32 QTdPoll::totalVoters() const {
    return m_totalVoters;
}

qint32 QTdPoll::openPeriod() const {
    return m_openPeriod;
}

bool QTdPoll::isAnonymous() const {
    return m_isAnonymous;
}

bool QTdPoll::isClosed() const {
    return m_isClosed;
}

bool QTdPoll::isQuiz() const {
    return m_pollType.data() != Q_NULLPTR && m_pollType.data()->correctOption() != -1;
}

qint32 QTdPoll::quizCorrectChoice() const {
    if (m_pollType.data() == Q_NULLPTR) {
        return -1;
    }
    return m_pollType.data()->correctOption();
}

QTdFormattedText *QTdPoll::quizExplanation() const {
    return m_pollType.data()->explanation();
}

bool QTdPoll::isMultiChoice() const {
    return m_pollType.data() != Q_NULLPTR && m_pollType.data()->allowMultipleAnswers();
}

void QTdPoll::unmarshalJson(const QJsonObject &json)
{
    m_id = json["id"].toInt();
    m_question = json["question"].toString();
    const QJsonArray options = json["options"].toArray();
    int i = 0;
    m_options->clear();
    for (const QJsonValue &option : options) {
        auto *s = new QTdPollOption();
        s->unmarshalJson(option.toObject());
        s->setOptionIndex(i++);
        m_options->append(s);
    }
    m_totalVoters = json["total_voter_count"].toInt();
    m_isAnonymous = json["is_anonymous"].toBool();
    m_pollType.reset(QTdPollTypeFactory::create(json["type"].toObject(), this));
    m_openPeriod = json["open_period"].toInt();
    m_closeDate = json["close_date"].toInt();
    m_isClosed = json["is_closed"].toBool();

    emit dataChanged();
}