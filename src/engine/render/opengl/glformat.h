#ifndef HINTS_H
#define HINTS_H

#include "../../global.h"

#include <string>
#include <yaml-cpp/yaml.h>

struct ENGINE_EXPORT GLFormat
{
    GLFormat();

    enum ClientApi
	{
		Default,
        Desktop,
        Embedded
    };
    enum Profile
	{
        Any,
        Core,
        Compatibility
    };
	enum Options
	{
		StereoBuffers,
		DebugContext,
		DeprecatedFunctions
	};
	enum SwapBehaviour
	{
		DefaultBehaviour,
		Single,
		Double,
		Triple
	};

public:
	int major;
	int minor;

    ClientApi api;
    Profile profile;
	Options options;
	SwapBehaviour behaviour;

	int redBits;
	int greenBits;
	int blueBits;
	int alphaBits;

	int depthBits;
	int stensilBits;

	int samples;
	int interval;
};

#endif