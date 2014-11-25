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
	connect(_fovView, SIGNAL(valueChanged(Any)), this, SLOT(fovChanged(Any)));

    _aspectView = new PropertyView("Aspect", new FloatEditor(), this);
    _layout->addWidget(_aspectView);
	connect(_aspectView, SIGNAL(valueChanged(Any)), this, SLOT(aspectChanged(Any)));

    _nearView = new PropertyView("Near Plane", new FloatEditor(), this);
    _layout->addWidget(_nearView);
	connect(_nearView, SIGNAL(valueChanged(Any)), this, SLOT(nearChanged(Any)));

    _farView = new PropertyView("Far Plane", new FloatEditor(), this);
    _layout->addWidget(_farView);
	connect(_farView, SIGNAL(valueChanged(Any)), this, SLOT(farChanged(Any)));

    body->setLayout(_layout);
    setBody(body);
}

CameraView::~CameraView()
{

}

void CameraView::inspect(entityx::BaseComponent *component)
{
	_camera = static_cast<CameraComponent *>(component);
	if (!_camera)
		return;

	_fovView->setValue(_camera->fieldOfView());
	_aspectView->setValue(_camera->aspect());
	_nearView->setValue(_camera->nearPlane());
	_farView->setValue(_camera->farPlane());
}

void CameraView::fovChanged(Any value)
{
	if (_camera)
		_camera->setFieldOfView(any_cast<float>(value));
}

void CameraView::aspectChanged(Any value)
{
	if (_camera)
		_camera->setAspect(any_cast<float>(value));
}

void CameraView::nearChanged(Any value)
{
	if (_camera)
		_camera->setNearPlane(any_cast<float>(value));
}

void CameraView::farChanged(Any value)
{
	if (_camera)
		_camera->setFarPlane(any_cast<float>(value));
}
