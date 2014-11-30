#include "componentview.h"
#include "floateditor.h"
#include "vectoreditor.h"

#include <glm/glm.hpp>

#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QLayoutItem>
#include <QRegularExpression>

ComponentView::ComponentView(const Api *api, QWidget *parent)
    : QWidget(parent),
    _label(nullptr)
{
	_layout = new QVBoxLayout(this);
	_layout->setContentsMargins(0, 0, 0, 0);
	setLayout(_layout);

	//Create header
	_label = new QPushButton(QString(api->name()), this);
	_label->setFlat(true);
	_label->setCheckable(true);
	_label->setChecked(true);
	_layout->addWidget(_label);
	connect(_label, SIGNAL(toggled(bool)),
		this, SLOT(toggleState(bool)));

	//Create editors
	_container = new QWidget(this);
	_editorsLayout = new QFormLayout(this);
	_editorsLayout->setContentsMargins(0, 0, 0, 0);
	_editorsLayout->setSpacing(3);
	_container->setLayout(_editorsLayout);
	_layout->addWidget(_container);

	//Fill property editors
	_editors.resize(api->propertyCount());
	for (int i = 0; i < api->propertyCount(); ++i)
		insertProperty(i, api->property(i));
}

ComponentView::~ComponentView()
{
}

void ComponentView::insertProperty(int index, Property p)
{
	// TODO Find proper editor
	PropertyEditor *editor = nullptr;
	if (p.type().id() == typeid(float))
		editor = new FloatEditor(p, this);
	if (p.type().id() == typeid(glm::vec3))
		editor = new VectorEditor(p, this);

	if (!editor)
		return;
	
	QString propName(p.name());
	QString editorName;
	int firstChar = 0;
	for (int i = 0; i < propName.size(); ++i)
	{
		if (propName.at(i).isUpper())
		{
			QString name = propName.mid(firstChar, i - firstChar);
			editorName.append(name);
			editorName.append(" ");
			firstChar = i;
		}
	}
	QString lastChars = propName.mid(firstChar, propName.size() - firstChar);
	editorName.append(lastChars);
	editorName[0] = editorName.at(0).toUpper();

	_editorsLayout->addRow(editorName, editor);
	_editors[index] = editor;
}

void ComponentView::inspect(Object *component)
{
	for (int i = 0; i < _editorsLayout->rowCount(); ++i)
	{
		_editors.at(i)->setObject(component);
		_editors.at(i)->update();
	}
}

void ComponentView::update()
{
	foreach(PropertyEditor *editor, _editors)
		editor->update();
}

void ComponentView::toggleState(bool checked)
{
	_container->setVisible(checked);
}
