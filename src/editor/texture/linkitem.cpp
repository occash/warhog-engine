#include "linkitem.h"
#include "connectoritem.h"

#include <QPen>
#include <QBrush>

LinkItem::LinkItem(BaseModule *linkModule, QGraphicsItem *parent)
    : QGraphicsRectItem(parent),
      _module(linkModule),
      _connector(nullptr)
{
    setPen(QPen(QColor(200, 200, 200)));
}

LinkItem::~LinkItem()
{

}

void LinkItem::updateConnection()
{
    if (_connector)
        _connector->updateGeometry();
}

SourceItem::SourceItem(BaseModule *module, int id, QGraphicsItem *parent)
    : LinkItem(module, parent),
      _id(id)
{
    setBrush(QBrush(QColor(0, 180, 250)));
}

SourceItem::~SourceItem()
{
}

OutputItem::OutputItem(BaseModule *module, QGraphicsItem *parent)
    : LinkItem(module, parent)
{
    setBrush(QBrush(QColor(0, 250, 180)));
}

OutputItem::~OutputItem()
{
}
