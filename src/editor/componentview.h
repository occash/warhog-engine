#ifndef COMPONENTVIEW_H
#define COMPONENTVIEW_H

#include <entityx/entityx.h>

#include <QWidget>
#include <glm/glm.hpp>
#include <memory>

class QVBoxLayout;
class QPushButton;

class ComponentView : public QWidget
{
    Q_OBJECT

public:
    ComponentView(const QString& name, QWidget *parent = 0);
    ~ComponentView();

    /*static ComponentView *find(entityx::BaseComponent::Family family);
    static void registerView(ComponentView *view);*/

    void setBody(QWidget *body);

    virtual void inspectComponent(entityx::BaseComponent *component);

private:
    QVBoxLayout *_layout;
    QPushButton *_label;
    //static QMap<entityx::BaseComponent::Family, entityx::ptr<entityx::BaseComponent> >componentMap;

};

#endif // COMPONENTVIEW_H
