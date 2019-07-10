/*
 * canhwinterfaceoptiondlg.h
 *
 *  Created on: 10.07.2019
 *      Author: Andreas
 */

#ifndef _UI_CANHWINTERFACEOPTIONDLG_H_
#define _UI_CANHWINTERFACEOPTIONDLG_H_

// Qt includes
#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>

// Project includes
#include "Model/ProjectModelItem.h"
#include "Model/ProjectModelHWInterface.h"

#include "ui_CANHwInterfaceOptionDlg.h"

class CANHwInterfaceOptionDlg : public QDialog
{
    public:
        CANHwInterfaceOptionDlg(QWidget *parent = nullptr);

        void setInterfaceItem(ProjectModelHWInterface* pItem);

    private:
        void initializeCOMPortUI();
        void initializeCANUI();

    private:
        Ui::CANHwInterfaceOptionDlg m_UI;

        ProjectModelHWInterface* m_pInterface;
};

#endif /* _UI_CANHWINTERFACEOPTIONDLG_H_ */
