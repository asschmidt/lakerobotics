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

/**
 * Enumeration of different project model item types
 */
enum ProjectModelItemType
{
    GROUP_ITEM  = 1,
    HW_INTERFACE_ITEM = 2
};

/**
 * Generic class for project model items in the project tree
 */
class ProjectModelItem
{
    public:
        ProjectModelItem(QString itemName, ProjectModelItemType type, ProjectModelItem* pParent = nullptr);
        virtual ~ProjectModelItem();

        ProjectModelItem* getParent();
        ProjectModelItem* getChild(int row);
        int getChildCount() const;
        int getColumnCount() const;
        int getRow() const;
        ProjectModelItemType getType() const;
        QString getName() const;

        ProjectModelItem* appendChild(ProjectModelItem* pChild);

        virtual QVariant getData() = 0;

    protected:
        QString m_Name;
        ProjectModelItemType m_ItemType;

        ProjectModelItem* m_pParentItem;
        QVector<ProjectModelItem*> m_Childs;
};

#endif
