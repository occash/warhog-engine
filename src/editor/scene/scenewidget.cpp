#include "scenewidget.h"
#include "scenemodel.h"

#include <QVBoxLayout>
#include <QTreeView>

SceneWidget::SceneWidget(entityx::EntityManager *manager, 
	entityx::EventManager *events, QWidget *parent) :
	QWidget(parent)
{
	_tree = new QTreeView(this);
	_model = new SceneModel(manager, events, this);
	_tree->setModel(_model);
	_tree->setHeaderHidden(true);

	connect(_tree, SIGNAL(pressed(const QModelIndex&)), 
		this, SIGNAL(pressed(const QModelIndex&)));
	
	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->addWidget(_tree);
	setLayout(layout);
}

void SceneWidget::prepare()
{
	_model->prepare();
}
