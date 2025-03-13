#include "qtdchatlistsortfiltermodel.h"
#include <QDebug>
#include "client/qtdclient.h"
#include "models/QmlObjectListModel.h"
#include "qtdbasicgroupchat.h"
#include "qtdsupergroupchat.h"

QTdChatListSortFilterModel::QTdChatListSortFilterModel(QObject *parent)
    : QSortFilterProxyModel(parent)
    , m_chatList(0)
    , m_chatFilters(Everything)
{
}

QTdChatListModel *QTdChatListSortFilterModel::model() const
{
    return m_chatList;
}

void QTdChatListSortFilterModel::setModel(QTdChatListModel *model)
{
    m_chatList = model;
    setSourceModel(static_cast<QAbstractItemModel *>(m_chatList->model()));
    connect(model, &QTdChatListModel::chatStatusChanged, [=]() {
        invalidateFilter();
    });
    emit modelChanged();
    setSortRole(static_cast<QQmlObjectListModel<QTdChat> *>(m_chatList->model())->roleForName("lastMessage"));
    setFilterRole(static_cast<QQmlObjectListModel<QTdChat> *>(m_chatList->model())->roleForName("chatType"));
    setDynamicSortFilter(true);
    sort(0, Qt::DescendingOrder);
}

int QTdChatListSortFilterModel::chatFilters() const
{
    return m_chatFilters;
}

void QTdChatListSortFilterModel::setChatFilters(int chatFilters)
{
    if (m_chatFilters == chatFilters)
        return;

    m_chatFilters = chatFilters;
    emit chatFiltersChanged(m_chatFilters);
    invalidateFilter();
}

void QTdChatListSortFilterModel::setChatNameFilter(const QString &chatNameFilter)
{
    m_chatNameFilter = chatNameFilter;
    invalidateFilter();
}

bool QTdChatListSortFilterModel::filterBarVisible() const {
    return m_filterBarVisible;
}

void QTdChatListSortFilterModel::toggleFilterBar(const bool &value) {
    m_filterBarVisible = value;
    if (!m_filterBarVisible) {
        m_chatFilters |= ChatFilters::Everything;
    } else {
        m_chatFilters &= ~ChatFilters::Everything;
    }
    invalidateFilter();
}

void QTdChatListSortFilterModel::setChatListFilter(const int &value) {

    switch(value) {
        case 0:
            m_chatFilters = ChatFilters::Everything;
            break;
        case 1:
            m_chatFilters = ChatFilters::Personal;
            break;
        case 2:
            m_chatFilters = ChatFilters::Unread;
            break;
        case 3:
            m_chatFilters = ChatFilters::Archived;
            break;
    }
    invalidateFilter();
}

bool QTdChatListSortFilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QQmlObjectListModel<QTdChat> *model = static_cast<QQmlObjectListModel<QTdChat> *>(sourceModel());
    QTdChat *chat = model->at(source_row);

    if (!chat || chat->position()->order() == 0) {
        return false;
    }

    bool showRow = true;
    bool archived = chat->position()->list() && chat->position()->list()->typeString() == "chatListArchive";

    //Apply chat title filter, if set
    if (!chat->title().contains(m_chatNameFilter, Qt::CaseInsensitive)) {
        showRow = false;
    }

    if (m_chatFilters & ChatFilters::Everything) {
        return showRow & !archived;
    }

    if (m_chatFilters & ChatFilters::Unread && !(chat->hasUnreadMessages() || chat->hasUnreadMentions())) {
        showRow = false;
    }

    if (m_chatFilters & ChatFilters::Personal && !(chat->isPrivate() || chat->isSecret())) {
        showRow = false;
    }

    if (chat->position()->list()) {
        if (m_chatFilters & ChatFilters::Archived) {
            showRow = showRow & archived;
        } else {
            showRow = showRow & !archived;
        }
    }

    return showRow;
}

bool QTdChatListSortFilterModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    /**
     * TDlib suggests to use QTdChat::order() for ordering of the chat list
     *
     * Note this requires calling getBasicGroupData and getSuperGroupData to get the QTdChat::order
     * to even update so we have to wait longer for them to arrive compared to a basic chat or channel.
     */
    QQmlObjectListModel<QTdChat> *model = static_cast<QQmlObjectListModel<QTdChat> *>(sourceModel());
    QTdChat *left = model->at(source_left.row());
    QTdChat *right = model->at(source_right.row());

    /*
    This is how the sorting rule works:
        IF left and right sort orders are <>0 AND left order is smaller than right order, return true
        OR IF both sort orders are equal AND left id is smaller than right id, return true
        OR IF left OR right order is 0 AND left last message date is smaller then right last message date
            AND left is not pinned, return true
        ELSE return false

        The first part is the rule from tdlib, sort by order, but if equal order is given, sort by id
        The second part is a safeguard against sort order being 0, which happens with "Saved Messages" chat a lot
     */
    auto result = left->position()->order() < right->position()->order()
            || left->position()->order() == right->position()->order() && left->id() < right->id();
    return result;
}
