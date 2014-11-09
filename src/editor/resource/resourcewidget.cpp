#include "resourcewidget.h"
#include "fileresourceio.h"
#include "resourcemodel.h"

#include "import/meshimporter.h"
#include "import/scriptimporter.h"
#include "import/textureimporter.h"

#include <resourcemanager.h>

#include <QFileInfo>
#include <QProgressDialog>
#include <QTreeView>
#include <QToolBar>
#include <QVBoxLayout>
#include <QApplication>
#include <QAction>
#include <QFileDialog>
#include <QStandardPaths>

ResourceWidget::ResourceWidget(QWidget *parent)
    : QWidget(parent),
	_io(std::make_shared<FileResourceIO>()),
	_toolbar(new QToolBar(this)),
	_progress(new QProgressDialog(this))
{
	_progress->setMinimum(0);
	_progress->setMaximum(100);

	_model = new ResourceModel(_io, this);

	_toolbar->setIconSize(QSize(16, 16));
	QAction *createGroup = _toolbar->addAction(
		QIcon(":/icons/folder"), tr("Create group"));
	QAction *importResource = _toolbar->addAction(
		QIcon(":/icons/computer"), tr("Import resource"));

	connect(createGroup, SIGNAL(triggered()), this, SLOT(createGroup()));
	connect(importResource, SIGNAL(triggered()), this, SLOT(importResource()));

	_view = new QTreeView(this);
	_view->setModel(_model);
	_view->setAcceptDrops(true);
	_view->setDefaultDropAction(Qt::MoveAction);
	_view->setDragDropMode(QAbstractItemView::DragDrop);
	_view->setDragDropOverwriteMode(false);
	_view->setDragEnabled(true);
	_view->setDropIndicatorShown(true);
	_view->setSelectionBehavior(QAbstractItemView::SelectItems);
	_view->setSelectionMode(QAbstractItemView::SingleSelection);
	_view->setAutoExpandDelay(400);
	_view->setHeaderHidden(true);

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->addWidget(_toolbar);
	layout->addWidget(_view);
	setLayout(layout);

	addImporter(new MeshImporter());
	addImporter(new ScriptImporter());
	addImporter(new TextureImporter());

    setAcceptDrops(true);

	setResourceFolder("");
}

ResourceWidget::~ResourceWidget()
{
	qDeleteAll(_importers);
}

void ResourceWidget::addImporter(Importer *importer)
{
	connect(importer, SIGNAL(progress(int)), this, SLOT(onProgress(int)));
	connect(importer, SIGNAL(info(QString)), this, SLOT(onInfo(QString)));
	connect(importer, SIGNAL(error(QString)), this, SLOT(onError(QString)));
	connect(importer, SIGNAL(success()), this, SLOT(onSuccess()));

	_model->addImporter(importer);
	_importers.append(importer);
}

void ResourceWidget::setResourceFolder(const QString& folder)
{
	_io->setBasePath(folder.toStdString());
	_model->changePath();
	_toolbar->setEnabled(!folder.isEmpty());
}

void ResourceWidget::createGroup()
{
	QModelIndex current = _view->currentIndex();
	_model->createGroup(current, "New group");
}

void ResourceWidget::importResource()
{
	QString defaultPath = QStandardPaths::writableLocation(
		QStandardPaths::DocumentsLocation);
	QString filter;
	foreach(Importer *importer, _importers)
	{
		QStringList suffixList;
		foreach(QString suffix, importer->suffixes())
			suffixList << QString("*." + suffix);

		QString name = importer->metaObject()->className();
		name = name.mid(0, name.indexOf("Importer"));
		QString f(name + " (%1)");
		f = f.arg(suffixList.join(" "));
		filter.append(f + ";;");
	}
	QString fileName = QFileDialog::getOpenFileName(this, tr("Import resource"),
		defaultPath, filter);
	_model->import(_view->currentIndex(), fileName);
}

void ResourceWidget::onProgress(int val)
{
	if (!_progress->isVisible())
		_progress->show();

	if (val < 0)
		_progress->setMaximum(0);
	else
		_progress->setMaximum(100);

	_progress->setValue(val);
	QApplication::processEvents();
}

void ResourceWidget::onInfo(QString e)
{

}

void ResourceWidget::onError(QString e)
{

}

void ResourceWidget::onSuccess()
{
	_progress->hide();
}
