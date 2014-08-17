#ifndef MONITOR_H
#define MONITOR_H

#include "global.h"

#include <vector>
#include <memory>

class GLFWmonitor;

struct VideoMode
{
    int 	width;
    int 	height;
    int 	redBits;
    int 	greenBits;
    int 	blueBits;
    int 	refreshRate;
};

class ENGINE_EXPORT Monitor
{
public:
    virtual ~Monitor();
    static std::shared_ptr<Monitor> screen(int index);

private:
    Monitor(GLFWmonitor *handle);

    static void getMonitors();

private:
    friend class Window;
    typedef std::vector<std::shared_ptr<Monitor>> MonitorArray;

    static MonitorArray _monitors;

    GLFWmonitor *_handle;
    VideoMode mode;

};

#endif
