#ifndef HINTS_H
#define HINTS_H

#include "global.h"

#include <string>
#include <yaml-cpp/yaml.h>

struct ENGINE_EXPORT GLContextHints
{
    GLContextHints();

    enum ClientApi {
        Desktop = 0x00030001,
        Embedded = 0x00030002
    };
    enum Profile {
        Any = 0,
        Core = 0x00032001,
        Compat = 0x00032002
    };
    enum Strategy {
        NotRobust = 0,
        ResetNotify = 0x00031001,
        LoseOnReset = 0x00031002
    };

public:
    ClientApi api;
    Profile profile;
    Strategy strategy;
    int major;
    int minor;
    bool debug;
    bool forward;

};

YAML::Emitter & operator<<(YAML::Emitter &doc, const GLContextHints& hints);
void operator>> (const YAML::Node& node, GLContextHints& hints);

struct ENGINE_EXPORT GLFramebufferHints
{
    GLFramebufferHints();

    int redBits;
    int greenBits;
    int blueBits;
    int alphaBits;

    int depthBits;
    int stensilBits;

    int redAccum;
    int greenAccum;
    int blueAccum;
    int alphaAccum;

    int auxBuffers;
    int samples;
    int refreshRate;

    bool stereo;
    bool srgb;
};

YAML::Emitter & operator<<(YAML::Emitter &doc, const GLFramebufferHints& hints);
void operator>> (const YAML::Node& node, GLFramebufferHints& hints);

struct ENGINE_EXPORT GLWindowHints
{
    GLWindowHints();

    bool visible;
    bool resizable;
    bool decorated;

    int width;
    int height;
    std::string title;
    bool fullscreen;
    int monitor;
};

YAML::Emitter & operator<<(YAML::Emitter &doc, const GLWindowHints& hints);
void operator>> (const YAML::Node& node, GLWindowHints& hints);

#endif