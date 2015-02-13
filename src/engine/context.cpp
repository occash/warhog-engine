#include "context.h"
#include "nativecontext.h"
#include "platformmanager.h"
#include "window.h"

Context::Context()
	: _context(PlatformManager::instance()->context())
{
	_context->create();
}

Context::~Context()
{
	_context->destroy();
}

void Context::makeCurrent(Window * window)
{
	_context->makeCurrent(window->_window);
}

void Context::doneCurrent()
{
	_context->doneCurrent();
}

void Context::swapBuffers()
{
	_context->swapBuffers();
}

GLFunction Context::resolve(const char *name) const
{
	return _context->resolve(name);
}