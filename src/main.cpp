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

#include <QDebug>
#include <QFile>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>

#include <QQuickView>
#include <QScreen>

#include "journalmodel.h"

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    // TODO: register as singleton maybe
    qmlRegisterType<JournalModel>("JournalC", 1, 0, "JournalModel");

    JournalModel model;

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("journalModel", &model);
    engine.load(QUrl::fromLocalFile("qml/main.qml"));

    app.exec();
}
