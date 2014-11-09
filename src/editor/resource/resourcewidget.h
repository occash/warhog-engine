#ifndef RESOURCEWIDGET_H
#define RESOURCEWIDGET_H

#include <QWidget>
#include <memory>

class QTreeView;
class QToolBar;
class QProgressDialog;

class ResourceModel;
class ResourceIO;
class ResourceManager;
class Importer;

class ResourceWidget : public QWidget
{
    Q_OBJECT

public:
    ResourceWidget(QWidget *parent = 0);
    ~ResourceWidget();

	void setResourceFolder(const QString& folder);
	void addImporter(Importer *importer);

private slots :
	void onProgress(int);
	void onInfo(QString e);
	void onError(QString e);
	void onSuccess();

private slots:
	void createGroup();
	void importResource();

private:
	std::shared_ptr<ResourceIO> _io;
	ResourceModel *_model;
	QList<Importer *> _importers;

	QTreeView *_view;
	QToolBar *_toolbar;
	QProgressDialog *_progress;

};

#endif // RESOURCEWIDGET_H
