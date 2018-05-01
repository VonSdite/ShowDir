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
	QPushButton * expandButton;		// 展开按钮
	QPushButton * collapseButton;	// 折叠按钮
	QPushButton * detailsButton;	// 属性

	QString windowTitle;

	void initDirModel();
	void initDirTreeView();
	void initHeadFrame();
	void initFontFrame();
	void initLayout();

// slot
private:
	void onLineTextChangedToShowDir();  // 输入框文字变化时显示搜索结果
	void enableDetailsButton();			
	void expandDir();					// 展开目录树
	void collapseDir();					// 折叠目录树
	void showDetails();					// 显示详情
};
