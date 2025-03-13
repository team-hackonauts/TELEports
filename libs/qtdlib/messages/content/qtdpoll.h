#ifndef QTDPOLL_H
#define QTDPOLL_H

#include <QObject>
#include <QPointer>
#include <QJsonArray>
#include "common/qabstracttdobject.h"
#include "common/qabstractint64id.h"
#include "qtdpolloption.h"
#include "qtdpolltype.h"
#include "models/QmlObjectListModel.h"

class QTdPoll : public QTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString question READ question NOTIFY dataChanged)
    Q_PROPERTY(QObject *options READ options NOTIFY dataChanged)
    Q_PROPERTY(bool userHasChosen READ userHasChosen NOTIFY dataChanged)
    Q_PROPERTY(qint32 totalVoters READ totalVoters NOTIFY dataChanged)
    Q_PROPERTY(qint32 openPeriod READ openPeriod NOTIFY dataChanged)     
    Q_PROPERTY(bool isAnonymous READ isAnonymous NOTIFY dataChanged)
    Q_PROPERTY(bool isClosed READ isClosed NOTIFY dataChanged)
    Q_PROPERTY(bool isQuiz READ isQuiz NOTIFY dataChanged)
    Q_PROPERTY(qint32 quizCorrectChoice READ quizCorrectChoice NOTIFY dataChanged)    
    Q_PROPERTY(QTdFormattedText *quizExplanation READ quizExplanation NOTIFY dataChanged)
    Q_PROPERTY(bool isMultiChoice READ isMultiChoice NOTIFY dataChanged)

public:
    explicit QTdPoll(QObject *parent = nullptr);

    QString question() const;
    QQmlObjectListModel<QTdPollOption> *options() const;
    qint32 totalVoters() const;
    bool userHasChosen() const;
    qint32 openPeriod() const;
    bool isAnonymous() const;
    bool isClosed() const;
    bool isQuiz() const;
    qint32 quizCorrectChoice() const;
    QTdFormattedText *quizExplanation() const;
    bool isMultiChoice() const;

    void unmarshalJson(const QJsonObject &json);

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QTdPoll)
    QTdInt64 m_id;
    QString m_question;
    QScopedPointer<QQmlObjectListModel<QTdPollOption>> m_options;
    qint32 m_totalVoters;
    //List recent voter Ids
    bool m_isAnonymous;
    QScopedPointer<QTdPollType> m_pollType;
    qint32 m_openPeriod;
    qint32 m_closeDate;
    bool m_isClosed;
};

#endif // QTDPOLL_H