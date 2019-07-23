/*
 * ProjectModelHWInterface.cpp
 *
 *  Created on: 09.07.2019
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
#include "Ui/QuickTraceAction.h"

/**
 *
 */
HWInterfaceData::HWInterfaceData()
    : HWInterfaceData("CANx")
{

}

/**
 *
 */
HWInterfaceData::HWInterfaceData(QString interfaceName)
{
    m_InterfaceName = interfaceName;
    m_InterfaceBaudrate = 125000;

    m_PortName = "COM4";
    m_PortBaudrate = 115200;

    m_InterfaceEnabled = true;
}

/**
 *
 */
void HWInterfaceData::setInterfaceName(QString interfaceName)
{
    m_InterfaceName = interfaceName;
}

/**
 *
 */
QString HWInterfaceData::getInterfaceName()
{
    return m_InterfaceName;
}

/**
 *
 */
void HWInterfaceData::setInterfaceBaudrate(int interfaceBaudrate)
{
    m_InterfaceBaudrate = interfaceBaudrate;
}

/**
 *
 */
int HWInterfaceData::getInterfaceBaudrate()
{
    return m_InterfaceBaudrate;
}

/**
 *
 */
void HWInterfaceData::setPortName(QString portName)
{
    m_PortName = portName;
}

/**
 *
 */
QString HWInterfaceData::getPortName()
{
    return m_PortName;
}

/**
 *
 */
void HWInterfaceData::setPortBaudrate(int portBaudrate)
{
    m_PortBaudrate = portBaudrate;
}

/**
 *
 */
int HWInterfaceData::getPortBaudrate()
{
    return m_PortBaudrate;
}

/**
 *
 */
bool HWInterfaceData::isEnabled()
{
   return m_InterfaceEnabled;
}

/**
 *
 */
void HWInterfaceData::setEnabled(bool enabled)
{
   m_InterfaceEnabled = enabled;
}

/**
 *
 */
ProjectModelHWInterface::ProjectModelHWInterface(QString itemName, ProjectModelItem* pParent)
    : ProjectModelItem(itemName, HW_INTERFACE_ITEM, pParent)
{
    // Create the initial interface data object
    m_pHWInterface = new HWInterfaceData("CANx");
}

/**
 * Destructor
 * Deletes all child objects of this project model item
 */
ProjectModelHWInterface::~ProjectModelHWInterface()
{
    delete m_pHWInterface;
}

/**
 *
 */
HWInterfaceData* ProjectModelHWInterface::getHWInterfaceData()
{
    return m_pHWInterface;
}

/**
 * Returns the item name as folder data
 * For a folder item the name (also used in UI) is the only data this item has
 */
QVariant ProjectModelHWInterface::getData(const QModelIndex& index)
{
    QVariant interfaceVariant(m_pHWInterface->getInterfaceName());
    return interfaceVariant;
}

/**
 * Default implementation doesn't return a menu.
 */
QMenu* ProjectModelHWInterface::createItemContextMenu(QMenu* pParentMenu)
{
    QAction* pQuickTraceActionUi = new QAction("Quick Trace Window", pParentMenu->parentWidget());
    QuickTraceAction* pQuickTraceAction = new QuickTraceAction(this, pQuickTraceActionUi);

    QObject::connect(pQuickTraceActionUi, SIGNAL(triggered()), pQuickTraceAction, SLOT(execute()));
    pParentMenu->addAction(pQuickTraceActionUi);

    return pParentMenu;
}
