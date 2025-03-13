#ifndef QTDMESSAGECONTENT_H
#define QTDMESSAGECONTENT_H

#include <QObject>
#include <QDateTime>
#include <QUrl>
#include "common/qabstracttdobject.h"
#include "files/qtdaudio.h"
#include "files/qtddocument.h"
#include "files/qtdphoto.h"
#include "files/qtdsticker.h"
#include "files/qtdvideo.h"

class QTdMessageContent : public QTdObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdMessageContent)
    Q_PROPERTY(QString infoText READ infoText NOTIFY dataChanged)
    Q_PROPERTY(QString typeText READ typeText NOTIFY dataChanged)
    Q_PROPERTY(bool isSecret READ isSecret NOTIFY dataChanged)
    Q_PROPERTY(QUrl infoImageUrl READ infoImageUrl NOTIFY dataChanged)
public:
    explicit QTdMessageContent(QObject *parent = nullptr);
    // infoText and infoImageUrl are helper methods and not part of of TDLib::message_content
    // They are used for displaying limited information about a message when editing or replying.
    QString infoText() const;
    QString typeText() const;
    QUrl infoImageUrl() const;
    bool isSecret() const;
    void setInfoText(const QString &infoText);
    void setTypeText(const QString &typeText);
signals:
    void dataChanged();

protected:
    QString m_infoText;
    QString m_typeText;
    QUrl m_infoImageUrl;
    bool m_isSecret;

};

class QTdMessageAction : public QTdMessageContent
{
    Q_OBJECT
public:
    explicit QTdMessageAction(QObject *parent = nullptr);

private:
    Q_DISABLE_COPY(QTdMessageAction)
};

class QTdMessageHidden : public QTdMessageContent
{
    Q_OBJECT
public:
    explicit QTdMessageHidden(QObject *parent = nullptr);

private:
    Q_DISABLE_COPY(QTdMessageHidden)
};
#endif // QTDMESSAGECONTENT_H
