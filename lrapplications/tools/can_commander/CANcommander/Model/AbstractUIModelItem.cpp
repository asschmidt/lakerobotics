/*
 * AbstractUIModelItem.cpp
 *
 *  Created on: 13.07.2019
 *      Author: Andreas
 */

// Qt includes
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtCore/QVector>

// Project includes
#include "AbstractUIModelItem.h"


/**
 *
 */
AbstractUIModelItem::AbstractUIModelItem(AbstractUIModelItem* pParent)
{
   this->m_pParentItem = pParent;
}

/**
 * Destructor
 * Deletes all child objects of this project model item
 */
AbstractUIModelItem::~AbstractUIModelItem()
{
    qDeleteAll(m_Childs);
}

/**
 * Returns a pointer to the parent item
 */
AbstractUIModelItem* AbstractUIModelItem::getParent()
{
    return m_pParentItem;
}

/**
 * Returns the child item specified by the row index
 */
AbstractUIModelItem* AbstractUIModelItem::getChild(int row)
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
int AbstractUIModelItem::getChildCount() const
{
    return m_Childs.count();
}

/**
 * Returns the number of data columns of this item The project model item only
 * has one column
 */
int AbstractUIModelItem::getColumnCount() const
{
    return 1;
}

/**
 * Returns a the index of this item (based on the parent)
 */
int AbstractUIModelItem::getRow() const
{
    if (m_pParentItem != nullptr)
    {
        return m_pParentItem->m_Childs.indexOf(const_cast<AbstractUIModelItem*>(this));
    }
    else
    {
        return 0;
    }
}

/**
 *
 */
AbstractUIModelItem* AbstractUIModelItem::appendChild(AbstractUIModelItem* pChild)
{
   if (pChild != nullptr)
   {
       pChild->m_pParentItem = this;
       m_Childs.append(pChild);
   }

   return pChild;
}
