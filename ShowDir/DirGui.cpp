#include "DirGui.h"

// 析构函数
DirGui::~DirGui()
{
	delete dirModel;
	delete dirTreeView;
	delete dirEdit;
	delete confirmButton;
}

// 构造函数
DirGui::DirGui(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	resize(800, 500);							// 窗口大小 
	setWindowTitle("Show Dir");					// 窗口标题
	setWindowIcon(QIcon("Resources/search.png"));

	// 初始化目录模型
	initDirModel();

	// 初始化目录树形结构
	initDirTreeView();

	// 初始化输入框架
	initEditFrame();

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
	connect(dirTreeView, &QTreeView::clicked, this, &DirGui::onlineTreeViewClick);
}

void DirGui::onlineTreeViewClick()
{
	detailsButton->setDisabled(false);
}

void DirGui::initEditFrame()
{
	// 输入框
	dirEdit = new QLineEdit;
	dirEdit->setPlaceholderText("Please enter dir");
	connect(dirEdit, &QLineEdit::textChanged, this, &DirGui::collaspeTreeView);

	// 查找按钮
	confirmButton = new QPushButton;
	confirmButton->setText("Search (Ctrl+E)");
	// 将Ctrl+1设置会快捷键
	confirmButton->setShortcut(QKeySequence(QApplication::translate("QtGuiApplication1Class", "Ctrl+E", Q_NULLPTR)));	
	connect(confirmButton, &QPushButton::pressed, this, &DirGui::showDir);

	detailsButton = new QPushButton;
	detailsButton->setText("Details");
	connect(detailsButton, &QPushButton::pressed, this, &DirGui::showDetails);
	detailsButton->setDisabled(true);
}

void DirGui::collaspeTreeView()
{
	dirTreeView->collapseAll();
}

void DirGui::initLayout()
{
	// 设置 Layout
	QHBoxLayout * searchBox = new QHBoxLayout;
	searchBox->addWidget(dirEdit);
	searchBox->addWidget(confirmButton);
	searchBox->addWidget(detailsButton);

	QVBoxLayout * mainLayout = new QVBoxLayout;
	mainLayout->addLayout(searchBox);
	mainLayout->addWidget(dirTreeView);

	setLayout(mainLayout);
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

void DirGui::showDir()
{
	QModelIndex index = dirModel->index(QString(dirEdit->text()));
	if (!index.isValid())
	{
		if (QString(dirEdit->text()).isEmpty())
		{
			dirTreeView->setRootIndex(dirModel->index(dirModel->rootPath()));
			this->setWindowTitle(QString("root:/"));
		}
		else
		{
			QMessageBox * box = new QMessageBox(QMessageBox::Warning,
				QString("Warning"),
				dirEdit->text() + " not found",
				QMessageBox::Ok);
			box->show();
		}
		return;
	}
	dirTreeView->setRootIndex(index);
	dirTreeView->expandAll();
	this->setWindowTitle(QString(dirEdit->text()));
}