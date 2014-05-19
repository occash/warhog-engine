#include "propertyview.h"
#include "propertyeditor.h"

#include <QHBoxLayout>
#include <QLabel>

PropertyView::PropertyView(const QString& name, PropertyEditor *editor, QWidget *parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(6, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(new QLabel(name, this));
    layout->addStretch();

    _editor = editor;
    _editor->setParent(this);
    layout->addWidget(_editor);
    connect(_editor, SIGNAL(valueChanged(boost::any)), this, SIGNAL(valueChanged(boost::any)));

    setLayout(layout);
}

PropertyView::~PropertyView()
{

}

void PropertyView::setValue(boost::any val)
{
    _editor->setValue(val);
}
