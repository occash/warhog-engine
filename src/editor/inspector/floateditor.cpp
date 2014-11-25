#include "floateditor.h"

#include <QHBoxLayout>
#include <QDoubleSpinBox>

FloatEditor::FloatEditor(QWidget *parent)
    : PropertyEditor(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    _spinBox = new QDoubleSpinBox(this);
    _spinBox->setMinimumWidth(100);
    layout->addWidget(_spinBox);

    setLayout(layout);

    connect(_spinBox, SIGNAL(valueChanged(double)), 
		this, SLOT(handleValueChange(double)));
}

FloatEditor::~FloatEditor()
{

}

void FloatEditor::setValue(Any value)
{
	float f = any_cast<float>(value);
    _spinBox->setValue(f);
}

void FloatEditor::handleValueChange(double d)
{
    emit valueChanged(Any(float(d)));
}
