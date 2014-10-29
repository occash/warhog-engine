#include "moduleitem.h"
#include "basemodule.h"
#include "linkitem.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>
#include <QGraphicsTextItem>

#include <QBrush>
#include <QPen>
#include <QFont>

#include <QMetaObject>
#include <QMetaProperty>

#include <QCheckBox> //bool
#include <QSpinBox> //int
#include <QDoubleSpinBox> //double
#include <QComboBox> //enum


ModuleItem::ModuleItem(BaseModule *module, QGraphicsItem *parent)
    : QGraphicsRectItem(parent),
    _module(module),
    _clicked(false),
    _output(nullptr),
    _borderAnim(this, "color")
{
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);

    setRect(0, 0, 200, 140);
    setBrush(QBrush(QColor(80, 80, 80)));
    setPen(QPen(QColor(200, 200, 200)));

    setupTitle(module->name());
    setupProperties(module);
    setupConnectors();

    setAcceptHoverEvents(true);
    _borderAnim.setStartValue(QColor(200, 200, 200));
    _borderAnim.setEndValue(QColor(0, 180, 250));
    _borderAnim.setDuration(400);
}

ModuleItem::~ModuleItem()
{
    delete _module;
    //TODO: clear _props map
}

void ModuleItem::setupTitle(QString title)
{
    //Setup title
    _title = new QGraphicsTextItem(title, this);
    _title->setDefaultTextColor(QColor(225, 225, 225));
    _title->setFont(QFont("Arial", 10, QFont::Bold));
    qreal xPos = (rect().width() / 2) - (_title->boundingRect().width() / 2);
    _title->setPos(xPos, 0);
}

void ModuleItem::setupProperties(QObject *module)
{
    //Setup properties
    const QMetaObject *moduleMeta = module->metaObject();
    for (int i = 1; i < moduleMeta->propertyCount(); ++i)
    {
        QMetaProperty prop = moduleMeta->property(i);
        QString pname = prop.name();
        QStringList plist = pname.split(QRegExp("(?=[A-Z])"), QString::SkipEmptyParts);
        pname = plist[0];
        for (int i = 1; i < plist.size(); ++i)
        {
            pname.append(" ");
            pname.append(plist[i]);
        }

        QGraphicsTextItem *propText =
            new QGraphicsTextItem(pname, this);
        propText->setDefaultTextColor(QColor(225, 225, 225));
        propText->setFont(QFont("Arial", 10));
        propText->setPos(20, 20 + (i - 1) * 20);

        QWidget *editor = nullptr;
        if (prop.type() == QVariant::Bool)
            editor = setupBool(module, prop);
        if (prop.type() == QVariant::Int)
            editor = setupInt(module, prop);
        if (prop.type() == QVariant::Double)
            editor = setupDouble(module, prop);
        if (prop.type() == QVariant::String)
            editor = setupEnum(module, prop);

        if (editor)
        {
            _props.insert(editor, prop);
            QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget(this);
            proxy->setWidget(editor);
            proxy->setGeometry(QRectF(
                QPointF(rect().width() - 80, 20 + (i - 1) * 20),
                QSizeF(40, 20)
                ));
        }
    }
}

void ModuleItem::setupConnectors()
{
    //Setup sources
    for (int i = 0; i < _module->module()->GetSourceModuleCount(); ++i)
    {
        SourceItem *source = new SourceItem(_module, i, this);
        source->setRect(-8, 36 + 30 * i, 16, 16);
        _sources.append(source);
    }

    //Setup output
    _output = new OutputItem(_module, this);
    _output->setRect(rect().width() - 8, rect().height() / 2 - 8, 16, 16);
}

void ModuleItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        _clicked = true;
        _point = event->scenePos();
        setSelected(true);
        setBorderColor(Qt::yellow);
    }
}

void ModuleItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        _clicked = false;
}

void ModuleItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(_clicked)
    {
        QPointF delta = event->scenePos() - _point;
        moveBy(delta.rx(), delta.ry());
        _point = event->scenePos();
    }
}

