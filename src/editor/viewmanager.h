#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include <QObject>
#include <QSettings>
#include <QMap>

class ViewCreator;

class QDockWidget;

/*! \brief This class manages the VIEW menu entries
*/
class ViewManager : public QObject
{
	Q_OBJECT

public:
	ViewManager(QObject *parent);
	~ViewManager();

	QStringList views() const;
	bool registerView(const QString& name, ViewCreator *creator);
	QDockWidget *createView(const QString& name);

private:
	void readSettings();
	void writeSettings();

private:
	QSettings _settings;
	QMap<QString, ViewCreator *> _views;

};

#endif
