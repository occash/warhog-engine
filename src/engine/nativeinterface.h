#ifndef NATIVEINTERFACE_H
#define NATIVEINTERFACE_H

class NativeLoop;
class NativeScreen;
class NativeWindow;
class NativeInput;
class NativeContext;

class NativeInterface
{
public:
    virtual NativeLoop *loop() const = 0;
    virtual NativeScreen *primaryScreen() = 0;
    virtual int screenCount() = 0;
    virtual NativeScreen *screen(int) = 0;
    virtual NativeWindow *window() const = 0;
    virtual NativeInput *input() const = 0;
    virtual NativeContext *context(const char *) const = 0;

};

#endif //NATIVEINTERFACE_H
