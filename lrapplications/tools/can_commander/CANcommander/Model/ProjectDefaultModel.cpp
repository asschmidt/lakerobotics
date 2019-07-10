/*
 * ProjectDefaultModel.cpp
 *
 *  Created on: 10.07.2019
 *      Author: Andreas
 */

// Qt includes
#include <QtCore/QString>

// Project includes
#include "ProjectModelItem.h"
#include "ProjectModelFolderItem.h"
#include "ProjectModel.h"
#include "ProjectDefaultModel.h"

/**
 *
 */
ProjectDefaultModel::ProjectDefaultModel(QString rootName)
    : ProjectModel(rootName)
{
    m_pProjectNode = new ProjectModelFolderItem("Project", m_pRootNode);
    m_pRootNode->appendChild(m_pProjectNode);

    m_pHWInterfaces = new ProjectModelFolderItem("HW Interfaces", m_pProjectNode);
    m_pProjectNode->appendChild(m_pHWInterfaces);

    m_pDataFiles = new ProjectModelFolderItem("Data Files", m_pProjectNode);
    m_pProjectNode->appendChild(m_pDataFiles);

    m_pMainCAN = new ProjectModelHWInterface("Main CAN", m_pHWInterfaces);
    m_pMainCAN->getHWInterfaceData()->setInterfaceName("CAN1");

    m_pHWInterfaces->appendChild(m_pMainCAN);
}

/**
 *
 */
ProjectDefaultModel::~ProjectDefaultModel()
{
    if (m_pHWInterfaces != nullptr)
    {
        delete m_pHWInterfaces;
    }

    if (m_pDataFiles != nullptr)
    {
        delete m_pDataFiles;
    }

    if (m_pProjectNode != nullptr)
    {
        delete m_pProjectNode;
    }
}
