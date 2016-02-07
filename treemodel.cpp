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

#include "treemodel.h"

TreeModel::TreeModel(QObject *parent) : QStandardItemModel(parent)
{
    QStandardItem *rootItem = createRootItem();
    appendRow(rootItem);
    m_currentItem = invisibleRootItem();
}

TreeModel::~TreeModel()
{
}

QStandardItem *TreeModel::createRootItem()
{
    QStandardItem *rootItem = new QStandardItem();
    QVariantMap rootData
    {
        {"name", "Document"},
        {"pathex", "/"}
    };
    rootItem->setData(rootData);
    return rootItem;
}

QVariantMap TreeModel::currentItemData()
{
    QStandardItem *currentItem = m_currentItem;
    QVariantMap currentItemData = currentItem->data().toMap();
    currentItemData["hasChildren"] = currentItem->hasChildren();
    return currentItemData;
}

QVariantList TreeModel::currentList()
{
    QStandardItem *currentItem = m_currentItem;
    QStandardItem *parentItem = currentItem->parent();
    QVariantList list;
    if (parentItem) {
        QVariantMap parentItemData
        {
            {"name", ".."},
            {"isParent", true}
        };
        list << parentItemData;
    }
    for (int row = 0; row < currentItem->rowCount(); row++) {
        QStandardItem *childItem = currentItem->child(row);
        QVariantMap childItemData = childItem->data().toMap();
        childItemData["row"] = childItem->row();
        childItemData["hasChildren"] = childItem->hasChildren();
        list << childItemData;
    }
    return list;
}

void TreeModel::go(int childRow)
{
    QStandardItem *currentItem = m_currentItem;
    QStandardItem *childItem = currentItem->child(childRow);
    m_currentItem = childItem;
    emit currentItemDataChanged();
    emit currentListChanged();
}

void TreeModel::goParent()
{
    QStandardItem *currentItem = m_currentItem;
    QStandardItem *parentItem = currentItem->parent();
    if (parentItem) {
        m_currentItem = parentItem;
    } else {
        m_currentItem = invisibleRootItem();
    }
    emit currentItemDataChanged();
    emit currentListChanged();
}

void TreeModel::load(const QVariant& tree)
{
    clear();
    QStandardItem *rootItem = createRootItem();
    appendRow(rootItem);
    load(tree, "/", rootItem);
    if (tree.toList().isEmpty() && tree.toMap().isEmpty()) {
        m_currentItem = invisibleRootItem();
    } else {
        m_currentItem = rootItem;
    }
    emit currentItemDataChanged();
    emit currentListChanged();
}

void TreeModel::load(const QVariant& tree, const QString& pathex, QStandardItem *item)
{
    if (!tree.toList().isEmpty()) {
        QVariantList list = tree.toList();
        QString childPathex = pathex + "*/";
        for (int i = 0; i < list.size(); i++) {
            QStandardItem *childItem = new QStandardItem();
            QVariantMap data
            {
                {"name", QString::number(i)},
                {"pathex", childPathex}
            };
            childItem->setData(data);
            item->appendRow(childItem);
            load(list[i], childPathex, childItem);
        }
    } else if (!tree.toMap().isEmpty()) {
        QVariantMap map = tree.toMap();
        for (QString key: map.keys()) {
            QStandardItem *childItem = new QStandardItem();
            QString childPathex = pathex + key + "/";
            QVariantMap data
            {
                {"name", key},
                {"pathex", childPathex}
            };
            childItem->setData(data);
            item->appendRow(childItem);
            load(map[key], childPathex, childItem);
        }
    }
}
