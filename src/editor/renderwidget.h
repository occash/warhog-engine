#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#include <window.h>
//#include <glcontext.h>

#include <QWidget>

class RenderWidget : public QWidget
{
    Q_OBJECT

public:
    RenderWidget(QWidget *parent = 0);
    ~RenderWidget();

protected:
    void timerEvent(QTimerEvent *);

private:
   // GLContext _context;
    Window _window;
};

#endif // RENDERWIDGET_H
