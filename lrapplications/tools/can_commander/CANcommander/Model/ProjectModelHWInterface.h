/*
 * ProjectModelFolderItem.h
 *
 *  Created on: 09.07.2019
 *      Author: Andreas
 */
#ifndef _PROJECTMODELHWINTERFACE_H_
#define _PROJECTMODELHWINTERFACE_H_

// Qt includes
#include <QtCore/QVector>
#include <QtCore/QVariant>

// Project includes
#include "ProjectModelItem.h"

/**
 * Class encapsulating the data needed to describe a CAN HW Interface
 * like USBtin
 */
class HWInterfaceData
{
    public:
        HWInterfaceData();
        HWInterfaceData(QString interfaceName);

        void setInterfaceName(QString interfaceName);
        QString getInterfaceName();

        void setInterfaceBaudrate(int interfaceBaudrate);
        int getInterfaceBaudrate();

        void setPortName(QString portName);
        QString getPortName();

        void setPortBaudrate(int portBaudrate);
        int getPortBaudrate();

    private:
        QString m_InterfaceName;
        QString m_PortName;
        int m_PortBaudrate;

        int m_InterfaceBaudrate;
};

// Make the HWInterfaceData compliant to the QVariant
Q_DECLARE_METATYPE(HWInterfaceData);

/**
 * Class for a HW interface in the project model tree.
 */
class ProjectModelHWInterface : public ProjectModelItem
{
    public:
        ProjectModelHWInterface(QString itemName, ProjectModelItem* pParent);
        virtual ~ProjectModelHWInterface();

        virtual QVariant getData();

        HWInterfaceData* getHWInterfaceData();

    private:
        HWInterfaceData* m_pHWInterface;
};

#endif
