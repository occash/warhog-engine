#ifndef WINDOWSCONTEXT_H
#define WINDOWSCONTEXT_H

#include <nativecontext.h>

class WindowsContext : public NativeContext
{
public:
	WindowsContext();
	~WindowsContext();

	SurfaceFormat format() const override;
	void setFormat(const SurfaceFormat&) override;

	void makeCurrent(Window *) override;
	void doneCUrrent() override;

private:
	SurfaceFormat _format;

};

#endif //WINDOWSCONTEXT_H
