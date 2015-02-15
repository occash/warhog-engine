#include "floateditor.h"

#include <QHBoxLayout>
#include <QDoubleSpinBox>

FloatEditor::FloatEditor(Property p, QWidget *parent)
    : PropertyEditor(p, parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    _spinBox = new QDoubleSpinBox(this);
    _spinBox->setMinimumWidth(100);
    _spinBox->setMinimum(0.0);
    _spinBox->setMaximum(1000.0);
    layout->addWidget(_spinBox);

    setLayout(layout);

    connect(_spinBox, SIGNAL(valueChanged(double)),
            this, SLOT(updateValue(double)));
}

FloatEditor::~FloatEditor()
{
}

void FloatEditor::update()
{
    if (!object())
        return;

    Any any = value();
    float value = any_cast<float>(any);
    _spinBox->setValue(value);
}

void FloatEditor::updateValue(double value)
{
    setValue(float(value));
}
