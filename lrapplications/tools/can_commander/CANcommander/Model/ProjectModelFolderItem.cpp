/*
 * ProjectModelFolderItem.cpp
 *
 *  Created on: 09.07.2019
 *      Author: Andreas
 */

// Project includes
#include "ProjectModelItem.h"
#include "ProjectModelFolderItem.h"

/**
 *
 */
ProjectModelFolderItem::ProjectModelFolderItem(QString itemName, ProjectModelItem* pParent)
    : ProjectModelItem(itemName, GROUP_ITEM, pParent)
{

}

/**
 * Destructor
 * Deletes all child objects of this project model item
 */
ProjectModelFolderItem::~ProjectModelFolderItem()
{

}

/**
 * Returns the item name as folder data
 * For a folder item the name (also used in UI) is the only data this item has
 */
QVariant ProjectModelFolderItem::getData()
{
    return QVariant(m_Name);
}
