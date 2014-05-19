#include "floateditor.h"

#include <QHBoxLayout>
#include <QDoubleSpinBox>
#include <glm/glm.hpp>
#include <iostream>

FloatEditor::FloatEditor(QWidget *parent)
    : PropertyEditor(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    _spinBox = new QDoubleSpinBox(this);
    _spinBox->setMinimumWidth(100);
    layout->addWidget(_spinBox);

    setLayout(layout);

    connect(_spinBox, SIGNAL(valueChanged(double)), this, SLOT(handleValueChange(double)));
}

FloatEditor::~FloatEditor()
{

}

void FloatEditor::setValue(boost::any val)
{
    glm::float_t v;
    try
    {
        v = boost::any_cast<glm::float_t>(val);
    }
    catch (boost::bad_any_cast bac)
    {
        std::cout << "Cast error: " << bac.what() << std::endl;
        return;
    }

    _spinBox->setValue(v);
}

void FloatEditor::handleValueChange(double d)
{
    emit valueChanged(boost::any((glm::float_t)d));
}
