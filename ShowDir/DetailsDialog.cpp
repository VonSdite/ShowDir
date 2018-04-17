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
	//dir.entryInfoList(QDir::Files)�����ļ���Ϣ 
	foreach(QFileInfo fileInfo, dir.entryInfoList(QDir::Files))
	{
		//�����ļ���С 
		record[recordPath].tmpSize += fileInfo.size();
	}

	//dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot)����������Ŀ¼�������й��� 
	foreach(QString subDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
	{
		//��������Ŀ¼����ݹ����dirFileSize()���� 
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


