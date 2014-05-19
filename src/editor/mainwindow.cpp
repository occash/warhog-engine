#include "scenemodel.h"
#include "inspectorwidget.h"#
#include "mainwindow.h"
#include "renderwidget.h"
#include "resourcewidget.h"

#include <QDockWidget>
#include <QTreeView>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    _tree(new QTreeView(this)),
    _model(new SceneModel(this)),
    _inspector(new InspectorWidget(this)),
    _resources(new ResourceWidget(this))
{
    installActions();

    setCentralWidget(new RenderWidget(this));
    
    QDockWidget *leftDock = new QDockWidget("Project tree", this);
    _tree->setHeaderHidden(true);
    _tree->setModel(_model);
    leftDock->setWidget(_tree);
    addDockWidget(Qt::LeftDockWidgetArea, leftDock);

    QDockWidget *rightDock = new QDockWidget("Inspector", this);
    rightDock->setWidget(_inspector);
    addDockWidget(Qt::RightDockWidgetArea, rightDock);

    QDockWidget *bottomDock = new QDockWidget("Resources", this);
    bottomDock->setWidget(_resources);
    addDockWidget(Qt::BottomDockWidgetArea, bottomDock);

    connect(_tree, SIGNAL(activated(const QModelIndex&)),
        _inspector, SLOT(inspectEntity(const QModelIndex&)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::installActions()
{
    QMenu *fileMenu = new QMenu("FILE", this);
    QMenu *entityMenu = new QMenu("ENTITY", this);
    QMenu *componentMenu = new QMenu("COMPONENT", this);
    QMenu *aboutMenu = new QMenu("ABOUT", this);

    _menubar = new QMenuBar(this);
    _menubar->addMenu(fileMenu);
    _menubar->addMenu(entityMenu);
    _menubar->addMenu(componentMenu);
    _menubar->addMenu(aboutMenu);
    setMenuBar(_menubar);

    _toolBar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, _toolBar);

    _statusBar = new QStatusBar(this);
    setStatusBar(_statusBar);
}
