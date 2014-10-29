#ifndef PROPERTYVIEW_H
#define PROPERTYVIEW_H

#include <QWidget>

#include <glm/glm.hpp>
#include <boost/any.hpp>

class PropertyEditor;

class PropertyView : public QWidget
{
    Q_OBJECT

public:
    PropertyView(const QString& name, PropertyEditor *editor, QWidget *parent = 0);
    ~PropertyView();

    void setValue(boost::any val);
    //void setEditor(PropertyEditor *editor);

signals:
    void valueChanged(boost::any val);

private:
    PropertyEditor *_editor;

};

#endif // PROPERTYVIEW_H
