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

#include <stdio.h>
#include <systemd/sd-journal.h>

#include "journalmodel.h"

struct JournalModelRow
{
    static JournalModelRow *fromJournal(sd_journal *j);

    enum Priority : char {
        // TODO: syslog fields
    };

    QString message() const { return m_message; }
    QByteArray messageId() const { return m_messageId; }
    Priority priority() const { return m_priority; }
    QByteArray codeFile() const { return m_codeFile; }
    quint32 codeLine() const { return m_codeLine; }
    QByteArray codeFunc() const { return m_codeFunc; }
    quint32 pid() const { return m_pid; }
    quint32 uid() const { return m_uid; }
    quint32 gid() const { return m_gid; }

private:
    QString m_message;
    QByteArray m_messageId;
    Priority m_priority;
    QByteArray m_codeFile;
    quint32 m_codeLine;
    QByteArray m_codeFunc;
    quint32 m_pid;
    quint32 m_uid;
    quint32 m_gid;
};

static QString fetchDataFor(sd_journal *j, const char *fieldName)
{
    const char *d;
    size_t l;
    int r = sd_journal_get_data(j, fieldName, (const void **)&d, &l);
    if (r < 0) {
        // silently ignore; this happens a lot.
        return QString();
    }

    /* +1 fiddliness is due to the = */
    return QString::fromLocal8Bit(d + strlen(fieldName) + 1, l - (strlen(fieldName) + 1));
}

JournalModelRow *JournalModelRow::fromJournal(sd_journal *j)
{
    // TODO: sd_journal_get_cursor so we can seek back if we need to
    JournalModelRow *jm = new JournalModelRow();

    jm->m_message = fetchDataFor(j, "MESSAGE");
    jm->m_messageId = fetchDataFor(j, "MESSAGE_ID").toLatin1();
    jm->m_priority << fetchDataFor(j, "PRIORITY").toInt();
    jm->m_codeFile = fetchDataFor(j, "CODE_FILE").toUtf8();
    jm->m_codeLine = fetchDataFor(j, "CODE_LINE").toInt();
    jm->m_codeFunc = fetchDataFor(j, "CODE_FUNC").toUtf8();
    jm->m_pid = fetchDataFor(j, "_PID").toInt();
    jm->m_uid = fetchDataFor(j, "_UID").toInt();
    jm->m_gid = fetchDataFor(j, "_GID").toInt();

    return jm;
}

JournalModel::JournalModel(QObject *parent)
    : QAbstractListModel(parent)
{
    int r;
    sd_journal *j;
    r = sd_journal_open(&j, SD_JOURNAL_LOCAL_ONLY);
    if (r < 0) {
        fprintf(stderr, "Failed to open journal: %s\n", strerror(-r));
        return;
//            return 1;
    }
    SD_JOURNAL_FOREACH(j) {
        JournalModelRow *row = JournalModelRow::fromJournal(j);
        m_rows.append(row);
    }
    sd_journal_close(j);
}

int JournalModel::rowCount(const QModelIndex &parent) const
{
    return m_rows.count();
}

QVariant JournalModel::data(const QModelIndex &index, int role) const
{
    if (role == MessageRole)
        return m_rows.at(index.row())->message();
    return QVariant();
}

QHash<int, QByteArray> JournalModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[MessageRole] = "message";
    return roles;
}

