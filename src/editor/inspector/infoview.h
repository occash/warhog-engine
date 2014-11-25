#ifndef INFOVIEW_H
#define INFOVIEW_H

#include "componentview.h"

class QLineEdit;

class InfoView : public ComponentView
{
public:
	InfoView(QWidget *parent = 0);

	void inspect(entityx::BaseComponent *component) override;

private slots:
	void changeName(const QString& name);

private:
	QLineEdit *_nameEdit;
	entityx::BaseComponent *_info;
};

#endif