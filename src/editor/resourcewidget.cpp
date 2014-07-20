#include "resourcewidget.h"
#include "meshimporter.h"
#include "scriptimporter.h"
#include "textureimporter.h"
#include "fileresourceio.h"
#include "resourcemodel.h"

#include <resourcemanager.h>

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>
#include <QFileInfo>
#include <QFileSystemModel>
#include <QTreeView>
#include <QVBoxLayout>

ResourceWidget::ResourceWidget(QWidget *parent)
    : QWidget(parent),
	_io(std::make_shared<FileResourceIO>()),
	_manager(std::make_shared<ResourceManager>(_io))
{
    //ui.setupUi(this);

	setResourceFolder("D:/projects/warhog-engine/test/project1/resources");
	_model = new ResourceModel(_io, this);

	_view = new QTreeView(this);
	_view->setModel(_model);
	_view->setAcceptDrops(true);
	_view->setDefaultDropAction(Qt::CopyAction);
	_view->setDragDropMode(QAbstractItemView::DragDrop);
	_view->setDragDropOverwriteMode(false);
	_view->setDragEnabled(true);
	_view->setDropIndicatorShown(true);
	_view->setSelectionBehavior(QAbstractItemView::SelectItems);
	_view->setSelectionMode(QAbstractItemView::SingleSelection);
	//_view->setAnimated(true);
	_view->setAutoExpandDelay(400);
	_view->setHeaderHidden(true);

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->addWidget(_view);
	setLayout(layout);

	addImporter(new MeshImporter());
	addImporter(new ScriptImporter());
	addImporter(new TextureImporter());

    setAcceptDrops(true);
}

ResourceWidget::~ResourceWidget()
{
}

/*void ResourceWidget::dragEnterEvent(QDragEnterEvent *event)
{
	const QMimeData *data = event->mimeData();
	if (data->hasUrls())
	{
		QList<QUrl> urls = data->urls();
		for each (QUrl url in urls)
		{
			if (url.isValid() && url.isLocalFile())
			{
				QString fileName = url.toLocalFile();
				QFileInfo fileInfo(fileName);
				if (fileInfo.isFile())
				{
					QString extension = fileInfo.suffix();
					foreach (Importer *importer, _importers)
					{
						if (importer->suffixes().contains(extension))
						{
							event->acceptProposedAction();
							return;
						}
					}
				}
			}
		}
	}
}

void ResourceWidget::dropEvent(QDropEvent *event)
{
    const QMimeData *data = event->mimeData();
    if (data->hasUrls())
    {
        QList<QUrl> urls = data->urls();
        for each (QUrl url in urls)
        {
            if (url.isValid() && url.isLocalFile())
            {
                QString fileName = url.toLocalFile();
                QFileInfo fileInfo(fileName);
                if (fileInfo.isFile())
                {
                    QString extension = fileInfo.suffix();
                    Importer *importer = findImporter(extension);
                    if (importer)
                        importer->import(fileName);
                }
            }
        }
    }
}*/

void ResourceWidget::addImporter(Importer *importer)
{
	_model->addImporter(importer);
}

void ResourceWidget::setResourceFolder(const QString& folder)
{
	_manager->setBasePath(folder.toStdString());
	//_model->setRootPath(folder);
	//_view->setRootIndex(_model->index(_model->rootPath()));
}
