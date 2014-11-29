#ifndef INSPECTORWIDGET_H
#define INSPECTORWIDGET_H

#include <entityx/Entity.h>

#include <QWidget>
#include <QModelIndex>

class QVBoxLayout;
class ComponentView;

class InspectorWidget : public QWidget
{
    Q_OBJECT

public:
    InspectorWidget(entityx::EntityManager *manager, QWidget *parent = 0);
    ~InspectorWidget();

public slots:
    void inspect(const QModelIndex &index);

private:
    QVBoxLayout *_layout;
	ComponentView *_transformView;
	ComponentView *_cameraView;
	entityx::EntityManager *_manager;

private:
    void showComponents(quint32 id, quint32 version);	

};

#endif // INSPECTORWIDGET_H
