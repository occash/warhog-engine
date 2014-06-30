#include "scenemodel.h"
#include "inspectorwidget.h"
#include "mainwindow.h"
#include "renderwidget.h"
#include "resourcewidget.h"
#include "viewmanager.h"
#include "viewcreator.h"

#include <QDockWidget>
#include <QTreeView>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QSessionManager>
#include <QCoreApplication>
#include <QMessageBox>
#include <QKeyEvent>

/*class TestCreator : public ViewCreator
{
public:
	QWidget *create() const override
	{
		return new QWidget();
	}
};*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    _tree(new QTreeView(this)),
    _model(new SceneModel(this)),
    _inspector(new InspectorWidget(this)),
    _resources(new ResourceWidget(this)),
	_viewManager(new ViewManager(this))
{
	readSettings();

	//_viewManager->registerView("Test", new TestCreator());

    installUi();

	RenderWidget *renderer = new RenderWidget(this);
    setCentralWidget(renderer);

    connect(_tree, SIGNAL(activated(const QModelIndex&)),
        _inspector, SLOT(inspectEntity(const QModelIndex&)));

	connect(qApp, SIGNAL(commitDataRequest(QSessionManager *)), this, SLOT(commitData(QSessionManager *)));
}

MainWindow::~MainWindow()
{
	writeSettings();
}

void MainWindow::installUi()
{
	//Create top level menus
    QMenu *fileMenu = new QMenu(tr("FILE"), this);
	QMenu *viewMenu = new QMenu(tr("VIEW"), this);
    QMenu *entityMenu = new QMenu(tr("ENTITY"), this);
    QMenu *componentMenu = new QMenu(tr("COMPONENT"), this);
    QMenu *aboutMenu = new QMenu(tr("ABOUT"), this);

	//Create actions for FILE menu
	QAction *newAction = new QAction(tr("New project"), fileMenu);
	QAction *openAction = new QAction(tr("Open project"), fileMenu);
	QAction *closeAction = new QAction(tr("Close project"), fileMenu);
	QAction *saveAction = new QAction(tr("Save project"), fileMenu);
	QMenu *recentMenu = new QMenu(tr("Recent projects"), fileMenu);
	QAction *quitAction = new QAction(tr("Quit"), fileMenu);
	//For MacOS only 
	quitAction->setMenuRole(QAction::QuitRole);

	connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

	fileMenu->addAction(newAction);
	fileMenu->addAction(openAction);
	fileMenu->addAction(closeAction);
	fileMenu->addAction(saveAction);
	fileMenu->addSeparator();
	fileMenu->addMenu(recentMenu);
	fileMenu->addAction(quitAction);

	//Create actions for VIEW menu
	QAction *fullscreenAction = new QAction(tr("Full screen"), viewMenu);

	//addDockWidget(Qt::LeftDockWidgetArea, _viewManager->createView("Test"));

	QDockWidget *leftDock = new QDockWidget("Project tree", this);
	leftDock->setWidget(_tree);
	addDockWidget(Qt::LeftDockWidgetArea, leftDock);

	QDockWidget *rightDock = new QDockWidget("Inspector", this);
	rightDock->setWidget(_inspector);
	addDockWidget(Qt::RightDockWidgetArea, rightDock);

	QDockWidget *bottomDock = new QDockWidget("Resources", this);
	bottomDock->setWidget(_resources);
	addDockWidget(Qt::BottomDockWidgetArea, bottomDock);

	//Install menus
    _menubar = new QMenuBar(this);
    _menubar->addMenu(fileMenu);
	_menubar->addMenu(viewMenu);
    _menubar->addMenu(entityMenu);
    _menubar->addMenu(componentMenu);
    _menubar->addMenu(aboutMenu);
    setMenuBar(_menubar);

    _toolBar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, _toolBar);

    _statusBar = new QStatusBar(this);
    setStatusBar(_statusBar);
}

void MainWindow::commitData(QSessionManager *manager)
{
	if (manager->allowsInteraction())
	{
		int ret = QMessageBox::warning(
			this,
			tr("Session end"),
			tr("Save changes to disk?"),
			QMessageBox::Save | QMessageBox::Discard, QMessageBox::Cancel
			);
		switch (ret)
		{
		case QMessageBox::Save:
			manager->release();
			/*if (!saveAll())
				manager->cancel();*/
			break;
		case QMessageBox::Discard:
			break;
		case QMessageBox::Cancel:
		default:
			manager->cancel();
			break;
		}
	}
	//We can't interact with user so just quit
}

void MainWindow::readSettings()
{
	bool fullscreen = _settings.value("editor/fullscreen", false).toBool();
	bool maximized = _settings.value("editor/maximized", false).toBool();
	int width = _settings.value("editor/width", 800).toInt();
	int height = _settings.value("editor/height", 600).toInt();
	
	resize(width, height);
	Qt::WindowStates states = windowState();
	if (fullscreen)
		states |= Qt::WindowFullScreen;
	if (maximized)
		states |= Qt::WindowMaximized;
	setWindowState(states);
}

void MainWindow::writeSettings()
{
	_settings.setValue("editor/fullscreen", isFullScreen());
	_settings.setValue("editor/maximized", isMaximized());
	if (!isMaximized() && !isFullScreen())
	{
		_settings.setValue("editor/width", width());
		_settings.setValue("editor/height", height());
	}
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_F11)
		setWindowState(windowState() ^ Qt::WindowFullScreen);
}
