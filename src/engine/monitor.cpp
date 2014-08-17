#include "monitor.h"

/*#include <GLFW/glfw3.h>

Monitor::Monitor(GLFWmonitor *handle)
    : _handle(handle)
{
}

Monitor::~Monitor()
{
}

std::shared_ptr<Monitor> Monitor::screen(int index)
{
    if (index < 1)
    {
        GLFWmonitor *primary = glfwGetPrimaryMonitor();
        return std::shared_ptr<Monitor>(new Monitor(primary));
    }
    else
    {
        if (_monitors.size() == 0)
            getMonitors();

        if (index >= _monitors.size())
            return nullptr;

        return _monitors[index - 1];
    }
}

void Monitor::getMonitors()
{
    int count = 0;
    GLFWmonitor **monitors = glfwGetMonitors(&count);
    
    _monitors.clear();
    _monitors.resize(count);
    for (int i = 0; i < count; +i)
        _monitors.push_back(
        std::shared_ptr<Monitor>(
        new Monitor(monitors[i])));
}

Monitor::MonitorArray Monitor::_monitors;
*/