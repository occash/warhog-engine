#ifndef HINTS_H
#define HINTS_H

#include "flags.h"

class SurfaceFormat
{
public:
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
    enum Option
    {
        NoOptions,
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

    W_DECLAGE_FLAGS(Options, Option);

public:
    int major = 4;
    int minor = 3;

    ClientApi api = Desktop;
    Profile profile = Core;
    Options options = NoOptions;
    SwapBehaviour behaviour = Double;

    int redBits = 8;
    int greenBits = 8;
    int blueBits = 8;
    int alphaBits = 8;

    int depthBits = 24;
    int stensilBits = 8;

    int samples;
    int interval;
};

#endif