QVariant ModuleItem::itemChange(GraphicsItemChange change, const QVariant & value)
{
    if(change == QGraphicsItem::ItemPositionChange)
    {
        _output->updateConnection();
        foreach(SourceItem *source, _sources)
            source->updateConnection();
    }

    return QGraphicsRectItem::itemChange(change, value);
}

void ModuleItem::onBoolChanged(bool b)
{
    QCheckBox *slider = qobject_cast<QCheckBox *>(sender());
    auto prop = _props.find(slider);
    if (prop != _props.end())
    {
        if ((*prop).write(_module, b))
            emit changed();
    }
}

void ModuleItem::onIntChanged(int i)
{
    QSpinBox *slider = qobject_cast<QSpinBox *>(sender());
    auto prop = _props.find(slider);
    if (prop != _props.end())
    {
        if ((*prop).write(_module, i))
            emit changed();
    }
}

void ModuleItem::onDoubleChanged(double d)
{
    QDoubleSpinBox *slider = qobject_cast<QDoubleSpinBox *>(sender());
    auto prop = _props.find(slider);
    if (prop != _props.end())
    {
        if ((*prop).write(_module, d))
            emit changed();
    }
}

void ModuleItem::onEnumChanged(const QString& e)
{
    QComboBox *slider = qobject_cast<QComboBox *>(sender());
    auto prop = _props.find(slider);
    if (prop != _props.end())
    {
        if ((*prop).write(_module, e))
            emit changed();
    }
}

QWidget * ModuleItem::setupBool(QObject *meta, QMetaProperty prop)
{
    QCheckBox *box = new QCheckBox();
    box->setChecked(prop.read(meta).toBool());
    connect(box, SIGNAL(toggled(bool)), this, SLOT(onBoolChanged(bool)));
    return box;
}

QWidget * ModuleItem::setupInt(QObject *meta, QMetaProperty prop)
{
    QSpinBox *slider = new QSpinBox();
    slider->setValue(prop.read(meta).toInt());
    QVariant vrange = meta->property((QString(prop.name()) + "Range").toLatin1().constData());
    if (vrange.type() == QVariant::Size)
    {
        QSize range = vrange.toSize();
        slider->setMinimum(range.width());
        slider->setMaximum(range.height());
        slider->setSingleStep(1);
    }
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(onIntChanged(int)));
    return slider;
}

QWidget * ModuleItem::setupDouble(QObject *meta, QMetaProperty prop)
{
    QDoubleSpinBox *slider = new QDoubleSpinBox();
    slider->setValue(prop.read(meta).toDouble());
    QVariant vrange = meta->property((QString(prop.name()) + "Range").toLatin1().constData());
    if (vrange.type() == QVariant::SizeF)
    {
        QSizeF range = vrange.toSizeF();
        slider->setMinimum(range.width());
        slider->setMaximum(range.height());
        slider->setSingleStep((range.height() - range.width()) / 1000);
    }
    connect(slider, SIGNAL(valueChanged(double)), this, SLOT(onDoubleChanged(double)));
    return slider;
}

QWidget * ModuleItem::setupEnum(QObject *meta, QMetaProperty prop)
{
    QComboBox *box = new QComboBox();
    QVariant vrange = meta->property((QString(prop.name()) + "Range").toLatin1().constData());
    if (vrange.type() == QVariant::StringList)
    {
        QStringList range = vrange.toStringList();
        box->addItems(range);
    }
    box->setCurrentText(prop.read(meta).toString());
    connect(box, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(onEnumChanged(const QString&)));
    return box;
}

QColor ModuleItem::getBorderColor() const
{
    return pen().color();
}

void ModuleItem::setBorderColor(QColor c)
{
    setPen(QPen(c));
}

void ModuleItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    _borderAnim.setDirection(QAbstractAnimation::Forward);
    _borderAnim.start();
}

void ModuleItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    _borderAnim.setDirection(QAbstractAnimation::Backward);
    _borderAnim.start();
}
