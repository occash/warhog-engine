#ifndef ENUMERATIONVIEW_H
#define ENUMERATIONVIEW_H

#include "propertyeditor.h"

class EnumerationEditor : public PropertyEditor
{
    Q_OBJECT

public:
    EnumerationEditor(QWidget *parent = 0);
    ~EnumerationEditor();

    void setValue(boost::any val);

};

#endif // ENUMERATIONVIEW_H
