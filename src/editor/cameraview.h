#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H

#include "componentview.h"

class QVBoxLayout;
class PropertyView;

class CameraView : public ComponentView
{
    Q_OBJECT

public:
    CameraView(QWidget *parent = 0);
    ~CameraView();

	virtual void inspectComponent(entityx::BaseComponent *component);

private:
    QVBoxLayout *_layout;
    PropertyView *_fovView;
    PropertyView *_aspectView;
    PropertyView *_nearView;
    PropertyView *_farView;

};

#endif // CAMERAVIEW_H
