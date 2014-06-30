#ifndef RESOURCEWIDGET_H
#define RESOURCEWIDGET_H

#include <QtWidgets/QWidget>
//#include "ui_resourcewidget.h"

class Importer;
class QFileSystemModel;
class QTreeView;

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
	QFileSystemModel *_model;
	QTreeView *_view;

};

#endif // RESOURCEWIDGET_H
