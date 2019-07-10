/*
 * canhwinterfaceoptiondlg.cpp
 *
 *  Created on: 10.07.2019
 *      Author: Andreas
 */

// Qt Includes
#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLayout>

// Project includes
#include "ui_CANHwInterfaceOptionDlg.h"
#include "canhwinterfaceoptiondlg.h"

/**
 *
 */
CANHwInterfaceOptionDlg::CANHwInterfaceOptionDlg(QWidget *parent)
    : QDialog(parent)
{
    m_UI.setupUi(this);
    setFixedSize(size());

    initializeCOMPortUI();
    initializeCANUI();

    m_pInterface = nullptr;
}

/**
 *
 */
void CANHwInterfaceOptionDlg::setInterfaceItem(ProjectModelHWInterface* pItem)
{
   m_pInterface = pItem;

   int index = m_UI.cmbCOMPort->findData(m_pInterface->getHWInterfaceData()->getPortName());
   if (index != -1)
   {
       m_UI.cmbCOMPort->setCurrentIndex(index);
   }

   index = m_UI.cmbPortBaudrate->findData(m_pInterface->getHWInterfaceData()->getPortBaudrate());
   if (index != -1)
   {
       m_UI.cmbPortBaudrate->setCurrentIndex(index);
   }

   index = m_UI.cmbCANBaudrate->findData(m_pInterface->getHWInterfaceData()->getInterfaceBaudrate());
   if (index != -1)
   {
       m_UI.cmbCANBaudrate->setCurrentIndex(index);
   }
}

/**
 *
 */
void CANHwInterfaceOptionDlg::initializeCOMPortUI()
{
   m_UI.cmbCOMPort->addItem("COM1", QVariant("COM1"));
   m_UI.cmbCOMPort->addItem("COM2", QVariant("COM2"));
   m_UI.cmbCOMPort->addItem("COM3", QVariant("COM3"));
   m_UI.cmbCOMPort->addItem("COM4", QVariant("COM4"));
   m_UI.cmbCOMPort->addItem("COM5", QVariant("COM5"));

   m_UI.cmbPortBaudrate->addItem("9600", QVariant(9600));
   m_UI.cmbPortBaudrate->addItem("115200", QVariant(115200));
}

/**
 *
 */
void CANHwInterfaceOptionDlg::initializeCANUI()
{
   m_UI.cmbCANBaudrate->addItem("10k", QVariant(10000));
   m_UI.cmbCANBaudrate->addItem("20k", QVariant(20000));
   m_UI.cmbCANBaudrate->addItem("50k", QVariant(50000));
   m_UI.cmbCANBaudrate->addItem("100k", QVariant(100000));
   m_UI.cmbCANBaudrate->addItem("125k", QVariant(125000));
   m_UI.cmbCANBaudrate->addItem("250k", QVariant(250000));
   m_UI.cmbCANBaudrate->addItem("500k", QVariant(500000));
   m_UI.cmbCANBaudrate->addItem("800k", QVariant(800000));
   m_UI.cmbCANBaudrate->addItem("1M", QVariant(1000000));
}
