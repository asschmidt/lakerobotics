/*
 * ProjectModelFolderItem.cpp
 *
 *  Created on: 09.07.2019
 *      Author: Andreas
 */

// Qt includes
#include <QtCore/QStack>

// Project includes
#include "ProjectModel.h"
#include "ProjectModelFolderItem.h"

/**
 *
 */
ProjectModel::ProjectModel(QString rootName)
    : QAbstractItemModel(nullptr)
{
    // Create the root node
    m_pRootNode = new ProjectModelFolderItem(rootName, nullptr);
}

/**
 *
 */
ProjectModel::~ProjectModel()
{
    if (m_pRootNode != nullptr)
    {
        delete m_pRootNode;
    }
}

/**
 *
 */
int ProjectModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return static_cast<ProjectModelItem*>(parent.internalPointer())->getColumnCount();
    }
    else
    {
        return m_pRootNode->getColumnCount();
    }
}

/**
 *
 */
QVariant ProjectModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    ProjectModelItem *item = static_cast<ProjectModelItem*>(index.internalPointer());

    return item->getData(index);
}

/**
 *
 */
Qt::ItemFlags ProjectModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return Qt::NoItemFlags;
    }

    return QAbstractItemModel::flags(index);
}

/**
 *
 */
QVariant ProjectModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        QModelIndex invalidIndex;
        return m_pRootNode->getData(invalidIndex);
    }

    return QVariant();
}

/**
 *
 */
QModelIndex ProjectModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    AbstractUIModelItem* parentItem;

    if (!parent.isValid())
    {
        parentItem = m_pRootNode;
    }
    else
    {
        parentItem = static_cast<AbstractUIModelItem*>(parent.internalPointer());
    }

    AbstractUIModelItem* childItem = parentItem->getChild(row);
    if (childItem)
    {
        return createIndex(row, column, childItem);
    }

    return QModelIndex();
}

/**
 *
 */
QModelIndex ProjectModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return QModelIndex();
    }

    AbstractUIModelItem* childItem = static_cast<AbstractUIModelItem*>(index.internalPointer());
    AbstractUIModelItem* parentItem = childItem->getParent();

    if (parentItem == m_pRootNode || parentItem == nullptr)
    {
        return QModelIndex();
    }

    return createIndex(parentItem->getRow(), 0, parentItem);
}

/**
 *
 */
int ProjectModel::rowCount(const QModelIndex &parent) const
{
    ProjectModelItem* parentItem;

    if (parent.column() > 0)
    {
        return 0;
    }

    if (!parent.isValid())
    {
        parentItem = m_pRootNode;
    }
    else
    {
        parentItem = static_cast<ProjectModelItem*>(parent.internalPointer());
    }

    return parentItem->getChildCount();
}

/**
 *
 */
QVector<ProjectModelItem*>* ProjectModel::getAllItemsOfType(ProjectModelItemType itemType) const
{
    QVector<ProjectModelItem*>* pItemList = new QVector<ProjectModelItem*>();

    QStack<ProjectModelItem*> itemStack;
    itemStack.push(m_pRootNode);

    while (itemStack.count() > 0)
    {
        ProjectModelItem* pCurrentItem = itemStack.pop();

        for( int i=0; i<pCurrentItem->getChildCount(); i++)
        {
            ProjectModelItem* pItem = static_cast<ProjectModelItem*>(pCurrentItem->getChild(i));
            if (pItem != nullptr)
            {
                if (pItem->getType() == itemType)
                {
                    pItemList->append(pItem);
                }

                if (pItem->getType() == GROUP_ITEM)
                {
                    itemStack.push(pItem);
                }
            }
        }
    }

    return pItemList;
}
