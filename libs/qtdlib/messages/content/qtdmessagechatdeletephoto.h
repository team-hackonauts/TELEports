#ifndef QTDMESSAGECHATDELETEPHOTO_H
#define QTDMESSAGECHATDELETEPHOTO_H

#include <QObject>
#include "messages/qtdmessagecontent.h"

class QTdMessageChatDeletePhoto : public QTdMessageContent
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdMessageChatDeletePhoto)
public:
    explicit QTdMessageChatDeletePhoto(QObject *parent = nullptr);
};

#endif // QTDMESSAGECHATDELETEPHOTO_H
