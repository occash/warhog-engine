#ifndef NATIVEINTERFACE_H
#define NATIVEINTERFACE_H

class NativeLoop;
class NativeScreen;
class NativeWindow;
class NativeInput;
class NativeGLContext;

class NativeInterface
{
public:
	virtual NativeLoop *loop() const = 0;
	virtual NativeScreen *screen() const = 0;
	virtual NativeWindow *window() const = 0;
	virtual NativeInput *input() const = 0;
	virtual NativeGLContext *glContext() const = 0;

};

#endif //NATIVEINTERFACE_H
