/*
 * ProjectExplorerWidget.cpp
 *
 *  Created on: 10.07.2019
 *      Author: Andreas
 */

// Qt includes
#include <QtCore/QVariant>
#include <QtWidgets/QWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>

// Project includes
#include "ProjectExplorerWidget.h"

/**
 *
 */
ProjectExplorerWidget::ProjectExplorerWidget(QWidget* pParent)
    : QWidget(pParent)
{
    createWidgetLayout();
}

/**
 *
 */
void ProjectExplorerWidget::createWidgetLayout()
{
    m_pTreeView = new QTreeView();
    m_pTreeView->header()->hide();

    QVBoxLayout* pLayout = new QVBoxLayout(this);
    pLayout->addWidget(m_pTreeView);
}

/**
 *
 */
void ProjectExplorerWidget::setProjectModel(ProjectModel* pModel)
{
   if (m_pTreeView != nullptr)
   {
       m_pTreeView->setModel(pModel);
   }
}
