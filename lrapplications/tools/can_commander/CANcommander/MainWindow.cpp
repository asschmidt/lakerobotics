/*
 * MainWindow.cpp
 *
 *  Created on: 09.07.2019
 *      Author: Andreas
 */

// Standard includes
#include <iostream>

// Qt Includes
#include <QtCore/QSettings>
#include <QtWidgets/QtWidgets>
#include <QtWidgets/QMenu>

// CANcore DLL includes
#include "CAN/CANMessage.h"
#include "Utils/XmlSettings.h"

// Project includes
#include "Model/Project/ProjectModel.h"
#include "Model/Project/ProjectDefaultModel.h"
#include "Model/ModelRepository.h"

#include "Accquire/CANThreadManager.h"

#include "Widgets/ProjectExplorerWidget.h"
#include "Ui/UIRepository.h"

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

	UIRepository::getInstance()->setMainWindow(this);

	ModelRepository::getInstance()->createDefaultProjectModel();
	m_ThreadManager = new CANThreadManager(ModelRepository::getInstance()->getCANModel());

	createMenubar();
	createToolbar();
	createStatusbar();
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
void MainWindow::createMenubar()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    fileMenu->addSeparator();

    const QIcon exitIcon = QIcon::fromTheme("application-exit");
    QAction *exitAct = fileMenu->addAction(exitIcon, tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));


    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::actAbout);
    aboutAct->setStatusTip(tr("Show the application's About box"));
}

/**
 *
 */
void MainWindow::createToolbar()
{
    QToolBar* pMeasurementToolBar = addToolBar("Measurement");

    QAction* pStartAction = new QAction(this);
    QPixmap* pStartIcon = new QPixmap(":/Images/media-playback-start.svg");
    pStartAction->setIcon(*pStartIcon);

    pMeasurementToolBar->addAction(pStartAction);
    connect(pStartAction, SIGNAL(triggered()), this, SLOT(actStartMeasurement()));

    QAction* pStopAction = new QAction(this);
    QPixmap* pStopIcon = new QPixmap(":/Images/media-playback-pause.svg");
    pStopAction->setIcon(*pStopIcon);

    pMeasurementToolBar->addAction(pStopAction);
    connect(pStopAction, SIGNAL(triggered()), this, SLOT(actStopMeasurement()));
}

/**
 *
 */
void MainWindow::createStatusbar()
{
    statusBar()->showMessage(tr("Ready"));
}

/**
 *
 */
void MainWindow::createMdiArea()
{
    pMDIArea = new QMdiArea();
    pMDIArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    pMDIArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setCentralWidget(pMDIArea);

    UIRepository::getInstance()->setMDIArea(pMDIArea);
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
    this->addDockWidget(Qt::LeftDockWidgetArea, dock);

    // Create a temporary project model
    ProjectModel* pProjectModel = ModelRepository::getInstance()->getProjectModel();
    m_pProjectExplorer->setProjectModel(pProjectModel);
}

/**
 *
 */
void MainWindow::actAbout()
{
    QMessageBox::about(this, tr("About CANcommander"), tr("The <b>CANcommander</b> is a CAN Analyzer SW "));
}

/**
 *
 */
void MainWindow::actStartMeasurement()
{
    statusBar()->showMessage(tr("Starting Measurement..."));

    // Get all HW Interfaces where we want to start the measurement
    QVector<ProjectModelItem*>* pItemList = ModelRepository::getInstance()->getProjectModel()->getAllItemsOfType(HW_INTERFACE_ITEM);
    if (pItemList != nullptr)
    {
        for( int i=0; i<pItemList->count(); i++)
        {
            // Get the HW interface object
            ProjectModelHWInterface* pItem = static_cast<ProjectModelHWInterface*>(pItemList->at(i));
            std::cout << "Creating Thread for HW Interface: " << pItem->getName().toStdString() << " (" << pItem->getHWInterfaceData()->getInterfaceName().toStdString() << ")" << std::endl;

            // If it is enabled, then create a thread for it
            if (pItem->getHWInterfaceData()->isEnabled() == true)
            {
                QString interfacePort = pItem->getHWInterfaceData()->getPortName();
                int interfaceBaudrate = pItem->getHWInterfaceData()->getInterfaceBaudrate();
                QString interfaceName = pItem->getHWInterfaceData()->getInterfaceName();

                // Create the HW interface object and open the channel
                USBtin* pCANInterface = new USBtin();
                pCANInterface->connect(interfacePort);
                pCANInterface->openCANChannel(interfaceBaudrate, ACTIVE);

                m_ThreadManager->createCANThread(interfaceName, pCANInterface);
            }

        }
    }

    delete pItemList;

    m_ThreadManager->startAllThreads();
}

/**
 *
 */
void MainWindow::actStopMeasurement()
{
    statusBar()->showMessage(tr("Measurement stopped"));
    m_ThreadManager->stopAllThreads();
}
