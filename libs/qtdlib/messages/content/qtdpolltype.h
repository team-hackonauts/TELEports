#ifndef QTDPOLLTYPE_H
#define QTDPOLLTYPE_H

#include <QObject>
#include <QPointer>
#include "common/qabstracttdobject.h"
#include "qtdformattedtext.h"

class QTdPollType : public QTdObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 correctOption READ correctOption NOTIFY dataChanged)
    Q_PROPERTY(QTdFormattedText *explanation READ explanation NOTIFY dataChanged)
    Q_PROPERTY(bool allowMultipleAnswers READ allowMultipleAnswers NOTIFY dataChanged)

public:
    explicit QTdPollType(QObject *parent = nullptr);

    virtual qint32 correctOption() const;
    virtual QTdFormattedText *explanation() const;
    virtual bool allowMultipleAnswers() const;

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QTdPollType)
};

class QTdPollTypeQuiz : public QTdPollType
{
    Q_OBJECT

public:
    explicit QTdPollTypeQuiz(QObject *parent = nullptr);

    qint32 correctOption() const;
    QTdFormattedText *explanation() const;

    void unmarshalJson(const QJsonObject &json);

private:
    Q_DISABLE_COPY(QTdPollTypeQuiz)

    qint32 m_correctOption;
    QScopedPointer<QTdFormattedText> m_explanation;
};

class QTdPollTypeRegular : public QTdPollType
{
    Q_OBJECT

public:
    explicit QTdPollTypeRegular(QObject *parent = nullptr);

    bool allowMultipleAnswers() const;

    void unmarshalJson(const QJsonObject &json);

private:
    Q_DISABLE_COPY(QTdPollTypeRegular)

    bool m_allowMultipleAnswers;
};

struct QTdPollTypeFactory
{
    static QTdPollType *create(const QJsonObject &json, QObject *parent = Q_NULLPTR);
};

#endif // QTDPOLLTYPE_H