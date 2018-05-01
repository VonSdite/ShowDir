#pragma once
#include "ui_DirGui.h"
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QFileInfo>
#include <QDir>
#include <map>
#include <stack>
#include <QThread>
#include <QLockFile>

using namespace std;

struct dirRecord
{
	quint64 size;
	bool isCalc;
};

static map<QString, dirRecord> record;

class DetailsDialog : public QDialog
{
	Q_OBJECT

public:
	DetailsDialog(QString fileName, QString filePath, quint64 fileSize, QWidget *parent = Q_NULLPTR);
	~DetailsDialog();


private:
	QGridLayout * gridLayout;
	QLabel * fileName;
	QLabel * fileSize;
	QLabel * filePath;

	QLabel * fileNameText;
	QLabel * fileSizeText;
	QLabel * filePathText;
	quint64 dirFileSize(const QString & path);
	quint64 calcSubDirSize(const QString &path);
	void waitFileSize(const QString &path);
};


