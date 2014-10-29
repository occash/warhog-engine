#ifndef PROPERTYEDITOR_H
#define PROPERTYEDITOR_H

#include <QWidget>

#include <boost/any.hpp>

class PropertyEditor : public QWidget
{
    Q_OBJECT

public:
    PropertyEditor(QWidget *parent = 0);
    ~PropertyEditor();

    virtual void setValue(boost::any val);

signals:
    void valueChanged(boost::any val);

};

#endif // PROPERTYEDITOR_H
