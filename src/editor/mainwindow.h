#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

class QTreeView;
class QSessionManager;

class SceneModel;
class InspectorWidget;
class ResourceWidget;
class ViewManager;

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

private slots:
	void commitData(QSessionManager *);

private:
	//Common
	QSettings _settings;
    QMenuBar *_menubar;
    QToolBar *_toolBar;
    QStatusBar *_statusBar;

	ViewManager *_viewManager;

    QTreeView *_tree;
    SceneModel *_model;
    InspectorWidget *_inspector;
    ResourceWidget *_resources;

};

#endif // MAINWINDOW_H
