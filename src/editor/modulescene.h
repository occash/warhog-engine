#ifndef MODULESCENE_H
#define MODULESCENE_H

#include <QGraphicsScene>
#include <QMenu>

class OutputItem;
class BaseModule;

class ModuleScene : public QGraphicsScene
{
    Q_OBJECT

public:
    ModuleScene(QObject *parent = nullptr);
    ~ModuleScene();

    BaseModule *output() const;

signals:
    void needInspect(QObject *);
    void generate();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private slots:
    void onSelectionChanged();

private:
    BaseModule *_outputModule;
    OutputItem *_temp;
    QMenu _menu;

};

#endif // MODULESCENE_H
