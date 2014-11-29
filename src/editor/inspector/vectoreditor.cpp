#include "vectoreditor.h"

#include <glm/glm.hpp>

#include <QHBoxLayout>
#include <QDoubleSpinBox>

VectorEditor::VectorEditor(Property p, QWidget *parent)
	: PropertyEditor(p, parent)
{
	QHBoxLayout *layout = new QHBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);

	_spinBoxX = new QDoubleSpinBox(this);
	_spinBoxX->setMinimumWidth(30);
	_spinBoxX->setMinimum(-1000.0);
	_spinBoxX->setMaximum(1000.0);
	layout->addWidget(_spinBoxX);

	_spinBoxY = new QDoubleSpinBox(this);
	_spinBoxY->setMinimumWidth(30);
	_spinBoxY->setMinimum(-1000.0);
	_spinBoxY->setMaximum(1000.0);
	layout->addWidget(_spinBoxY);

	_spinBoxZ = new QDoubleSpinBox(this);
	_spinBoxZ->setMinimumWidth(30);
	_spinBoxZ->setMinimum(-1000.0);
	_spinBoxZ->setMaximum(1000.0);
	layout->addWidget(_spinBoxZ);

	setLayout(layout);

	connect(_spinBoxX, SIGNAL(valueChanged(double)),
		this, SLOT(updateX(double)));
	connect(_spinBoxY, SIGNAL(valueChanged(double)),
		this, SLOT(updateY(double)));
	connect(_spinBoxZ, SIGNAL(valueChanged(double)),
		this, SLOT(updateZ(double)));
}

VectorEditor::~VectorEditor()
{

}

void VectorEditor::update()
{
	Any any = value();
	glm::vec3 value = any_cast<glm::vec3>(any);
	_spinBoxX->setValue(value.x);
	_spinBoxY->setValue(value.y);
	_spinBoxZ->setValue(value.z);
}

void VectorEditor::updateX(double val)
{
	Any any = value();
	glm::vec3 value = any_cast<glm::vec3>(any);
	value.x = val;
	setValue(value);
}

void VectorEditor::updateY(double val)
{
	Any any = value();
	glm::vec3 value = any_cast<glm::vec3>(any);
	value.y = val;
	setValue(value);
}

void VectorEditor::updateZ(double val)
{
	Any any = value();
	glm::vec3 value = any_cast<glm::vec3>(any);
	value.z = val;
	setValue(value);
}
