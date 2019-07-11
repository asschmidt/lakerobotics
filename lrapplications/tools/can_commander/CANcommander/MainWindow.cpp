/*
 * MainWindow.cpp
 *
 *  Created on: 09.07.2019
 *      Author: Andreas
 */

// Qt Includes
#include <QtWidgets/QtWidgets>
#include <QtCore/QSettings>

// CANcore DLL includes
#include "CAN/CANMessage.h"
#include "Utils/XmlSettings.h"

// Project includes
#include "Model/ProjectModel.h"
#include "Model/ProjectDefaultModel.h"

#include "Widgets/ProjectExplorerWidget.h"

#include "CAN/CANMessage.h"
#include "CAN/USBtin.h"

#include "MainWindow.h"

/**
 *
 */
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

    createMdiArea();
	createDockWidgets();

	/*CANMessage myMsg(QString("T12345678197"));

	unsigned char data1[] = { 0x97, 0, 0, 0, 0, 0, 0, 0 };
	CANMessage msg1(0x12345678, 1, data1);
	QString msg1Str = msg1.toString();

	unsigned char data2[] = { 0x11, 0x22, 0, 0, 0, 0, 0, 0 };
	CANMessage msg2(0x001, 2, data2);
	QString msg2Str = msg2.toString();

	QSettings::Format xmlFormat = registerXmlSettingsFormat();

	QSettings settings(xmlFormat, QSettings::UserScope, "LakeRobotics", "CANcommander");

	QString canChannel1 = settings.value("Hardware/CAN1").toString();

	settings.beginGroup("Hardware");
	settings.setValue("CAN1", "COM3");	
	settings.endGroup();*/

	/*USBtin usbtin;
	usbtin.connect("COM4");
	usbtin.openCANChannel(125000, ACTIVE);

	unsigned char data1[] = { 0x97, 0, 0, 0, 0, 0, 0, 0 };
    CANMessage msg1(0x12345678, 1, data1);
    usbtin.sendMessageToFIFO(&msg1);
    usbtin.sendFirstFIFOMessage();

    QQueue<CANMessage*> receiveQueue;

    for (int i=0; i<10; i++)
    {
        usbtin.receiveMessages(receiveQueue);
    }*/
}

/**
 *
 */
void MainWindow::createMdiArea()
{
    pMDIArea = new QMdiArea();
    pMDIArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    pMDIArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(pMDIArea);
}

/**
 *
 */
void MainWindow::createDockWidgets()
{
    // Create the Dock widget for Project Explorer
    QDockWidget *dock = new QDockWidget(tr("Project Explorer"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    // Create the project explorer and add it to the dock widget
    m_pProjectExplorer = new ProjectExplorerWidget(dock);
    dock->setWidget(m_pProjectExplorer);
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    // Create a temporary project model
    m_pProjectModel = new ProjectDefaultModel("Root Item");
    m_pProjectExplorer->setProjectModel(m_pProjectModel);
}
