/*
 * ProjectExplorerWidget.h
 *
 *  Created on: 10.07.2019
 *      Author: Andreas
 */

#ifndef _CANCOMMANDER_PROJECT_EXPLORER_H_
#define _CANCOMMANDER_PROJECT_EXPLORER_H_

// Qt includes
#include <QtCore/QVariant>
#include <QtWidgets/QWidget>
#include <QtWidgets/QTreeView>

// Project Includes
#include "Model/ProjectModel.h"

class ProjectExplorerWidget : public QWidget
{
    Q_OBJECT

    public:
        ProjectExplorerWidget(QWidget* pParent = nullptr);

        void setProjectModel(ProjectModel* pModel);

    private:
        void createWidgetLayout();

        QTreeView* m_pTreeView;
};


#endif /* _CANCOMMANDER_PROJECT_EXPLORER_H_ */
