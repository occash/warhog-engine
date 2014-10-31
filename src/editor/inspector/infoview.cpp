#include "infoview.h"

#include <components/infocomponent.h>

#include <QHBoxLayout>
#include <QLineEdit>

InfoView::InfoView(QWidget *parent) :
	ComponentView("Info", parent)
{
	QHBoxLayout *layout = new QHBoxLayout(this);

	QLineEdit *nameEdit = new QLineEdit(this);
	layout->addWidget(nameEdit);

	setLayout(layout);
}

void InfoView::changeName(const QString& name)
{
	
}

void InfoView::inspect(entityx::BaseComponent *component)
{

}
