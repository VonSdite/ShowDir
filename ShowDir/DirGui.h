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
	QPushButton * confirmButton;	// ȷ�ϰ�ť
	QPushButton * detailsButton;	// ����

	void initDirModel();
	void initDirTreeView();
	void initEditFrame();
	void initLayout();

	// slot
private:
	void showDir();					// ��ʾ�������
	void showDetails();				// ��ʾ����

	void collaspeTreeView();

	void onlineTreeViewClick();
};
