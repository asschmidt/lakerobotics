/*
 * QuickTraceAction.h
 *
 *  Created on: 14.07.2019
 *      Author: Andreas
 */

#ifndef _QUICK_TRACE_ACTION_H_
#define _QUICK_TRACE_ACTION_H_

// Qt includes
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>

// Project Includes
#include "Model/Project/ProjectModelItem.h"
#include "Model/Project/ProjectModelHWInterface.h"

/**
 *
 */
class QuickTraceAction : public QObject
{
    Q_OBJECT

    public:
        QuickTraceAction(ProjectModelHWInterface* pHWInterface, QObject* pParent);

    public slots:
        void execute();

    private:
        ProjectModelHWInterface* m_pHWInterface;
};

#endif /* _QUICK_TRACE_ACTION_H_ */
