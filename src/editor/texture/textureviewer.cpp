#include "textureviewer.h"
#include "basemodule.h"

#include <QPainter>
#include <QtConcurrent/QtConcurrent>

#include <noise/module/perlin.h>
#include <noise/module/clamp.h>
#include <noise/model/plane.h>

#define IND_MAX 128

RenderWorker::RenderWorker(QImage *image, noise::module::Module *module)
: QObject(nullptr),
_image(image)
{
    _plane.SetModule(*module);
}

RenderWorker::RenderWorker(const RenderWorker& other)
    : _image(other._image),
    _plane(other._plane)
{
}

RenderWorker::~RenderWorker()
{
}

void RenderWorker::operator()(int idx)
{
    QRgb *data = (QRgb *)_image->bits();
    int hs = _image->height() * idx / IND_MAX;
    int he = _image->height() * (idx + 1) / IND_MAX;
    int i = hs * _image->width();
    for (int y = hs; y < he; ++y)
    {
        for (int x = 0; x < _image->width(); ++x)
        {
            double val = _plane.GetValue(x, y);
            val = (val + 1.0) / 2.0;
            int r = val * 255;
            QColor color(r, r, r);
            data[i] = color.rgb();
            i++;
        }
    }
}

TextureViewer::TextureViewer(BaseModule *module, int w, int h, QWidget *parent)
    : QWidget(parent),
    _module(module),
    _image(w, h, QImage::Format_ARGB32),
    _worker(&_image, module->module()),
    _jobs(IND_MAX)
{
    setFixedSize(w, h);
    startTimer(10);
}

TextureViewer::~TextureViewer()
{
}

void TextureViewer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, _image);
}

void TextureViewer::generate()
{
    if (!_module || !_module->isValid())
        return;

    for (int i = 0; i < _jobs.size(); ++i)
    {
        _jobs[i] = i;
    }

    QtConcurrent::map(_jobs, _worker);
}

void TextureViewer::timerEvent(QTimerEvent *event)
{
    update();
}
