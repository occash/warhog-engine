#ifndef ENGINE_H
#define ENGINE_H

#include "global.h"
#include <entityx/Event.h>
#include <entityx/Entity.h>
#include <entityx/System.h>
#include <entityx/quick.h>
#include <ctime>

using namespace entityx;

class ENGINE_EXPORT Engine : public EntityX 
{
public:
	void start();
	int run();
	void step(double dt);
	void stop();

protected:
	void configure();
	void initialize();
	void update(double dt);

private:
	std::clock_t _timer;
	bool _running = false;

};

#endif