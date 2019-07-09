/*
 * MainWindow.h
 *
 *  Created on: 09.07.2019
 *      Author: Andreas
 */
#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QtWidgets/QMainWindow>
#include "ui_CANcommander.h"

class QMdiArea;
class QMdiSubWindow;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);

private:
	Ui::CANcommanderClass ui;

	QMdiArea* pMDIArea;
};

#endif
