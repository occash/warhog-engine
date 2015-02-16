#include "dispatcher.h"
#include "platformmanager.h"
#include "nativeloop.h"


Dispatcher::Dispatcher()
    : _loop(PlatformManager::instance()->loop())
{
}

Dispatcher::~Dispatcher()
{
    delete _loop;
}

void Dispatcher::update()
{
    _loop->update();
}
