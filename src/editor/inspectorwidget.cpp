#include "inspectorwidget.h"

#include <cameracomponent.h>
#include <lightcomponent.h>
#include <materialcomponent.h>
#include <meshfiltercomponent.h>
#include <renderercomponent.h>
#include <scriptcomponent.h>
#include <transformcomponent.h>

#include "cameraview.h"

#include <QVBoxLayout>
#include <tree.h>
#include <bitset>

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
        entityx::ptr<CameraComponent> camera = 
            entity.component<CameraComponent>();
        _cameraView->inspectComponent(camera);
    }

    std::bitset<entityx::MAX_COMPONENTS> componentMask = entity.component_mask();
    int scriptOffset = ScriptComponent::maxComponents();
}

void InspectorWidget::showComponents(entityx::Entity entity)
{

}
