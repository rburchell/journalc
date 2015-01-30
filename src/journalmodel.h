#ifndef JOURNALMODEL_H
#define JOURNALMODEL_H

#include <QAbstractListModel>

class JournalModel : public QAbstractListModel
{
    Q_OBJECT
public:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const
    {
        return 0;
    }
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const
    {
        return QVariant();
    }
};

#endif // JOURNALMODEL_H
