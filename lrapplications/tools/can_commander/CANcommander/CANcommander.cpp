#include "CANcommander.h"
#include "CANMessage.h"

#include <QSettings>

#include "CANcore.h"
#include "XmlSettings.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	/*CANMessage myMsg(QString("T12345678197"));

	unsigned char data1[] = { 0x97, 0, 0, 0, 0, 0, 0, 0 };
	CANMessage msg1(0x12345678, 1, data1);
	QString msg1Str = msg1.toString();

	unsigned char data2[] = { 0x11, 0x22, 0, 0, 0, 0, 0, 0 };
	CANMessage msg2(0x001, 2, data2);
	QString msg2Str = msg2.toString();*/

	/*QSettings::Format xmlFormat = registerXmlSettingsFormat();

	QSettings settings(xmlFormat, QSettings::UserScope, "LakeRobotics", "CANcommander");

	QString canChannel1 = settings.value("Hardware/CAN1").toString();

	settings.beginGroup("Hardware");
	settings.setValue("CAN1", "COM3");	
	settings.endGroup();*/
}
