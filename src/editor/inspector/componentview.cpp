#include "componentview.h"
#include "floateditor.h"
#include "vectoreditor.h"

#include <glm/glm.hpp>

#include <QPushButton>
#include <QFormLayout>
#include <QLayoutItem>
#include <QRegularExpression>

ComponentView::ComponentView(const Api *api, QWidget *parent)
    : QWidget(parent)
    //_label(new QPushButton(name, this))
{
	_layout = new QFormLayout(this);
    _layout->setContentsMargins(0, 0, 0, 0);
    _layout->setSpacing(3);

    /*_label->setFlat(true);
    _label->setCheckable(true);
    _label->setChecked(true);
    _layout->addWidget(_label);*/

	_editors.resize(api->propertyCount());
	for (int i = 0; i < api->propertyCount(); ++i)
		insertProperty(i, api->property(i));

    setLayout(_layout);
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

	_layout->addRow(editorName, editor);
	_editors[index] = editor;
}

void ComponentView::inspect(Object *component)
{
	for (int i = 0; i < _layout->rowCount(); ++i)
	{
		_editors.at(i)->setObject(component);
		_editors.at(i)->update();
	}
}

/*void ComponentView::setBody(QWidget *body)
{
    QLayoutItem *item = _layout->itemAt(1);
    if (item)
    {
        item->widget()->hide();
        item->widget()->setParent(nullptr);
        _layout->removeItem(item);
        item->widget()->deleteLater();
    }
        
    body->setParent(this);
    connect(_label, SIGNAL(clicked(bool)), body, SLOT(setVisible(bool)));
    _layout->addWidget(body);
}*/
