/* This file is part of the transform app
 * Copyright (c) 2016 Carlos E. Torchia
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

#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QVariant>
#include <QStandardItemModel>

/**
 * I got the idea of using QStandardItemModel from here:
 * @see https://github.com/bvanderlaan/ImaginativeThinking_tutorials/blob/master/Qt/QtQuick_TreeView/MyTreeModel.hpp
 */
class TreeModel : public QStandardItemModel
{
    Q_OBJECT
    Q_PROPERTY(QVariantMap currentItemData READ currentItemData NOTIFY currentItemDataChanged)
    Q_PROPERTY(QVariantList currentList READ currentList NOTIFY currentListChanged)
public:
    explicit TreeModel(QObject *parent = 0);
    virtual ~TreeModel();

    QVariantMap currentItemData();
    QVariantList currentList();

    Q_INVOKABLE void go(int childRow);
    Q_INVOKABLE void goParent();
signals:
    void currentItemDataChanged();
    void currentListChanged();
public slots:
protected:
    QStandardItem *createRootItem();
private:
    QStandardItem *m_currentItem;
};

#endif // TREEMODEL_H
