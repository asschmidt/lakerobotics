/*
 * ProjectDefaultModel.h
 *
 *  Created on: 10.07.2019
 *      Author: Andreas
 */

#ifndef _PROJECTDEFAULT_MODEL_H_
#define _PROJECTDEFAULT_MODEL_H_

// Qt includes
#include <QtCore/QString>

// Project includes
#include "ProjectModelItem.h"
#include "ProjectModelFolderItem.h"
#include "ProjectModelHWInterface.h"
#include "ProjectModel.h"

class ProjectDefaultModel : public ProjectModel
{
    public:
        ProjectDefaultModel(QString rootName);
        ~ProjectDefaultModel();

    private:
        ProjectModelFolderItem* m_pProjectNode;
        ProjectModelFolderItem* m_pHWInterfaces;
        ProjectModelFolderItem* m_pDataFiles;

        ProjectModelHWInterface* m_pMainCAN;
};

#endif /* _PROJECTDEFAULT_MODEL_H_ */
