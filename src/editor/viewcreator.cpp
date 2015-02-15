#include "viewcreator.h"

#include <QAction>
#include <QDockWidget>

ViewCreator::ViewCreator()
{

}

ViewCreator::~ViewCreator()
{

}

QDockWidget *ViewCreator::createView()
{
    QDockWidget *dockWidget = new QDockWidget(name());
    QWidget *widget = create();
    widget->setParent(dockWidget);
    dockWidget->setWidget(widget);

    return dockWidget;
}

QAction *ViewCreator::action()
{
    QAction *dockAction = new QAction(name(), this);
    dockAction->setToolTip(description());
    dockAction->setStatusTip(description());
    dockAction->setWhatsThis(helpString());

    connect(dockAction, SIGNAL(triggered()), this, SLOT(showDockWidget()));

    return dockAction;
}

void ViewCreator::showDockWidget()
{

}
