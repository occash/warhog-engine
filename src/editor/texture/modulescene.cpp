#include "modulescene.h"
#include "moduleitem.h"
#include "linkitem.h"
#include "connectoritem.h"

#include "perlinmodule.h"
#include "voronoimodule.h"
#include "clampmodule.h"
#include "selectmodule.h"
#include "absmodule.h"
#include "billowmodule.h"
#include "constmodule.h"
#include "blendmodule.h"

#include <QGraphicsSceneMouseEvent>

class NoiseOutput : public noise::module::Module
{
public:
    NoiseOutput()
        : noise::module::Module(1) {}

    double GetValue(double x, double y, double z) const { return m_pSourceModule[0]->GetValue(x, y, z); }
    int GetSourceModuleCount() const { return 1; }
};

class OutputModule : public BaseModule
{
public:
    OutputModule(QObject *parent = nullptr)
        : BaseModule("Output", new NoiseOutput(), parent) {}
};

ModuleScene::ModuleScene(QObject *parent)
    : QGraphicsScene(parent),
    _temp(nullptr),
    _menu()
{
    _outputModule = new OutputModule();
    QGraphicsItem *item = new ModuleItem(_outputModule);
    item->setPos(0, 0);
    addItem(item);
    connect(this, SIGNAL(selectionChanged()), SLOT(onSelectionChanged()));

    QMenu *modifiers = _menu.addMenu("Modifier");
    modifiers->addAction("Abs");
    modifiers->addAction("Clamp");
    //QMenu *combiners = _menu.addMenu("Combiner");
    QMenu *generators = _menu.addMenu("Generator");
    generators->addAction("Billow");
    //generators->addAction("Checkerboard");
    generators->addAction("Const");
    //generators->addAction("Cylinders");
    generators->addAction("Perlin");
    //generators->addAction("RidgetMulti");
    //generators->addAction("Spheres");
    generators->addAction("Voronoi");
    QMenu *selectors = _menu.addMenu("Selector");
    selectors->addAction("Blend");
    selectors->addAction("Select");
    //QMenu *miscellaneouses = _menu.addMenu("Miscellaneous");
    //QMenu *transformers = _menu.addMenu("Transformer");
}

ModuleScene::~ModuleScene()
{
}

void ModuleScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!_temp)
    {
        QList<QGraphicsItem *> itms = items(event->scenePos());
        foreach(QGraphicsItem *itm, itms)
        {
            OutputItem *out = dynamic_cast<OutputItem *>(itm);
            if(out)
                _temp = out;
        }
    }

    QGraphicsScene::mousePressEvent(event);
}

void ModuleScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(_temp)
    {
        QList<QGraphicsItem *> itms = items(event->scenePos());
        foreach(QGraphicsItem *itm, itms)
        {
            SourceItem *src = dynamic_cast<SourceItem *>(itm);
            if(src)
            {
                //Already connected
                if(src->connector()
                    && _temp->connector()
                    && src->connector() == _temp->connector())
                    return;

                if(src->connector())
                {
                    ConnectorItem *connector = src->connector();
                    connector->disconnect();
                    removeItem(connector);
                    delete connector;
                }

                if(_temp->connector())
                {
                    ConnectorItem *connector = _temp->connector();
                    connector->disconnect();
                    removeItem(connector);
                    delete connector;
                }

                ConnectorItem *connector = new ConnectorItem(_temp, src);
                addItem(connector);
                emit generate();
            }
        }

        _temp = nullptr;
    }
    else
    {
        if (event->button() == Qt::RightButton)
        {
            QList<QGraphicsItem *> itms = items(event->scenePos());
            if (itms.isEmpty())
            {
                QAction *action = _menu.exec(event->screenPos());
                if (action)
                {
                    BaseModule *module;
                    if (action->text() == "Abs")
                        module = new AbsModule();
                    else if (action->text() == "Clamp")
                        module = new ClampModule();

                    else if (action->text() == "Billow")
                        module = new BillowModule();
                    else if (action->text() == "Const")
                        module = new ConstModule();
                    else if (action->text() == "Perlin")
                        module = new PerlinModule();
                    else if (action->text() == "Voronoi")
                        module = new VoronoiModule();

                    else if (action->text() == "Blend")
                        module = new BlendModule();
                    else if (action->text() == "Select")
                        module = new SelectModule();
                    

                    ModuleItem *item = new ModuleItem(module);
                    connect(item, SIGNAL(changed()), this, SIGNAL(generate()));
                    item->setPos(event->scenePos());
                    addItem(item);
                }
            }
        }
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

BaseModule *ModuleScene::output() const
{
    return _outputModule;
}

void ModuleScene::onSelectionChanged()
{
    QList<QGraphicsItem *> items = selectedItems();
    if (items.isEmpty())
    {
        emit needInspect(nullptr);
        return;
    }

    QGraphicsItem *item = items.at(0);
    ModuleItem *module = dynamic_cast<ModuleItem *>(item);

    if (module)
        emit needInspect(module->module());
}
