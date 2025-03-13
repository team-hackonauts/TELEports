#include "chat/qtdchatlist.h"

QTdChatList::QTdChatList(QObject *parent)
    : QTdObject(parent)
{
}

QTdChatListMain::QTdChatListMain(QObject *parent)
    : QTdChatList(parent)
{
    setType(CHAT_LIST_MAIN);
}

QTdChatListArchive::QTdChatListArchive(QObject *parent)
    : QTdChatList(parent)
{
    setType(CHAT_LIST_ARCHIVE);
}

QTdChatListFilter::QTdChatListFilter(QObject *parent)
    : QTdChatList(parent)
{
    setType(CHAT_LIST_FILTER);
}

