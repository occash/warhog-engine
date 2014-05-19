#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTreeView;
class SceneModel;
class InspectorWidget;
class ResourceWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QMenuBar *_menubar;
    QToolBar *_toolBar;
    QStatusBar *_statusBar;
    QTreeView *_tree;
    SceneModel *_model;
    InspectorWidget *_inspector;
    ResourceWidget *_resources;

private:
    void installActions();

};

#endif // MAINWINDOW_H
