#ifndef NATIVESCREEN_H
#define NATIVESCREEN_H

class NativeScreen
{
public:
    virtual int width() = 0;
    virtual int height() = 0;
    virtual int refreshRate() = 0;
    virtual int physicalWidth() = 0;
    virtual int physicalHeight() = 0;

    virtual void setVideoMode(int, int, int) = 0;
};

#endif //NATIVESCREEN_H
