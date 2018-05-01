#include "DetailsDialog.h"  
#include <thread>
#include <iostream>

DetailsDialog::~DetailsDialog()
{
	delete fileName;
	delete filePath;
	delete fileSize;
	delete gridLayout;
}

quint64 DetailsDialog::calcSubDirSize(const QString &path)
{
	QString recordPath = path;
	recordPath.replace("/", "").replace("\\", "");
	if (record[recordPath].size)
		return record[recordPath].size;

	record[recordPath].isCalc = true;
	stack<QString> s;
	s.push(path);

	//QLockFile lock(path);
	//lock.lock();
	quint64 size = 0;
	while (!s.empty())
	{
		QString p = s.top();
		s.pop();

		QDir dir(p);
		//dir.entryInfoList(QDir::Files)返回文件信息 
		foreach(QFileInfo fileInfo, dir.entryInfoList(QDir::Files))
		{
			//计算文件大小 
			size += fileInfo.size();
		}

		//dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot)返回所有子目录，并进行过滤 
		foreach(QString subDir, dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot))
		{
			//若存在子目录，入栈
			QString subPath = p + QDir::separator() + subDir;
			s.push(subPath);
		}
	}
	//lock.unlock();
	
	record[recordPath].size = size;
	return size;
}

quint64 DetailsDialog::dirFileSize(const QString & path)
{
	quint64 size = 0;
	
	QDir dir(path);
	//dir.entryInfoList(QDir::Files)返回文件信息 
	foreach(QFileInfo fileInfo, dir.entryInfoList(QDir::Files))
	{
		//计算文件大小 
		size += fileInfo.size();
	}

	fileSize->setText(QString::number(size) + " Byte (loading...)");

	//dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot)返回所有子目录，并进行过滤 
	foreach(QString subDir, dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot))
	{
		QString subPath = path + QDir::separator() + subDir;
		size += calcSubDirSize(subPath);
		fileSize->setText(QString::number(size) + " Byte (loading...)");
	}

	QString recordPath = path;
	recordPath.replace("/", "").replace("\\", "");
	record[recordPath].size = size;
	fileSize->setText(QString::number(size) + " Byte");
	return size;
}

void DetailsDialog::waitFileSize(const QString &path)
{
	while (!record[path].size);
	fileSize->setText(QString::number(record[path].size) + " Byte");
}

DetailsDialog::DetailsDialog(QString name, QString path, quint64 size, QWidget *parent)
{

	resize(300, 200);
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);
	setWindowTitle(path);

	fileNameText = new QLabel(QString("File Name: " ));
	fileSizeText = new QLabel(QString("File Size: " ));
	filePathText = new QLabel(QString("File Path: " ));

	fileName = new QLabel(name);
	filePath = new QLabel(path);
	fileSize = new QLabel(QString::number(size) + " Byte");

	QFileInfo info(path);
	if (info.isDir())
	{
		QString recordPath = path;
		recordPath.replace("/", "").replace("\\", "");
		if (record[recordPath].size != 0)
		{
			fileSize->setText(QString::number(record[recordPath].size) + " Byte");
		}
		else
		{
			fileSize->setText(QString("Size loading..."));
			
			if (!record[recordPath].isCalc)
			{
				record[recordPath].isCalc = true;
				std::thread t(&DetailsDialog::dirFileSize, this, path);
				t.detach();
			}
			else
			{
				std::thread t(&DetailsDialog::waitFileSize, this, recordPath);
				t.detach();
			}
		}
	}

	gridLayout = new QGridLayout;
	gridLayout->addWidget(fileNameText, 0, 0);
	gridLayout->addWidget(fileName, 0, 1);
	gridLayout->addWidget(filePathText, 1, 0);
	gridLayout->addWidget(filePath, 1, 1);
	gridLayout->addWidget(fileSizeText, 2, 0);
	gridLayout->addWidget(fileSize, 2, 1);

	setLayout(gridLayout);

	adjustSize();
}


