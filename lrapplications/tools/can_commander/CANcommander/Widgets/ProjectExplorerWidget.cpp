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
#include "Model/Project/ProjectModelItem.h"
#include "Model/Project/ProjectModelHWInterface.h"

#include "ProjectExplorerWidget.h"
#include "Ui/canhwinterfaceoptiondlg.h"

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

    // Connect the doubleclick signal to the method
    connect(m_pTreeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(itemDoubleClicked(QModelIndex)));

    QVBoxLayout* pLayout = new QVBoxLayout(this);
    pLayout->addWidget(m_pTreeView);
}

/**
 *
 */
void ProjectExplorerWidget::itemDoubleClicked(const QModelIndex& index)
{
    ProjectModelItem* pSelectedItem = static_cast<ProjectModelItem*>(index.internalPointer());

    if (pSelectedItem != nullptr)
    {
        switch(pSelectedItem->getType())
        {
            case GROUP_ITEM:
                break;

            case HW_INTERFACE_ITEM:
            {
                ProjectModelHWInterface* pInterfaceItem = static_cast<ProjectModelHWInterface*>(index.internalPointer());

                CANHwInterfaceOptionDlg* pDlg = new CANHwInterfaceOptionDlg(this);
                pDlg->setInterfaceItem(pInterfaceItem);
                pDlg->exec();
                delete pDlg;
            }
        }
    }
}

/**
 *
 */
void ProjectExplorerWidget::setProjectModel(ProjectModel* pModel)
{
    m_pModel = pModel;

    if (m_pTreeView != nullptr)
    {
        m_pTreeView->setModel(pModel);
    }
}
