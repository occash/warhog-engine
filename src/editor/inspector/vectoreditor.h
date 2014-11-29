#ifndef VECTOREDITOR_H
#define VECTOREDITOR_H

#include "propertyeditor.h"

class QDoubleSpinBox;

class VectorEditor : public PropertyEditor
{
	Q_OBJECT

public:
	VectorEditor(Property p, QWidget *parent = 0);
	~VectorEditor();

	void update() override;

private slots:
	void updateX(double value);
	void updateY(double value);
	void updateZ(double value);

private:
	QDoubleSpinBox *_spinBoxX;
	QDoubleSpinBox *_spinBoxY;
	QDoubleSpinBox *_spinBoxZ;
};

#endif