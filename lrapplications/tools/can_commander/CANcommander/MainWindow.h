/*
 * MainWindow.h
 *
 *  Created on: 09.07.2019
 *      Author: Andreas
 */
#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

// Qt includes
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>

// Project includes
#include "ui_CANcommander.h"
#include "Model/Project/ProjectModel.h"
#include "Widgets/ProjectExplorerWidget.h"


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);

private:
	void createMenubar();
	void createToolbar();
	void createStatusbar();

	void createDockWidgets();
    void createMdiArea();

private:
    void actAbout();

private:
	Ui::CANcommanderClass ui;

	QMdiArea* pMDIArea;

	ProjectExplorerWidget* m_pProjectExplorer;
};

#endif
