#include "DirGui.h"

// ��������
DirGui::~DirGui()
{
	delete dirModel;
	delete dirTreeView;
	delete dirEdit;
	delete expandButton;
	delete collapseButton;
	delete detailsButton;
}

// ���캯��
DirGui::DirGui(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	windowTitle = "Show Dir";
	resize(800, 500);							// ���ڴ�С 
	setWindowTitle(windowTitle);				// ���ڱ���
	setWindowIcon(QIcon("Resources/search.png"));

	// ��ʼ��Ŀ¼ģ��
	initDirModel();

	// ��ʼ��Ŀ¼���νṹ
	initDirTreeView();

	// ��ʼ���������
	initHeadFrame();

	// ��ʼ���ײ����
	initFontFrame();

	// ��ʼ�� Layout
	initLayout();
}

void DirGui::initDirModel()
{
	// �ļ�Ŀ¼ģ��
	dirModel = new QFileSystemModel;
	dirModel->setReadOnly(true);	// ����Ϊֻ��
	dirModel->setRootPath("");
}

void DirGui::initDirTreeView()
{
	dirTreeView = new QTreeView;
	dirTreeView->setModel(dirModel);
	dirTreeView->header()->setStretchLastSection(true);
	dirTreeView->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);	// �Զ��仯��С
	connect(dirTreeView, &QTreeView::clicked, this, &DirGui::enableDetailsButton);
	dirTreeView->setSortingEnabled(true);
}

void DirGui::enableDetailsButton()
{
	detailsButton->setDisabled(false);
}

void DirGui::initHeadFrame()
{
	// �����
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
	// չ����ť
	expandButton = new QPushButton;
	expandButton->setText("Expand (Ctrl+E)");
	// ��Ctrl+E���û��ݼ�
	expandButton->setShortcut(QKeySequence(QApplication::translate("QtGuiApplication1Class", "Ctrl+E", Q_NULLPTR)));
	connect(expandButton, &QPushButton::pressed, this, &DirGui::expandDir);
	expandButton->setEnabled(false);

	// �۵���ť
	collapseButton = new QPushButton;
	collapseButton->setText("Collapse (Ctrl+D)");
	// ��Ctrl+D���û��ݼ�
	collapseButton->setShortcut(QKeySequence(QApplication::translate("QtGuiApplication1Class", "Ctrl+D", Q_NULLPTR)));
	connect(collapseButton, &QPushButton::pressed, this, &DirGui::collapseDir);
}

void DirGui::onLineTextChangedToShowDir()
{
	// ���ָı��ʱ������Ŀ¼��ֱ����ת����Ŀ¼
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
	// ���� Layout
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

