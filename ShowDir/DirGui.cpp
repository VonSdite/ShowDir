#include "DirGui.h"

// 析构函数
DirGui::~DirGui()
{
	delete dirModel;
	delete dirTreeView;
	delete dirEdit;
	delete expandButton;
	delete collapseButton;
	delete detailsButton;
}

// 构造函数
DirGui::DirGui(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	windowTitle = "Show Dir";
	resize(800, 500);							// 窗口大小 
	setWindowTitle(windowTitle);				// 窗口标题
	setWindowIcon(QIcon("Resources/search.png"));

	// 初始化目录模型
	initDirModel();

	// 初始化目录树形结构
	initDirTreeView();

	// 初始化顶部框架
	initHeadFrame();

	// 初始化底部框架
	initFontFrame();

	// 初始化 Layout
	initLayout();
}

void DirGui::initDirModel()
{
	// 文件目录模型
	dirModel = new QFileSystemModel;
	dirModel->setReadOnly(true);	// 设置为只读
	dirModel->setRootPath("");
}

void DirGui::initDirTreeView()
{
	dirTreeView = new QTreeView;
	dirTreeView->setModel(dirModel);
	dirTreeView->header()->setStretchLastSection(true);
	dirTreeView->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);	// 自动变化大小
	connect(dirTreeView, &QTreeView::clicked, this, &DirGui::enableDetailsButton);
	dirTreeView->setSortingEnabled(true);
}

void DirGui::enableDetailsButton()
{
	detailsButton->setDisabled(false);
}

void DirGui::initHeadFrame()
{
	// 输入框
	dirEdit = new QLineEdit;
	dirEdit->setPlaceholderText("Please enter dir");
	connect(dirEdit, &QLineEdit::textChanged, this, &DirGui::onLineTextChangedToShowDir);

	detailsButton = new QPushButton;
	detailsButton->setText("Details");
	connect(detailsButton, &QPushButton::pressed, this, &DirGui::showDetails);
	detailsButton->setDisabled(true);
}

void DirGui::initFontFrame()
{
	// 展开按钮
	expandButton = new QPushButton;
	expandButton->setText("Expand (Ctrl+E)");
	// 将Ctrl+E设置会快捷键
	expandButton->setShortcut(QKeySequence(QApplication::translate("QtGuiApplication1Class", "Ctrl+E", Q_NULLPTR)));
	connect(expandButton, &QPushButton::pressed, this, &DirGui::expandDir);
	expandButton->setEnabled(false);

	// 折叠按钮
	collapseButton = new QPushButton;
	collapseButton->setText("Collapse (Ctrl+D)");
	// 将Ctrl+D设置会快捷键
	collapseButton->setShortcut(QKeySequence(QApplication::translate("QtGuiApplication1Class", "Ctrl+D", Q_NULLPTR)));
	connect(collapseButton, &QPushButton::pressed, this, &DirGui::collapseDir);
}

void DirGui::onLineTextChangedToShowDir()
{
	// 文字改变的时候，若是目录，直接跳转到该目录
	QModelIndex index = dirModel->index(QString(dirEdit->text()));
	if (!index.isValid())
	{
		if (QString(dirEdit->text()).isEmpty())
		{
			dirTreeView->setRootIndex(dirModel->index(dirModel->rootPath()));
			this->setWindowTitle(windowTitle);
		}
		expandButton->setEnabled(false);
	}
	else
	{
		dirTreeView->setRootIndex(index);
		this->setWindowTitle(QString(dirEdit->text()));

		expandButton->setEnabled(true);
	}
}

void DirGui::expandDir()
{
	dirTreeView->expandAll();
}

void DirGui::collapseDir()
{
	dirTreeView->collapseAll();
}

void DirGui::showDetails()
{
	QModelIndex index = dirTreeView->currentIndex();

	QString filePath = dirModel->filePath(index);
	quint64 fileSize = dirModel->size(index);
	int tmp = filePath.length() - filePath.lastIndexOf('/') - 1;
	QString fileName = tmp ? filePath.right(tmp) : filePath;

	DetailsDialog * dialog = new DetailsDialog(fileName, filePath, fileSize);
	dialog->show();
}

void DirGui::initLayout()
{
	// 设置 Layout
	QHBoxLayout * head = new QHBoxLayout;
	head->addWidget(dirEdit);
	head->addWidget(detailsButton);

	QHBoxLayout * foot = new QHBoxLayout;
	foot->addStretch();
	foot->addWidget(expandButton);
	foot->addWidget(collapseButton);

	QVBoxLayout * mainLayout = new QVBoxLayout;
	mainLayout->addLayout(head);
	mainLayout->addWidget(dirTreeView);
	mainLayout->addLayout(foot);

	setLayout(mainLayout);
}

