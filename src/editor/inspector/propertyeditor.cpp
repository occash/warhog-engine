#include "propertyeditor.h"

PropertyEditor::PropertyEditor(Property p, QWidget *parent)
    : QWidget(parent),
	_property(p),
	_object(nullptr)
{
}

PropertyEditor::~PropertyEditor()
{
}

Object *PropertyEditor::object() const
{
	return _object;
}

void PropertyEditor::setObject(Object *object)
{
	_object = object;
}

Property PropertyEditor::property() const
{
	return _property;
}

void PropertyEditor::setProperty(Property property)
{
	_property = property;
}

Any PropertyEditor::value() const
{
	if (_object)
		return _property.read(_object);
}

void PropertyEditor::setValue(Any value)
{
	if (_object)
		_property.write(_object, value);
}
