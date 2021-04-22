#ifndef ISH_PARSER
#define ISH_PARSER
#include <QObject>
#include <QProcess>
#include <QDir>
#include <QDebug>

static QString ish_path = "../data/isaac-secret-helper_1.0/IsaacSecretHelper.exe";
static QString arguments = R"(-p  C:/DEV/perso/dist/bin/data/mysave -u)";


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
};
#endif // !ISH_PARSER
