#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QFile>

int main(int argc, char *argv[])
{
	//Setup application
	QApplication::setApplicationDisplayName("Warhog Editor");
	QApplication::setApplicationName("Warhog Editor");
	QApplication::setApplicationVersion("0.1");
	QApplication::setOrganizationDomain("warhog.com");
	QApplication::setOrganizationName("Warhog");

    QApplication a(argc, argv);

	//Load style
    QFile styleFile(":/styles/dark");
    styleFile.open(QIODevice::ReadOnly);
    a.setStyleSheet(styleFile.readAll());

	//Load splash screen
	QSplashScreen splash(QPixmap(":/splash"));
	splash.showMessage("Loading resources...", Qt::AlignBottom, Qt::black);
	splash.show();
	a.processEvents();

	//Create main window
	MainWindow w;
	splash.finish(&w);
	w.show();
	w.installThumbnail();

    return a.exec();
}
