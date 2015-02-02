//#include <engine.h>
#include <window.h>
#include <dispatcher.h>

int main()
{
	Dispatcher app;

	Window w;
	w.show();

	while (w.isVisible())
		app.update();
	
	/*Engine game;
	game.start();
	return game.run();*/
}