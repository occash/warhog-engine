#include "project.h"

#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonObject>
#include <QJsonDocument>

Project::Project(const QString& path) :
	QObject(nullptr),
	_path(path)
{
}

Project *Project::open(const QString& path)
{
	QFile projFile(path);
	if (!projFile.open(QIODevice::ReadOnly))
		return nullptr;

	QJsonDocument projDocument;
	projDocument.fromBinaryData(projFile.readAll());
	QJsonObject global = projDocument.object();

	Project *project = new Project(QFileInfo(path).path());
	project->setVersion(global["version"].toString());
	project->setName(global["name"].toString());
	project->setResources(global["resources"].toString());
	project->setScene(global["scene"].toString());

	return project;
}

QString Project::create(const QString& path, const QString& name)
{
	QDir projectDir(path);
	if (!projectDir.mkdir(name))
		return QString();

	//Create required subfolders
	projectDir.mkdir("resources");
	//projectDir.mkdir("Levels");

	QString projFileName = name.toLower();
	projFileName.append(".whproj");
	projFileName = projectDir.filePath(projFileName);

	QJsonObject global;
	global["version"] = "0.1";
	global["name"] = name;
	global["resources"] = projectDir.relativeFilePath("resources");
	global["scene"] = projectDir.relativeFilePath("scene");
	
	QFile projFile(projFileName);
	if (!projFile.open(QIODevice::WriteOnly))
		return QString();

	QJsonDocument projDocument(global);
	projFile.write(projDocument.toBinaryData());

	return projFileName;
}

QString Project::version() const
{
	return _version;
}

QString Project::name() const
{
	return _name;
}

QString Project::resources() const
{
	return _resources;
}

QString Project::scene() const
{
	return _scene;
}

void Project::setVersion(const QString& v)
{
	_version = v;
}

void Project::setName(const QString& v)
{
	_name = v;
}

void Project::setResources(const QString& v)
{
	QDir projectPath(_path);
	projectPath.setPath(v);
	_resources = projectPath.absolutePath();
}

void Project::setScene(const QString& v)
{
	QDir projectPath(_path);
	projectPath.setPath(v);
	_resources = projectPath.absolutePath();
}
