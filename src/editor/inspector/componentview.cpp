#include "componentview.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QLayoutItem>

ComponentView::ComponentView(const QString& name, QWidget *parent)
    : QWidget(parent),
    _label(new QPushButton(name, this))
{
    _layout = new QVBoxLayout(this);
    _layout->setContentsMargins(0, 0, 0, 0);
    _layout->setSpacing(0);

    _label->setFlat(true);
    _label->setCheckable(true);
    _label->setChecked(true);
    _layout->addWidget(_label);

    setLayout(_layout);
}

ComponentView::~ComponentView()
{

}

void ComponentView::inspectComponent(entityx::BaseComponent *component)
{

}

void ComponentView::setBody(QWidget *body)
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
}
