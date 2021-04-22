#include <QtWidgets/QApplication>
#include <QDebug>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	qDebug() << "hello world";

	return app.exec();
}