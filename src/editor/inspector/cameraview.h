#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H

#include "componentview.h"
#include <meta/any.h>

class QVBoxLayout;
class PropertyView;
class CameraComponent;

class CameraView : public ComponentView
{
    Q_OBJECT

public:
    CameraView(QWidget *parent = 0);
    ~CameraView();

	void inspect(entityx::BaseComponent *component) override;

private slots:
	void fovChanged(Any value);
	void aspectChanged(Any value);
	void nearChanged(Any value);
	void farChanged(Any value);

private:
	CameraComponent *_camera;
    QVBoxLayout *_layout;
    PropertyView *_fovView;
    PropertyView *_aspectView;
    PropertyView *_nearView;
    PropertyView *_farView;

};

#endif // CAMERAVIEW_H
