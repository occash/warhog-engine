/*#include "resourcewidget.h"
#include "resourcemanager.h"
#include "meshresource.h"
#include "scriptresource.h"*/
//#include "renderwidget.h"
#include "scenemodel.h"
#include "inspectorwidget.h"
#include "mainwindow.h"
/*#include "textureviewer.h"
#include "moduleinspector.h"*/


/*#include "moduleitem.h"
#include "basemodule.h"
#include "modulescene.h"
#include "perlinmodule.h"
#include "clampmodule.h"*/

#include <QtWidgets/QApplication>
//#include <QGraphicsView>
#include <QFile>
#include <QStandardPaths>
#include <QSplashScreen>

#include "resourcemanager.h"
#include "fileresourceio.h"
#include <resource/scriptresource.h>

int main(int argc, char *argv[])
{
	QApplication::setApplicationDisplayName("WarHog Editor");
	QApplication::setApplicationName("WarHog Editor");
	QApplication::setApplicationVersion("0.1");
	QApplication::setOrganizationDomain("warhog.com");
	QApplication::setOrganizationName("Shal Ind");

    QApplication a(argc, argv);

	//QString configDir = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);

    QFile styleFile(":/style/main");
    styleFile.open(QIODevice::ReadOnly);
    a.setStyleSheet(styleFile.readAll());

	QSplashScreen splash(QPixmap(":/icons/splash"));
	splash.showMessage("Loading resources...", Qt::AlignBottom, Qt::white);
	splash.show();
	a.processEvents();

    MainWindow w;
	splash.finish(&w);
    w.show();

    /*ResourceManager::base = "C:\\projects\\ModernGL\\Win32\\Debug\\Assets\\";
    ResourceManager::add<MeshResource>();
    ResourceManager::add<ScriptResource>();
	*/
    /*std::shared_ptr<Script> script1(new Script());
    script1->engine = "lua";
    script1->name = "script1";
    script1->source = "class 'Script1' (Script);\n\nfunction Script1:init(self)\nend";

    ResourceManager::save<Script>("Scripts\\script1.script", script1);
    std::shared_ptr<Script> script2 = ResourceManager::load<Script>("Scripts\\script1.script");

    std::shared_ptr<Mesh> mesh = ResourceManager::load<Mesh>("Meshes\\teapot.mesh");*/

    /*ResourceWidget w;
    w.show();*/

    /*PerlinModule perlin;
    perlin.setOctaveCount(16);
    perlin.setFrequency(0.01);
    perlin.setPersistence(0.5);
    ModuleItem perlinItem(&perlin);

    ClampModule clamp;
    clamp.setLowerBound(-1.0);
    clamp.setUpperBound(1.0);
    ModuleItem clampItem(&clamp);

    perlinItem.setPos(0, 0);
    clampItem.setPos(250, 0);*/

    /*ModuleScene scene;
    QGraphicsView view(&scene);
    view.resize(640, 480);
    view.setBackgroundBrush(QBrush(QColor(40, 40, 40)));

    TextureViewer v(scene.output(), 512, 512);
    ModuleInspector inspector;

    view.show();
    v.show();
    inspector.show();

    QObject::connect(&scene, SIGNAL(generate()), &v, SLOT(generate()));
    QObject::connect(&scene, SIGNAL(needInspect(QObject *)), 
        &inspector, SLOT(inspectModule(QObject *)));*/

    return a.exec();
	//return 0;
}
