#ifndef ENGINE_H
#define ENGINE_H

#include "global.h"
#include <entityx/Event.h>
#include <entityx/Entity.h>
#include <entityx/System.h>
#include <entityx/quick.h>
#include <ctime>

class Material;
class Window;

class ENGINE_EXPORT Engine : public entityx::EntityX
{
public:
	void start();
	int run();
	void step(double dt);
	void stop();
	Window *window() const;

protected:
	void configure();
	void initialize();
	void update(double dt);

private:
	Window *_window;
	Material *mat;
	entityx::Entity _lightNode;
	double _elapsed;
	std::clock_t _timer;
	bool _running = false;

};

#endif