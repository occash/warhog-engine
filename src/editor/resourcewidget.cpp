#include "resourcewidget.h"
#include "meshimporter.h"
#include "scriptimporter.h"
#include "textureimporter.h"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>
#include <QFileInfo>

ResourceWidget::ResourceWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    _importers.append(new MeshImporter());
    _importers.append(new ScriptImporter());
    _importers.append(new TextureImporter());

    setAcceptDrops(true);
}

ResourceWidget::~ResourceWidget()
{

}

void ResourceWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
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

Importer *ResourceWidget::findImporter(const QString& ext)
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
