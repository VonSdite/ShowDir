#include "DirGui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	DirGui ui;
	ui.show();
	return app.exec();
}
