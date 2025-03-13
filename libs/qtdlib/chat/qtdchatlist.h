#ifndef QTDCHATLIST_H
#define QTDCHATLIST_H

#include <QObject>
#include "common/qabstracttdobject.h"

/**
 * @brief The QTdChatList class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_chat_list.html
 */
class QTdChatList : public QTdObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatList)
public:
    explicit QTdChatList(QObject *parent = nullptr);
};

/**
 * @brief The QTdChatListMain class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1chat_list_main.html
 */
class QTdChatListMain : public QTdChatList
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatListMain)
public:
    explicit QTdChatListMain(QObject *parent = Q_NULLPTR);
};

/**
 * @brief The QTdChatListArchive class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1chat_list_archive.html
 */
class QTdChatListArchive : public QTdChatList
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatListArchive)
public:
    explicit QTdChatListArchive(QObject *parent = Q_NULLPTR);
};

/**
 * @brief The QTdChatListFilter class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1chat_list_filter.html
 */
class QTdChatListFilter : public QTdChatList
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatListFilter)
public:
    explicit QTdChatListFilter(QObject *parent = Q_NULLPTR);
};
#endif // QTDCHATLIST_H
