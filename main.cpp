/* This file is part of the transform app
 * Copyright (c) 2015 Carlos E. Torchia
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtGlobal>
#include <QtQml/qqml.h>
#include <QApplication>
#include <QQmlApplicationEngine>

#include "feedstore.h"
#include "datatransformer.h"
#include "csvexporter.h"
#include "treemodel.h"

int main(int argc, char *argv[])
{
    qputenv("QT_QUICK_CONTROLS_STYLE", "Flat");

    QApplication app(argc, argv);

    qmlRegisterType<FeedStore>("Feeds", 1, 0, "FeedStore");
    qmlRegisterType<DataTransformer>("Transformation", 1, 0, "DataTransformer");
    qmlRegisterType<CsvExporter>("Export", 1, 0, "CsvExporter");
    qmlRegisterType<TreeModel>("Trees", 1, 0, "TreeModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

