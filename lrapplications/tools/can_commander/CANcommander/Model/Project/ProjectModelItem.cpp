/*
 * ProjectModelItem.cpp
 *
 *  Created on: 09.07.2019
 *      Author: Andreas
 */

// Project includes
#include "ProjectModelItem.h"

/**
 *
 */
ProjectModelItem::ProjectModelItem(QString itemName, ProjectModelItemType type, ProjectModelItem* pParent)
{
   this->m_Name = itemName;
   this->m_pParentItem = pParent;
   this->m_ItemType = type;
}

/**
 * Destructor
 * Deletes all child objects of this project model item
 */
ProjectModelItem::~ProjectModelItem()
{
    qDeleteAll(m_Childs);
}

/**
 * Returns a pointer to the parent item
 */
ProjectModelItem* ProjectModelItem::getParent()
{
    return m_pParentItem;
}

/**
 * Returns the child item specified by the row index
 */
ProjectModelItem* ProjectModelItem::getChild(int row)
{
    if (row >= 0 && row < m_Childs.size())
    {
        return m_Childs.at(row);
    }
    else
    {
        return nullptr;
    }
}

/**
 * Returns the number of child items
 */
int ProjectModelItem::getChildCount() const
{
    return m_Childs.count();
}

/**
 * Returns the number of data columns of this item The project model item only
 * has one column
 */
int ProjectModelItem::getColumnCount() const
{
    return 1;
}

/**
 * Returns a the index of this item (based on the parent)
 */
int ProjectModelItem::getRow() const
{
    if (m_pParentItem != nullptr)
    {
        return m_pParentItem->m_Childs.indexOf(const_cast<ProjectModelItem*>(this));
    }
    else
    {
        return 0;
    }
}

/**
 * Returns the item type
 */
ProjectModelItemType ProjectModelItem::getType() const
{
    return this->m_ItemType;
}

/**
 * Returns the name of the item
 * Can be used for representation in the UI
 */
QString ProjectModelItem::getName() const
{
    return this->m_Name;
}

/**
 *
 */
ProjectModelItem* ProjectModelItem::appendChild(ProjectModelItem* pChild)
{
   if (pChild != nullptr)
   {
       pChild->m_pParentItem = this;
       m_Childs.append(pChild);
   }

   return pChild;
}
