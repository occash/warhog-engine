#ifndef LINKITEM_H
#define LINKITEM_H

#include <QGraphicsRectItem>

class BaseModule;
class ConnectorItem;

class LinkItem : public QGraphicsRectItem
{
public:
    LinkItem(BaseModule *linkedModule, QGraphicsItem *parent = nullptr);
    ~LinkItem();

    BaseModule *module() const { return _module; }
    ConnectorItem *connector() const { return _connector; }
    void setConnector(ConnectorItem *c) { _connector = c; }
    void updateConnection();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) {}

private:
    BaseModule *_module;
    ConnectorItem *_connector;

};

class SourceItem : public LinkItem
{
public:
    SourceItem(BaseModule *module, int id, QGraphicsItem *parent = nullptr);
    ~SourceItem();

    int id() const { return _id; }

private:
    int _id;

};

class OutputItem : public LinkItem
{
public:
    OutputItem(BaseModule *module, QGraphicsItem *parent = nullptr);
    ~OutputItem();

};

#endif // LINKITEM_H
