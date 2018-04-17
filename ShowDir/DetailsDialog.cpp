#include "DetailsDialog.h"  
#include <thread>

DetailsDialog::~DetailsDialog()
{
	delete fileName;
	delete filePath;
	delete fileSize;
	delete gridLayout;
}

quint64 dirFileSize(const QString & path)
{
	QDir dir(path);
	QString recordPath = path;
	recordPath.replace("/", "").replace("\\", "");
	//dir.entryInfoList(QDir::Files)返回文件信息 
	foreach(QFileInfo fileInfo, dir.entryInfoList(QDir::Files))
	{
		//计算文件大小 
		record[recordPath].tmpSize += fileInfo.size();
	}

	//dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot)返回所有子目录，并进行过滤 
	foreach(QString subDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
	{
		//若存在子目录，则递归调用dirFileSize()函数 
		quint64 tmp = 0;
		QString subPath = path + QDir::separator() + subDir;
		tmp = dirFileSize(subPath);
		record[recordPath].tmpSize += tmp;
	}
	record[recordPath].size = record[recordPath].tmpSize;
	return record[recordPath].size;
}

DetailsDialog::DetailsDialog(QString name, QString path, quint64 size, QWidget *parent)
{

	resize(300, 200);
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);

	
	fileName = new QLabel(QString("File Path: " + name));
	filePath = new QLabel(QString("File Path: " + path));
	fileSize = new QLabel("File Size: " + QString::number(size) + " Byte");

	QFileInfo info(path);
	if (info.isDir())
	{
		QString recordPath = path;
		recordPath.replace("/", "").replace("\\", "");
		if (record[recordPath].size != 0)
		{
			fileSize->setText("File Size: " + QString::number(record[recordPath].size) + " Byte");
		}
		else
		{
			fileSize->setText("File Size: " + QString("Next reopen may show"));
			if (record[recordPath].tmpSize == 0)
			{
				std::thread t(dirFileSize, path);
				t.detach();
			}
		}
	}

	gridLayout = new QGridLayout;
	gridLayout->addWidget(fileName, 0, 0);
	gridLayout->addWidget(filePath, 1, 0);
	gridLayout->addWidget(fileSize, 2, 0);
	gridLayout->setColumnStretch(2, 2);

	setLayout(gridLayout);

	adjustSize();
}


