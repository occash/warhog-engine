#ifndef FLOATVIEW_H
#define FLOATVIEW_H

#include "propertyeditor.h"

class QDoubleSpinBox;

class FloatEditor : public PropertyEditor
{
    Q_OBJECT

public:
    FloatEditor(Property p, QWidget *parent = 0);
    ~FloatEditor();

	void update() override;

private slots:
	void updateValue(double value);

private:
    QDoubleSpinBox *_spinBox;

};

#endif // FLOATVIEW_H
