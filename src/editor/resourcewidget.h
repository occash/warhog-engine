#ifndef RESOURCEWIDGET_H
#define RESOURCEWIDGET_H

#include <QtWidgets/QWidget>
#include <memory>
//#include "ui_resourcewidget.h"

class QAbstractItemModel;
class QTreeView;
class Importer;
class ResourceIO;
class ResourceManager;

class ResourceWidget : public QWidget
{
    Q_OBJECT

public:
    ResourceWidget(QWidget *parent = 0);
    ~ResourceWidget();

	void setResourceFolder(const QString& folder);
	void addImporter(Importer *importer);
    Importer *findImporter(const QString& ext) const;

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private:
    //Ui::ResourceWidgetClass ui;
    QList<Importer *> _importers;
	std::shared_ptr<ResourceIO> _io;
	std::shared_ptr<ResourceManager> _manager;
	QAbstractItemModel *_model;
	QTreeView *_view;

};

#endif // RESOURCEWIDGET_H
