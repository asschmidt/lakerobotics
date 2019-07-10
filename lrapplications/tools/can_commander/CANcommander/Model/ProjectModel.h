/*
 * ProjectModel.h
 *
 *  Created on: 09.07.2019
 *      Author: Andreas
 */
#ifndef _PROJECTMODEL_H_
#define _PROJECTMODEL_H_

// Qt includes
#include <QtCore/QAbstractItemModel>
#include <QtCore/QModelIndex>
#include <QtCore/QVariant>

// Project includes
#include "ProjectModelItem.h"

class ProjectModel : public QAbstractItemModel
{
        Q_OBJECT

    public:
        ProjectModel(QString rootName);
        virtual ~ProjectModel();

        QVariant data(const QModelIndex &index, int role) const override;

        Qt::ItemFlags flags(const QModelIndex &index) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

        QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
        QModelIndex parent(const QModelIndex &index) const override;

        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    protected:
        ProjectModelItem* m_pRootNode;
};

#endif
