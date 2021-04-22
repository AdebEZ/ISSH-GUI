#ifndef ISH_PARSER
#define ISH_PARSER
#include <QObject>
#include <QProcess>
#include <QDir>
#include <QDebug>

#include <windows.h>
#include <stdio.h>
 


static QString ish_path = "../data/isaac-secret-helper_1.0/IsaacSecretHelper.exe";
static QString arguments = "-p  ../data/mysave/ -u";


class ISHParser : public QObject
{
	Q_OBJECT

signals:
public slots:
	void readOutput();

public:
	ISHParser(int save = 1);
	~ISHParser();

private:
	QProcess* process;

	void startExternalProgram();
	void startExternalProgramWithQt();

};
#endif // !ISH_PARSER
