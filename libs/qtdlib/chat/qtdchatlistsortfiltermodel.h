#ifndef QTDCHATLISTSORTFILTERMODEL_H
#define QTDCHATLISTSORTFILTERMODEL_H

#include <QObject>
#include <QPointer>
#include <QFlags>
#include <QString>
#include <QSortFilterProxyModel>
#include "qtdchatlistmodel.h"

/**
 * @brief The QTdChatListSortFilterModel class
 *
 * Sorts chat list in descending order based on QTdChat::order()
 *
 * Filters can be applied to show certain QTdChatType's
 */
class QTdChatListSortFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QTdChatListModel *model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(int chatFilters READ chatFilters WRITE setChatFilters NOTIFY chatFiltersChanged)
    Q_PROPERTY(bool filterBarVisible READ filterBarVisible NOTIFY filterBarVisibleChanged)

public:
    explicit QTdChatListSortFilterModel(QObject *parent = nullptr);

    enum ChatFilters {
        Everything = 1, // this includes banned or left chats
        Personal =2,
        Unread = 4,
        Archived = 8
    };
    Q_ENUM(ChatFilters)

    QTdChatListModel *model() const;
    void setModel(QTdChatListModel *model);
    int chatFilters() const;
    bool filterBarVisible() const;

public slots:
    void setChatFilters(int chatFilters);
    void setChatNameFilter(const QString &nameFilter);
    void toggleFilterBar(const bool &value);
    void setChatListFilter(const int &value);

signals:
    void modelChanged();
    void countChanged();
    void chatFiltersChanged(int chatFilters);
    void filterBarVisibleChanged();

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const;

private:
    Q_DISABLE_COPY(QTdChatListSortFilterModel)
    QPointer<QTdChatListModel> m_chatList;
    int m_chatFilters;
    bool m_filterBarVisible;
    QString m_chatNameFilter;
};

#endif // QTDCHATLISTSORTFILTERMODEL_H
