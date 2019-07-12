/*
 * ModelRepository.h
 *
 *  Created on: 11.07.2019
 *      Author: Andreas
 */

#ifndef _MODEL_REPOSITORY_H_
#define _MODEL_REPOSITORY_H_

// Project includes
#include "ProjectModel.h"
#include "CANModel.h"

class ModelRepository
{
    public:
        static ModelRepository* getInstance();

        void createDefaultProjectModel();

        ProjectModel* getProjectModel();
        CANModel* getCANModel();

    private:
        ModelRepository();
        ModelRepository(const ModelRepository&);
        ~ModelRepository();

        // Guard class for memory clean up
        class CGuard
        {
            public:
                ~CGuard()
                {
                    if (ModelRepository::m_pInstance != nullptr)
                    {
                        delete ModelRepository::m_pInstance;
                        ModelRepository::m_pInstance = nullptr;
                    }
                }
        };

        static ModelRepository* m_pInstance;

        ProjectModel* m_pProjectModel;
        CANModel* m_pCANModel;
};



#endif /* _MODEL_REPOSITORY_H_ */
