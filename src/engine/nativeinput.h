#ifndef NATIVEINPUT_H
#define NATIVEINPUT_H

#include "input.h"

class NativeInput
{
public:
	bool key(unsigned int key);
	bool button(Input::Button b);
	float axis(Input::Axis a);

};

#endif //NATIVEINPUT_H