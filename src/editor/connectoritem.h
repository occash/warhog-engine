#ifndef CONNECTORITEM_H
#define CONNECTORITEM_H

#include <QGraphicsLineItem>

class SourceItem;
class OutputItem;

class ConnectorItem : public QGraphicsLineItem
{
public:
    ConnectorItem(OutputItem *output, SourceItem *source);
    ~ConnectorItem();

    void updateGeometry();
    void disconnect();

private:
    OutputItem *_output;
    SourceItem *_source;

};

#endif // CONNECTORITEM_H
