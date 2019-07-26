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
#include <QtWidgets/QMenu>
#include <QtWidgets/QAction>

// Project includes
#include "Model/Project/ProjectModelItem.h"
#include "Model/Project/ProjectModelHWInterface.h"

#include "ProjectExplorerWidget.h"
#include "Ui/Dialogs/canhwinterfaceoptiondlg.h"

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
    m_pTreeView->setContextMenuPolicy(Qt::CustomContextMenu);

    // Connect the doubleclick signal to the method
    connect(m_pTreeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(itemDoubleClicked(QModelIndex)));
    connect(m_pTreeView, SIGNAL(customContextMenuRequested(QPoint)), SLOT(customMenuRequested(QPoint)));

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
void ProjectExplorerWidget::customMenuRequested(QPoint pos)
{
    QModelIndex index = m_pTreeView->indexAt(pos);

    QMenu *menu=new QMenu(this);
    menu->addAction(new QAction("Action 1", this));
    menu->addAction(new QAction("Action 2", this));
    menu->addAction(new QAction("Action 3", this));

    ProjectModelItem* pSelectedItem = static_cast<ProjectModelItem*>(index.internalPointer());
    if (pSelectedItem != nullptr)
    {
        pSelectedItem->createItemContextMenu(menu);
    }

    menu->popup(m_pTreeView->viewport()->mapToGlobal(pos));
}

/**
 *
 */
void ProjectExplorerWidget::customHeaderMenuRequested(QPoint pos)
{
    int column = m_pTreeView->header()->logicalIndexAt(pos);

    QMenu *menu=new QMenu(this);
    menu->addAction(new QAction("Header Action 1", this));
    menu->addAction(new QAction("Header Action 2", this));
    menu->addAction(new QAction("Header Action 3", this));
    menu->popup(m_pTreeView->header()->viewport()->mapToGlobal(pos));
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
        m_pTreeView->expandAll();
    }
}
