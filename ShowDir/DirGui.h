#pragma once

#include <QtWidgets/QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QMenu>
#include <QPushbutton>
#include "ui_DirGui.h"
#include "DetailsDialog.h"

class DirGui : public QWidget
{
	Q_OBJECT

public:
	DirGui(QWidget *parent = Q_NULLPTR);
	~DirGui();

private:
	Ui::DirGuiClass ui;

	QFileSystemModel * dirModel;	// Ŀ¼ģ��
	QTreeView * dirTreeView;		// Ŀ¼���νṹ
	QLineEdit * dirEdit;			// �����
	QPushButton * expandButton;		// չ����ť
	QPushButton * collapseButton;	// �۵���ť
	QPushButton * detailsButton;	// ����

	QString windowTitle;

	void initDirModel();
	void initDirTreeView();
	void initHeadFrame();
	void initFontFrame();
	void initLayout();

// slot
private:
	void onLineTextChangedToShowDir();  // ��������ֱ仯ʱ��ʾ�������
	void enableDetailsButton();			
	void expandDir();					// չ��Ŀ¼��
	void collapseDir();					// �۵�Ŀ¼��
	void showDetails();					// ��ʾ����
};
