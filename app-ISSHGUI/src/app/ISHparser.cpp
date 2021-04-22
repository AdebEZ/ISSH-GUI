#include "app/ISHparser.h"

ISHParser::ISHParser(int save)
{
	qDebug() << "new process!";
	process = new QProcess(this);
	QObject::connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput())); 
	QObject::connect(process, &QProcess::errorOccurred, [=](QProcess::ProcessError pe) {
		qDebug() << "error";
		qDebug() << pe;
	}
	);
	process->setProcessChannelMode(QProcess::MergedChannels);
	process->setNativeArguments(arguments); //https://doc.qt.io/qt-5/qprocess.html#start
	process->start(ish_path); 
}

ISHParser::~ISHParser()
{

}

void ISHParser::readOutput()
{
	qDebug() << "reading output";
	qDebug() << process->readAllStandardError();
	qDebug() << process->readAllStandardOutput();
}