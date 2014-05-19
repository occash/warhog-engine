#include "connectoritem.h"
#include "basemodule.h"
#include "linkitem.h"
#include "moduleitem.h"

#include <QPen>

ConnectorItem::ConnectorItem(OutputItem *output, SourceItem *source)
: QGraphicsLineItem(),
_output(output),
_source(source)
{
    setPen(QPen(QColor(200, 200, 200)));
    setZValue(-1);

    output->setConnector(this);
    source->setConnector(this);
    updateGeometry();

    BaseModule *outputModule = output->module();
    BaseModule *inputModule = source->module();
    inputModule->setSource(source->id(), outputModule);
}

ConnectorItem::~ConnectorItem()
{
}

void ConnectorItem::updateGeometry()
{
    QPointF srcPnt = _output->rect().center();
    srcPnt = _output->mapToScene(srcPnt);

    QPointF outPnt = _source->rect().center();
    outPnt = _source->mapToScene(outPnt);

    QLineF line(srcPnt, outPnt);

    setLine(line);
}

void ConnectorItem::disconnect()
{
    _output->setConnector(nullptr);
    _source->setConnector(nullptr);
    BaseModule *inputModule = _source->module();
    inputModule->setSource(_source->id(), nullptr);
}
