#include "inspectorwidget.h"
#include "cameraview.h"

#include <components/cameracomponent.h>
#include <components/lightcomponent.h>
#include <components/materialcomponent.h>
#include <components/meshfiltercomponent.h>
#include <components/scriptcomponent.h>
#include <components/transformcomponent.h>

#include <QVBoxLayout>

template<class C>
bool checkComponent(entityx::Entity entity)
{
	auto ptr = entity.component<C>();
	bool result = ptr ? true : false;
	return result;
}

InspectorWidget::InspectorWidget(QWidget *parent)
    : QWidget(parent),
    _layout(new QVBoxLayout(this))
{
    _layout->setContentsMargins(0, 0, 0, 0);

    _cameraView = new CameraView(this);
    _layout->addWidget(_cameraView);

    _layout->addStretch();
    setLayout(_layout);
}

InspectorWidget::~InspectorWidget()
{

}

void InspectorWidget::inspectEntity(const QModelIndex &index)
{
    tree_node_<entityx::Entity> *node =
        static_cast<tree_node_<entityx::Entity> *>(index.internalPointer());
    if (!node)
        return;

    entityx::Entity entity = node->data;
    if (!entity.valid())
        return;

    if (checkComponent<CameraComponent>(entity))
    {
		entityx::ComponentHandle<CameraComponent> camera =
            entity.component<CameraComponent>();
        _cameraView->inspectComponent(camera.get());
    }
}

void InspectorWidget::showComponents(quint32 id, quint32 version)
{

}
