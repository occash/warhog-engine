#ifndef RESOURCEWIDGET_H
#define RESOURCEWIDGET_H

#include <QtWidgets/QWidget>
#include <memory>
//#include "ui_resourcewidget.h"

class ResourceModel;
class QTreeView;
class Importer;
class ResourceIO;
class ResourceManager;
class QProgressBar;

class ResourceWidget : public QWidget
{
    Q_OBJECT

public:
    ResourceWidget(QWidget *parent = 0);
    ~ResourceWidget();

	void setResourceFolder(const QString& folder);
	void addImporter(Importer *importer);

protected:
    //void dragEnterEvent(QDragEnterEvent *event);
    //void dropEvent(QDropEvent *event);

private slots :
	void onProgress(int);
	void onInfo(QString e);
	void onError(QString e);
	void onSuccess();

private:
    //Ui::ResourceWidgetClass ui;
	std::shared_ptr<ResourceIO> _io;
	std::shared_ptr<ResourceManager> _manager;
	ResourceModel *_model;
	QTreeView *_view;
	QProgressBar *_progress;

};

#endif // RESOURCEWIDGET_H
