#include "cameraview.h"
#include "propertyview.h"
#include "floateditor.h"

#include <components/cameracomponent.h>
#include <QVBoxLayout>

CameraView::CameraView(QWidget *parent)
    : ComponentView("Camera", parent)
{
    QWidget *body = new QWidget();
    _layout = new QVBoxLayout(body);
    _layout->setContentsMargins(0, 0, 0, 0);
    _layout->setSpacing(6);

    _fovView = new PropertyView("Field of View", new FloatEditor(), this);
    _layout->addWidget(_fovView);

    _aspectView = new PropertyView("Aspect", new FloatEditor(), this);
    _layout->addWidget(_aspectView);

    _nearView = new PropertyView("Near Plane", new FloatEditor(), this);
    _layout->addWidget(_nearView);

    _farView = new PropertyView("Far Plane", new FloatEditor(), this);
    _layout->addWidget(_farView);

    body->setLayout(_layout);
    setBody(body);
}

CameraView::~CameraView()
{

}

void CameraView::inspect(entityx::BaseComponent *component)
{
	CameraComponent *camera = static_cast<CameraComponent *>(component);

    _fovView->setValue(camera->fieldOfView());
    _aspectView->setValue(camera->aspect());
    _nearView->setValue(camera->nearPlane());
    _farView->setValue(camera->farPlane());
}
