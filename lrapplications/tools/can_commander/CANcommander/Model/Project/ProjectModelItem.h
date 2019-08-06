/*
 * ProjectModelItem.h
 *
 *  Created on: 09.07.2019
 *      Author: Andreas
 */
#ifndef _PROJECTMODELITEM_H_
#define _PROJECTMODELITEM_H_

// Qt includes
#include <QtCore/QVector>
#include <QtCore/QVariant>

// Project includes
#include "Model/AbstractUIModelItem.h"

/**
 * Enumeration of different project model item types
 */
enum ProjectModelItemType
{
    GROUP_ITEM              = 1,
    HW_INTERFACE_ITEM       = 2,
    TRACE_WINDOW_ITEM       = 3,
    DATA_DEF_FILE_ITEM      = 50
};

/**
 * Generic class for project model items in the project tree
 */
class ProjectModelItem : public AbstractUIModelItem
{
    public:
        ProjectModelItem(QString itemName, ProjectModelItemType type, AbstractUIModelItem* pParent = nullptr);
        virtual ~ProjectModelItem();

        ProjectModelItemType getType() const;
        QString getName() const;

    protected:
        QString m_Name;
        ProjectModelItemType m_ItemType;
};

#endif
