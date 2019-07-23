/*
 * ModelRepository.cpp
 *
 *  Created on: 11.07.2019
 *      Author: Andreas
 */

// Qt includes

// Project includes
#include "UIRepository.h"

UIRepository* UIRepository::m_pInstance = nullptr;

/**
 * Default constructor
 */
UIRepository::UIRepository()
{

}

/**
 * Copy Constructor
 */
UIRepository::UIRepository(const UIRepository& repo)
    : UIRepository()
{

}

/**
 * Destructor
 */
UIRepository::~UIRepository()
{

}

/**
 *
 */
UIRepository* UIRepository::getInstance()
{
   static CGuard guard;

   if (m_pInstance == nullptr)
   {
       m_pInstance = new UIRepository();
   }

   return m_pInstance;
}

/**
 *
 */
void UIRepository::setMainWindow(QMainWindow* pMainWindow)
{
   m_pMainWindow = pMainWindow;
}

/**
 *
 */
QMainWindow* UIRepository::getMainWindow()
{
    return m_pMainWindow;
}

/**
 *
 */
void UIRepository::setMDIArea(QMdiArea* pMDIArea)
{
   m_pMDIArea = pMDIArea;
}

/**
 *
 */
QMdiArea* UIRepository::getMDIArea()
{
    return m_pMDIArea;
}
