#include "resourcewidget.h"
#include "meshimporter.h"
#include "scriptimporter.h"
#include "textureimporter.h"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>
#include <QFileInfo>
#include <QFileSystemModel>
#include <QTreeView>
#include <QVBoxLayout>

ResourceWidget::ResourceWidget(QWidget *parent)
    : QWidget(parent)
{
    //ui.setupUi(this);

	_model = new QFileSystemModel(this);
	_model->setNameFilterDisables(false);

	_view = new QTreeView(this);
	_view->setModel(_model);

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(_view);
	setLayout(layout);

	setResourceFolder("D:/third-party");
	addImporter(new MeshImporter());
	addImporter(new ScriptImporter());
	addImporter(new TextureImporter());

    setAcceptDrops(true);
}

ResourceWidget::~ResourceWidget()
{

}

void ResourceWidget::dragEnterEvent(QDragEnterEvent *event)
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
}

void ResourceWidget::addImporter(Importer *importer)
{
	if (!importer)
		return;

	_importers.append(importer);
	QStringList exts = importer->suffixes();
	QStringList filters = _model->nameFilters();
	foreach(const QString& ext, exts)
	{
		filters.append(QString("*.%1").arg(ext));
	}
	_model->setNameFilters(filters);
}

Importer *ResourceWidget::findImporter(const QString& ext) const
{
    foreach(Importer *importer, _importers)
    {
        QStringList suffixes = importer->suffixes();
        foreach(QString suffix, suffixes)
        {
            if (suffix == ext)
                return importer;
        }
    }

    return nullptr;
}

void ResourceWidget::setResourceFolder(const QString& folder)
{
	_model->setRootPath(folder);
	_view->setRootIndex(_model->index(_model->rootPath()));
}
