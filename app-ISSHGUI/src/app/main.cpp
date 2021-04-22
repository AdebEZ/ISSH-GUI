#include <QtWidgets/QApplication>
#include <QDebug>

#include "gui/ISSHGUI_MainWindow.h"


int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	
	ISSHGUI_MainWindow* mw = new ISSHGUI_MainWindow();
	mw->show();

	return app.exec();
}