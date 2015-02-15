#ifndef MODULEITEM_H
#define MODULEITEM_H

#include <QGraphicsRectItem>
#include <QWidget>
#include <QMetaProperty>
#include <QMap>
#include <QPropertyAnimation>

class BaseModule;
class SourceItem;
class OutputItem;
class QGraphicsTextItem;

class ModuleItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ getBorderColor WRITE setBorderColor)

public:
    ModuleItem(BaseModule *module, QGraphicsItem *parent = nullptr);
    ~ModuleItem();

    QColor getBorderColor() const;
    void setBorderColor(QColor c);

    BaseModule *module() const { return _module; }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant& value);

signals:
    void changed();

private slots:
    void onBoolChanged(bool b);
    void onIntChanged(int i);
    void onDoubleChanged(double val);
    void onEnumChanged(const QString&);

private:
    void setupTitle(QString title);
    void setupProperties(QObject *module);
    void setupConnectors();

    QWidget *setupBool(QObject *, QMetaProperty);
    QWidget *setupInt(QObject *, QMetaProperty);
    QWidget *setupDouble(QObject *, QMetaProperty);
    QWidget *setupEnum(QObject *, QMetaProperty);

private:
    friend class ConnectorItem;

    QGraphicsTextItem *_title;
    OutputItem *_output;
    QList<SourceItem *> _sources;
    QMap<QWidget *, QMetaProperty> _props;
    QPropertyAnimation _borderAnim;

    bool _clicked;
    QPointF _point;

    BaseModule *_module;

};

#endif // MODULEITEM_H
