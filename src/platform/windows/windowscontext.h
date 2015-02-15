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

    void create() override;
    void destroy() override;

    void makeCurrent(NativeWindow *) override;
    void doneCurrent() override;

    void swapBuffers() override;

    GLFunction resolve(const char *) const override;

private:
    SurfaceFormat _format;
    friend struct ContextData;
    ContextData *_data;

};

#endif //WINDOWSCONTEXT_H
