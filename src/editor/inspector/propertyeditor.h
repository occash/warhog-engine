#ifndef PROPERTYEDITOR_H
#define PROPERTYEDITOR_H

#include <QWidget>
#include <meta/any.h>
#include <meta/property.h>

class PropertyEditor : public QWidget
{
    Q_OBJECT

public:
    PropertyEditor(Property p, QWidget *parent = 0);
    ~PropertyEditor();

    Object *object() const;
    void setObject(Object *object);

    Property property() const;
    void setProperty(Property property);

    Any value() const;
    void setValue(Any value);

    virtual void update() = 0;

private:
    Object *_object;
    Property _property;

};

#endif // PROPERTYEDITOR_H
