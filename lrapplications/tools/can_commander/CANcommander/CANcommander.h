#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CANcommander.h"

class CANcommander : public QMainWindow
{
	Q_OBJECT

public:
	CANcommander(QWidget *parent = Q_NULLPTR);

private:
	Ui::CANcommanderClass ui;
};
