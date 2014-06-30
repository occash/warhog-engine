#include "viewmanager.h"
#include "viewcreator.h"

#include <QString>
#include <QStringList>

ViewManager::ViewManager(QObject *parent) :
	QObject(parent)
{
}


ViewManager::~ViewManager()
{
}

QStringList ViewManager::views() const
{
	return _views.keys();
}

bool ViewManager::registerView(const QString& name, ViewCreator *creator)
{
	if (!creator)
		return false;

	_views.insert(name, creator);
	return true;
}

QDockWidget* ViewManager::createView(const QString& name)
{
	auto view = _views.find(name);
	if (view == _views.end())
		return nullptr;

	ViewCreator *creator = view.value();
	return creator->createView();
}

void ViewManager::readSettings()
{
	/*_settings.beginGroup("view");
	QStringList groups = _settings.childGroups();
	foreach(const QString& groupName, groups)
	{
		_settings.beginGroup(groupName);
		_settings.value("name");
		_settings.endGroup();
	}
	_settings.endGroup();*/
}

void ViewManager::writeSettings()
{

}
