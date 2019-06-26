#include "CANcommander.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CANcommander w;
	w.show();
	return a.exec();
}
