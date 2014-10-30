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
	SceneWidget(QWidget *parent = 0, Qt::WindowFlags f = 0);
	
private:
	QTreeView *_tree;
    SceneModel *_model;

};

#endif