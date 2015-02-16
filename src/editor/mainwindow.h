#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Compile: always include entityx before Qt
#include <entityx/Entity.h>

#include <QMainWindow>
#include <QSettings>

#include <engine.h>

class QSessionManager;
class QMenu;
class QAction;
class QWinJumpList;
class QWinThumbnailToolBar;

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

    void installThumbnail();

protected:
    void keyReleaseEvent(QKeyEvent *);
    void timerEvent(QTimerEvent *);

private:
    void installUi();
    void installRecent();
    void readSettings();
    void writeSettings();
    void setProject(Project *project);
    void openProject(const QString& path);

private slots:
    void commitData(QSessionManager&);
    void newProject();
    void openProject();
    void closeProject();
    void saveProject();
    void recentProject(QAction *);
    void createEmpty();
    void addComponent(QAction *);
private:
    //Common
    bool _maximized;
    QSettings _settings;
    QMenuBar *_menubar;
    QToolBar *_toolBar;
    QStatusBar *_statusBar;
    QMenu *_recentMenu;

#if defined(Q_OS_WIN)
    QWinJumpList *_jumpList;
    QWinThumbnailToolBar *_thumbToolbar;
#endif

    Project *_project;
    QStringList _recent;

    SceneWidget *_scene;
    InspectorWidget *_inspector;
    ResourceWidget *_resources;
    RenderWidget *_renderer;

    Engine _engine;
};

#endif // MAINWINDOW_H
