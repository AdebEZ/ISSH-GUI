#ifndef ISSHGUI_MW
#define ISSHGUI_MW

#include <QMainWindow>
#include <QDebug>

#include "app/ISHparser.h"

#include "ui_ISSHGUI_MainWindow.h"

class ISSHGUI_MainWindow : public QMainWindow
{
	Q_OBJECT

signals:

public slots:
	void save1selected();
	void save2selected();
	void save3selected();


public:
	ISSHGUI_MainWindow(QWidget* parent = nullptr);
	~ISSHGUI_MainWindow();

private:
	Ui::ISSHGUI_MainWindowClass ui;

	ISHParser* parser;

	void loadAndParseSaveFile();

};

#endif