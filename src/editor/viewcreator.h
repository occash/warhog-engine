#ifndef VIEWCREATOR_H
#define VIEWCREATOR_H

#include <QObject>

class QWidget;
class QDockWidget;
class QAction;

class ViewCreator : QObject
{
    Q_OBJECT

public:
    ViewCreator();
    ~ViewCreator();

    virtual QString name() const = 0;
    virtual QString description() const = 0;
    virtual QString helpString() const = 0;
    virtual QWidget *create() const = 0;

private:
    friend class ViewManager;

    QAction *action();
    QDockWidget *createView();

private slots:
    void showDockWidget();

private:
    QAction *_action;
    QDockWidget *_dock;

};

#endif