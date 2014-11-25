#ifndef PROPERTYEDITOR_H
#define PROPERTYEDITOR_H

#include <QWidget>
#include <meta/any.h>

class PropertyEditor : public QWidget
{
    Q_OBJECT

public:
    PropertyEditor(QWidget *parent = 0);
    ~PropertyEditor();

	virtual void setValue(Any value);

signals:
	void valueChanged(Any value);

};

#endif // PROPERTYEDITOR_H
