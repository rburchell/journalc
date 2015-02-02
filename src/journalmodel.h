/*
 * Copyright (C) 2014 Robin Burchell <robin.burchell@viroteck.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef JOURNALMODEL_H
#define JOURNALMODEL_H

#include <QAbstractListModel>
#include <QDebug>

class JournalModelRow;

class JournalModel : public QAbstractListModel
{
    Q_OBJECT
public:
    JournalModel(QObject *parent = 0);

    enum Priority : char {
        EmergencyPriority,
        AlertPriority,
        CriticalPriority,
        ErrorPriority,
        WarningPriority,
        NoticePriority,
        InfoPriority,
        DebugPriority
    };
    Q_ENUMS(Priority)

    enum Roles {
        MessageRole = Qt::UserRole,
        MessageIdRole,
        PriorityRole,
        CodeFileRole,
        CodeLineRole,
        CodeFuncRole,
        PidRole,
        UidRole,
        GidRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QVector<JournalModelRow *> m_rows;
};

#endif // JOURNALMODEL_H
