/*
 * QuickTraceAction.cpp
 *
 *  Created on: 14.07.2019
 *      Author: Andreas
 */

// Qt includes
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtCore/QDebug>
#include <QtWidgets/QAction>

// Project Includes
#include "Model/Project/ProjectModelItem.h"
#include "Model/Project/ProjectModelHWInterface.h"
#include "QuickTraceAction.h"

/**
 *
 */
QuickTraceAction::QuickTraceAction(ProjectModelHWInterface* pHWInterface, QObject* pParent)
    : QObject(pParent)
{
    m_pHWInterface = pHWInterface;
}

/**
 *
 */
void QuickTraceAction::execute()
{
    qDebug() << "Triggered QuickTraceAction for " << m_pHWInterface->getHWInterfaceData()->getInterfaceName();
}
