/*
 * ProjectModelItem.cpp
 *
 *  Created on: 09.07.2019
 *      Author: Andreas
 */

// Project includes
#include "Model/AbstractUIModelItem.h"
#include "ProjectModelItem.h"

/**
 *
 */
ProjectModelItem::ProjectModelItem(QString itemName, ProjectModelItemType type, AbstractUIModelItem* pParent)
    : AbstractUIModelItem(pParent)
{
   this->m_Name = itemName;
   this->m_ItemType = type;
}

/**
 * Destructor
 * Deletes all child objects of this project model item
 */
ProjectModelItem::~ProjectModelItem()
{

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
