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

	QFileSystemModel * dirModel;	// 目录模型
	QTreeView * dirTreeView;		// 目录树形结构
	QLineEdit * dirEdit;			// 输入框
	QPushButton * confirmButton;	// 确认按钮
	QPushButton * detailsButton;	// 属性

	void initDirModel();
	void initDirTreeView();
	void initEditFrame();
	void initLayout();

	// slot
private:
	void showDir();					// 显示搜索结果
	void showDetails();				// 显示详情

	void onlineTreeViewClick();
};
