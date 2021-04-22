#include "gui/ISSHGUI_MainWindow.h"

ISSHGUI_MainWindow::ISSHGUI_MainWindow(QWidget* parent) 
	: QMainWindow(parent)
{
	ui.setupUi(this);
	qDebug() << "lets go";

	QObject::connect(ui.pbSave1, SIGNAL(clicked()), this, SLOT(save1selected()));
	QObject::connect(ui.pbSave2, SIGNAL(clicked()), this, SLOT(save2selected()));
	QObject::connect(ui.pbSave3, SIGNAL(clicked()), this, SLOT(save3selected()));
}

ISSHGUI_MainWindow::~ISSHGUI_MainWindow()
{

}

void ISSHGUI_MainWindow::save1selected()
{
	qDebug() << "selecting file 1";
	parser = new ISHParser(1);
}

void ISSHGUI_MainWindow::save2selected()
{
	qDebug() << "selecting file 2";
	parser = new ISHParser(2);
		
}

void ISSHGUI_MainWindow::save3selected()
{
	qDebug() << "selecting file 3";
	parser = new ISHParser(3);
}