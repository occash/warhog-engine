#ifndef MONITOR_H
#define MONITOR_H

#include <boost/shared_ptr.hpp>
#include <vector>

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

class Monitor
{
public:
    virtual ~Monitor();

    static boost::shared_ptr<Monitor> screen(int index);

private:
    Monitor(GLFWmonitor *handle);

    static void getMonitors();

private:
    friend class Window;
    typedef std::vector<boost::shared_ptr<Monitor>> MonitorArray;

    static MonitorArray _monitors;

    GLFWmonitor *_handle;
    VideoMode mode;

};

#endif
