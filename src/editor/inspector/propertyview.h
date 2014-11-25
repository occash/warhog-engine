#ifndef PROPERTYVIEW_H
#define PROPERTYVIEW_H

#include <QWidget>
#include <meta/any.h>

class PropertyEditor;

class PropertyView : public QWidget
{
    Q_OBJECT

public:
    PropertyView(const QString& name, PropertyEditor *editor, QWidget *parent = 0);
    ~PropertyView();

    void setValue(Any value);
    //void setEditor(PropertyEditor *editor);

signals:
	void valueChanged(Any value);

private:
    PropertyEditor *_editor;

};

#endif // PROPERTYVIEW_H
