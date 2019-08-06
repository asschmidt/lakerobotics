/*
 * ProjectModelTraceWindow.cpp
 *
 *  Created on: 30.07.2019
 *      Author: Andreas
 */

// Qt includes
#include <QtCore/QObject>
#include <QtCore/QVector>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenu>

// Project includes
#include "ProjectModelItem.h"
#include "ProjectModelHWInterface.h"
#include "ProjectModelTraceWindow.h"


/**
 *
 */
ProjectModelTraceWindowData::ProjectModelTraceWindowData()
{
    // TODO Auto-generated constructor stub

}

/**
 *
 */
ProjectModelTraceWindowData::~ProjectModelTraceWindowData()
{
    // TODO Auto-generated destructor stub
}

/**
 *
 */
ProjectModelTraceWindow::ProjectModelTraceWindow(QString itemName, ProjectModelItem* pParent)
    : ProjectModelItem(itemName, TRACE_WINDOW_ITEM, pParent)
{
    // TODO Auto-generated constructor stub

}

/**
 *
 */
ProjectModelTraceWindow::~ProjectModelTraceWindow()
{
    // TODO Auto-generated destructor stub
}

