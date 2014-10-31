#include "scenewidget.h"
#include "scenemodel.h"

#include <QVBoxLayout>
#include <QTreeView>

SceneWidget::SceneWidget(QWidget *parent, Qt::WindowFlags f) :
	QWidget(parent, f)
{
	_tree = new QTreeView(this);
	_model = new SceneModel(this);
	_tree->setModel(_model);
	_tree->setHeaderHidden(true);

	connect(_tree, SIGNAL(pressed(const QModelIndex&)), 
		this, SIGNAL(pressed(const QModelIndex&)));
	
	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->addWidget(_tree);
	setLayout(layout);
}
