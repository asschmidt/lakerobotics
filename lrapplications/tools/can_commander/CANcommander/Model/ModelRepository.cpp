/*
 * ModelRepository.cpp
 *
 *  Created on: 11.07.2019
 *      Author: Andreas
 */

// Qt includes

// Project includes
#include "Project/ProjectModel.h"
#include "Project/ProjectDefaultModel.h"
#include "CAN/CANModel.h"

#include "ModelRepository.h"

ModelRepository* ModelRepository::m_pInstance = nullptr;

/**
 * Default constructor
 */
ModelRepository::ModelRepository()
{
    m_pProjectModel = nullptr;
    m_pCANModel = new CANModel();
}

/**
 * Copy Constructor
 */
ModelRepository::ModelRepository(const ModelRepository& repo)
    : ModelRepository()
{

}

/**
 * Destructor
 */
ModelRepository::~ModelRepository()
{

}

/**
 *
 */
ModelRepository* ModelRepository::getInstance()
{
   static CGuard guard;

   if (m_pInstance == nullptr)
   {
       m_pInstance = new ModelRepository();
   }

   return m_pInstance;
}

/**
 *
 */
void ModelRepository::createDefaultProjectModel()
{
    m_pProjectModel = new ProjectDefaultModel("Default");
}

/**
 *
 */
ProjectModel* ModelRepository::getProjectModel()
{
    return m_pProjectModel;
}

/**
 *
 */
CANModel* ModelRepository::getCANModel()
{
    return m_pCANModel;
}
