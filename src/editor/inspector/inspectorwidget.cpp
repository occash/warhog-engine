#include "inspectorwidget.h"
#include "componentview.h"

#include <components/cameracomponent.h>
#include <components/lightcomponent.h>
#include <components/materialcomponent.h>
#include <components/meshfiltercomponent.h>
#include <components/scriptcomponent.h>
#include <components/transformcomponent.h>

#include <QVBoxLayout>
#include <QPushButton>
#include <QMenu>

template<class C>
bool checkComponent(entityx::Entity entity)
{
	auto ptr = entity.component<C>();
	bool result = ptr ? true : false;
	return result;
}

InspectorWidget::InspectorWidget(entityx::EntityManager *manager, QWidget *parent)
    : QWidget(parent),
    _layout(new QVBoxLayout(this)),
	_manager(manager)
{
    _layout->setContentsMargins(6, 6, 6, 6);

	_transformView = new ComponentView(TransformComponent::classApi(), this);
	_transformView->hide();
	_layout->addWidget(_transformView);

	_cameraView = new ComponentView(CameraComponent::classApi(), this);
	_cameraView->hide();
    _layout->addWidget(_cameraView);

	_addButton = new QPushButton(tr("Add component"), this);
	_layout->addWidget(_addButton);

    _layout->addStretch();
    setLayout(_layout);
}

InspectorWidget::~InspectorWidget()
{
}

void InspectorWidget::inspect(const QModelIndex &index)
{
	for (int i = 0; i < _layout->count(); ++i)
	{
		QWidget *view = _layout->itemAt(i)->widget();
		if (view)
			view->hide();
	}
	_addButton->show();

    int id = reinterpret_cast<int>(index.internalPointer());

    entityx::Entity entity(_manager, entityx::Entity::Id(id, 1));
    if (!entity.valid())
        return;

	if (checkComponent<TransformComponent>(entity))
	{
		entityx::ComponentHandle<TransformComponent> transform =
			entity.component<TransformComponent>();
		_transformView->inspect(transform.get());
		_transformView->show();
	}

    if (checkComponent<CameraComponent>(entity))
    {
		entityx::ComponentHandle<CameraComponent> camera =
            entity.component<CameraComponent>();
        _cameraView->inspect(camera.get());
		_cameraView->show();
    }
}

void InspectorWidget::showComponents(quint32 id, quint32 version)
{

}

void InspectorWidget::update()
{
	_transformView->update();
	_cameraView->update();
}

void InspectorWidget::installComponents(QMenu *menu)
{
	_addButton->setMenu(menu);
}
