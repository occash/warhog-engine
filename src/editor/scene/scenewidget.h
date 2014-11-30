#ifndef SCENEWIDGET_H
#define SCENEWIDGET_H

#include <entityx/Entity.h>

#include <QWidget>

class QTreeView;
class SceneModel;

class SceneWidget : public QWidget
{
	Q_OBJECT
	
public:
	SceneWidget(entityx::EntityManager *manager,
		entityx::EventManager *events, 
		QWidget *parent = 0);

	void prepare();
	QModelIndex current() const;

signals:
	void pressed(const QModelIndex&);
	
private:
	QTreeView *_tree;
    SceneModel *_model;

};

#endif