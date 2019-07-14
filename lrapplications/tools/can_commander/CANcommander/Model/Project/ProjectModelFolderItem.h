/*
 * ProjectModelFolderItem.h
 *
 *  Created on: 09.07.2019
 *      Author: Andreas
 */
#ifndef _PROJECTMODELFOLDERITEM_H_
#define _PROJECTMODELFOLDERITEM_H_

// Qt includes
#include <QtCore/QVector>
#include <QtCore/QVariant>

// Project includes
#include "ProjectModelItem.h"

/**
 * Generic class for project model items in the project tree
 */
class ProjectModelFolderItem : public ProjectModelItem
{
    public:
        ProjectModelFolderItem(QString itemName, ProjectModelItem* pParent = nullptr);
        virtual ~ProjectModelFolderItem();

        virtual QVariant getData(const QModelIndex& index);

    private:

};

#endif
