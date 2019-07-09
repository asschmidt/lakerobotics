/*
 * main.cpp
 *
 *  Created on: 09.07.2019
 *      Author: Andreas
 */
#include "MainWindow.h"
#include <QtWidgets/QApplication>

/**
 *
 */
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MainWindow w;
	w.show();

	return a.exec();
}
