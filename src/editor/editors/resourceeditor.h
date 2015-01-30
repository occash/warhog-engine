#ifndef RESOURCEEDITOR_H
#define RESOURCEEDITOR_H

#include <QWidget>

class BaseResource;

class ResourceEditor : public QWidget
{
public:
	ResourceEditor(QWidget *parent = 0);
	~ResourceEditor();

	virtual void edit(BaseResource *) = 0;
};

#endif //RESOURCEEDITOR_H
