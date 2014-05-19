#include "renderwidget.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtGui/QWindow>

RenderWidget::RenderWidget(QWidget *parent)
    : QWidget(parent)
{
    WId handle = _window.handle();
    QWindow *win = QWindow::fromWinId(handle);
    QWidget *widget = QWidget::createWindowContainer(win);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(widget);
    layout->setMargin(0);
    setLayout(layout);

    startTimer(0);
}

RenderWidget::~RenderWidget()
{

}

void RenderWidget::timerEvent(QTimerEvent *)
{
    _window.render();
}
