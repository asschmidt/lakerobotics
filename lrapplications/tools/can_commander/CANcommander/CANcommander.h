#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CANcommander.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);

private:
	Ui::CANcommanderClass ui;
};
