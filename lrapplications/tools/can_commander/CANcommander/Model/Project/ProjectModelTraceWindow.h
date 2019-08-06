/*
 * ProjectModelTraceWindow.h
 *
 *  Created on: 30.07.2019
 *      Author: Andreas
 */

#ifndef _PROJECT_MODEL_TRACE_WINDOW_H_
#define _PROJECT_MODEL_TRACE_WINDOW_H_

// Qt includes
#include <QtCore/QVector>
#include <QtCore/QVariant>
#include <QtWidgets/QMenu>

// Project includes
#include "ProjectModelItem.h"

/**
 *
 */
class ProjectModelTraceWindowData
{
    public:
        ProjectModelTraceWindowData();
        ~ProjectModelTraceWindowData();
};

/**
 *
 */
class ProjectModelTraceWindow : public ProjectModelItem
{
    public:
        ProjectModelTraceWindow(QString itemName, ProjectModelItem* pParent);
        virtual ~ProjectModelTraceWindow();
};

#endif /* _PROJECT_MODEL_TRACE_WINDOW_H_ */
