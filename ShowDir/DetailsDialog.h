#pragma once
#include "ui_DirGui.h"
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QFileInfo>
#include <QDir>
#include <map>
#include <QThread>

using namespace std;

struct dirRecord
{
	quint64 tmpSize;
	quint64 size;
};

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
};

static map<QString, dirRecord> record;
