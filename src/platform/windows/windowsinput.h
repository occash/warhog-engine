#ifndef WINDOWSINPUT_H
#define WINDOWSINPUT_H

#include <nativeinput.h>

class WindowsInput : public NativeInput
{
public:
    WindowsInput();
    ~WindowsInput();

    bool key(unsigned int key) const override;
    bool button(Input::Button b) const override;
    float axis(Input::Axis a) const override;
    float mouseX() const override;
    float mouseY() const override;

    //Handle from Window
    void keyDown(unsigned int);
    void keyUp(unsigned int);
    void mouseMove(int, int);
    void buttonDown(Input::Button);
    void buttonUp(Input::Button);

private:
    friend struct InputData;
    InputData *_data;

};

#endif //WINDOWSINPUT_H