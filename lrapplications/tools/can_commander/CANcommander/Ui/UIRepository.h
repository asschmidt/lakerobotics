/*
 * UIRepository.h
 *
 *  Created on: 11.07.2019
 *      Author: Andreas
 */

#ifndef _UI_REPOSITORY_H_
#define _UI_REPOSITORY_H_

// Qt includes
#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>

// Project includes

class UIRepository
{
    public:
        static UIRepository* getInstance();

        void setMainWindow(QMainWindow* pMainWindow);
        QMainWindow* getMainWindow();

        void setMDIArea(QMdiArea* pMDIArea);
        QMdiArea* getMDIArea();

    private:
        UIRepository();
        UIRepository(const UIRepository&);
        ~UIRepository();

        // Guard class for memory clean up
        class CGuard
        {
            public:
                ~CGuard()
                {
                    if (UIRepository::m_pInstance != nullptr)
                    {
                        delete UIRepository::m_pInstance;
                        UIRepository::m_pInstance = nullptr;
                    }
                }
        };

        static UIRepository* m_pInstance;

    private:
        QMainWindow* m_pMainWindow;
        QMdiArea* m_pMDIArea;
};



#endif /* _UI_REPOSITORY_H_ */
