#ifndef TEXTUREVIEWER_H
#define TEXTUREVIEWER_H

#include <QWidget>
#include <QThread>

#include <noise/model/plane.h>
#include <noise/module/module.h>

class BaseModule;

class RenderWorker : public QObject
{
    Q_OBJECT

public:
    RenderWorker(QImage *image, noise::module::Module *module);
    RenderWorker(const RenderWorker& other);
    ~RenderWorker();

    void operator()(int idx);

private:
    QImage *_image;
    noise::model::Plane _plane;

};

class TextureViewer : public QWidget
{
    Q_OBJECT

public:
    TextureViewer(BaseModule *module, int w, int h, QWidget *parent = 0);
    ~TextureViewer();

public slots:
    void generate();

protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);

private:
    BaseModule *_module;
    QImage _image;
    RenderWorker _worker;
    QVector<int> _jobs;

};

#endif // TEXTUREVIEWER_H
