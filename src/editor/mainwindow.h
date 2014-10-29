#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Compile: always include entityx before Qt
#include <entityx/Entity.h>

#include <QMainWindow>
#include <QSettings>

class QSessionManager;

class InspectorWidget;
class ResourceWidget;
class SceneWidget;
class RenderWidget;
class Project;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
	void keyReleaseEvent(QKeyEvent *);

private:
	void installUi();
	void readSettings();
	void writeSettings();
	void setProject(Project *project);

private slots:
	void commitData(QSessionManager *);
	void newProject();

private:
	//Common
	QSettings _settings;
    QMenuBar *_menubar;
    QToolBar *_toolBar;
    QStatusBar *_statusBar;

	Project *_project;

	SceneWidget *_scene;
    InspectorWidget *_inspector;
    ResourceWidget *_resources;
	RenderWidget *_renderer;

};

#endif // MAINWINDOW_H
