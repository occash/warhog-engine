#ifndef COMPONENTVIEW_H
#define COMPONENTVIEW_H

#include <meta/api.h>
#include <meta/property.h>

#include <QWidget>

class PropertyEditor;

class QFormLayout;
class QVBoxLayout;
class QPushButton;

class ComponentView : public QWidget
{
    Q_OBJECT

public:
    ComponentView(const Api *api, QWidget *parent = 0);
    ~ComponentView();

    void inspect(Object *component);
    void update();

private slots:
    void toggleState(bool checked);

private:
    void insertProperty(int index, Property p);

private:
    QVBoxLayout *_layout;
    QFormLayout *_editorsLayout;
    QWidget *_container;
    QPushButton *_label;
    QVector<PropertyEditor *> _editors;

};

#endif // COMPONENTVIEW_H
