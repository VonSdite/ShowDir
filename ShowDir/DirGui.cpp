#include "DirGui.h"

// ��������
DirGui::~DirGui()
{
	delete dirModel;
	delete dirTreeView;
	delete dirEdit;
	delete confirmButton;
}

// ���캯��
DirGui::DirGui(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	resize(800, 500);							// ���ڴ�С 
	setWindowTitle("Show Dir");					// ���ڱ���
	setWindowIcon(QIcon("Resources/search.png"));

	// ��ʼ��Ŀ¼ģ��
	initDirModel();

	// ��ʼ��Ŀ¼���νṹ
	initDirTreeView();

	// ��ʼ��������
	initEditFrame();

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
	connect(dirTreeView, &QTreeView::clicked, this, &DirGui::onlineTreeViewClick);
}

void DirGui::onlineTreeViewClick()
{
	detailsButton->setDisabled(false);
}

void DirGui::initEditFrame()
{
	// �����
	dirEdit = new QLineEdit;
	dirEdit->setPlaceholderText("Please enter dir");
	connect(dirEdit, &QLineEdit::textChanged, this, &DirGui::collaspeTreeView);

	// ���Ұ�ť
	confirmButton = new QPushButton;
	confirmButton->setText("Search (Ctrl+E)");
	// ��Ctrl+1���û��ݼ�
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
	// ���� Layout
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