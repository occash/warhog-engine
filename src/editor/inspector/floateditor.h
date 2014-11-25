#ifndef FLOATVIEW_H
#define FLOATVIEW_H

#include "propertyeditor.h"

class QDoubleSpinBox;

class FloatEditor : public PropertyEditor
{
    Q_OBJECT

public:
    FloatEditor(QWidget *parent = 0);
    ~FloatEditor();

	void setValue(Any value);

private slots:
    void handleValueChange(double d);

private:
    QDoubleSpinBox *_spinBox;

};

#endif // FLOATVIEW_H
