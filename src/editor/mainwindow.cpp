#include "mainwindow.h"
#include "project.h"

#include "scene/scenewidget.h"
#include "inspector/inspectorwidget.h"
#include "resource/resourcewidget.h"
#include "render/renderwidget.h"

#include "dialogs/newproject.h"

#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QDockWidget>
#include <QSessionManager>
#include <QCoreApplication>
#include <QMessageBox>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
	_project(nullptr),
    _scene(new SceneWidget(this)),
    _inspector(new InspectorWidget(this)),
    _resources(new ResourceWidget(this)),
	_renderer(new RenderWidget(this))
{
	readSettings();
    installUi();

    setCentralWidget(_renderer);

	connect(qApp, SIGNAL(commitDataRequest(QSessionManager *)), 
		this, SLOT(commitData(QSessionManager *)));
}

MainWindow::~MainWindow()
{
	setProject(nullptr);
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

	connect(newAction, SIGNAL(triggered()), this, SLOT(newProject()));
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

	QDockWidget *leftDock = new QDockWidget("Project tree", this);
	leftDock->setWidget(_scene);
	addDockWidget(Qt::LeftDockWidgetArea, leftDock);

	QDockWidget *rightDock = new QDockWidget("Inspector", this);
	rightDock->setWidget(_inspector);
	addDockWidget(Qt::RightDockWidgetArea, rightDock);

	QDockWidget *bottomDock = new QDockWidget("Resources", this);
	bottomDock->setWidget(_resources);
	addDockWidget(Qt::LeftDockWidgetArea, bottomDock);
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

void MainWindow::newProject()
{
	NewProjectDialog dialog;
	if (dialog.exec())
	{
		QString baseName = dialog.projectName();
		QString basePath = dialog.projectPath();

		QString projFile = Project::create(basePath, baseName);
		if (projFile.isEmpty())
		{
			QMessageBox::warning(nullptr,
				tr("Project error"),
				tr("Cannot create project"),
				QMessageBox::Ok);
			return;
		}

		Project *project = Project::open(projFile);
		if (!project)
		{
			QMessageBox::warning(nullptr,
				tr("Project error"),
				tr("Cannot create project"),
				QMessageBox::Ok);
			return;
		}

		setProject(project);
	}
}

void MainWindow::setProject(Project *project)
{
	if (!project)
		delete _project;

	_project = project;
	
}

