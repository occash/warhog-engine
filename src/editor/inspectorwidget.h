#ifndef INSPECTORWIDGET_H
#define INSPECTORWIDGET_H

#include <entityx/entityx.h>

#include <QWidget>
#include <QModelIndex>

class QVBoxLayout;
class CameraView;

template<class C>
bool checkComponent(entityx::Entity entity)
{
    auto ptr = entity.component<C>();
    bool result = ptr ? true : false;
    return result;
}

class InspectorWidget : public QWidget
{
    Q_OBJECT

public:
    InspectorWidget(QWidget *parent = 0);
    ~InspectorWidget();

public slots:
    void inspectEntity(const QModelIndex &index);

private:
    //typedef QMap<entityx::BaseComponent::Family, QWidget *> ViewerMap;

    QVBoxLayout *_layout;
    CameraView *_cameraView;
    //ViewerMap _viewers;

private:
    void showComponents(entityx::Entity entity);

};

#endif // INSPECTORWIDGET_H
