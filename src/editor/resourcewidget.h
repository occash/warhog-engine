#ifndef RESOURCEWIDGET_H
#define RESOURCEWIDGET_H

#include <QtWidgets/QWidget>
//#include "ui_resourcewidget.h"

class Importer;

class ResourceWidget : public QWidget
{
    Q_OBJECT

public:
    ResourceWidget(QWidget *parent = 0);
    ~ResourceWidget();

    Importer *findImporter(const QString& ext);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private:
    //Ui::ResourceWidgetClass ui;
    QList<Importer *> _importers;

};

#endif // RESOURCEWIDGET_H
