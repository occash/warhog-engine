#include "hints.h"

#include <map>
#include <boost/preprocessor.hpp>
#include <boost/assign/list_of.hpp>

#define ENUM_TO_STRING_CASE(r, data, elem) \
    case data::elem: return BOOST_PP_STRINGIZE(elem);

#define ENUM_TO_STRING(scope, name, enumerators) \
\
    inline std::string toString(scope::name v) \
{ \
    switch (v) \
{ \
    BOOST_PP_SEQ_FOR_EACH( \
    ENUM_TO_STRING_CASE, \
    scope, \
    enumerators \
    ) \
    default: return ""; \
} \
}

template<class T>
T fromString(const std::string& c)
{
    return T();
}

#define STRING_TO_ENUM_CASE(r, data, elem) \
    (BOOST_PP_STRINGIZE(elem), data::elem)

#define STRING_TO_ENUM(scope, name, enumerators) \
    \
    std::map<std::string, scope::name> name##_map = boost::assign::map_list_of \
    BOOST_PP_SEQ_FOR_EACH(\
    STRING_TO_ENUM_CASE, \
    scope, \
    enumerators \
    ); \
    template<>\
    inline scope::name fromString<scope::name>(const std::string& c) \
    { \
    return name##_map[c]; \
    }

ENUM_TO_STRING(GLContextHints, ClientApi, (Desktop)(Embedded))
STRING_TO_ENUM(GLContextHints, ClientApi, (Desktop)(Embedded))
ENUM_TO_STRING(GLContextHints, Profile, (Any)(Core)(Compat))
STRING_TO_ENUM(GLContextHints, Profile, (Any)(Core)(Compat))
ENUM_TO_STRING(GLContextHints, Strategy, (NotRobust)(ResetNotify)(LoseOnReset))
STRING_TO_ENUM(GLContextHints, Strategy, (NotRobust)(ResetNotify)(LoseOnReset))

GLContextHints::GLContextHints()
    : api(Desktop),
    profile(Any),
    strategy(NotRobust),
    major(1),
    minor(0),
#ifdef _DEBUG || DEBUG
    debug(true),
#else
    debug(false),
#endif
    forward(false)
{
}

YAML::Emitter & operator<<(YAML::Emitter &doc, const GLContextHints& hints)
{
    doc << YAML::BeginMap;

    doc << YAML::Key << "api";
    doc << YAML::Value;
    doc << toString(hints.api);

    doc << YAML::Key << "profile";
    doc << YAML::Value;
    doc << toString(hints.profile);

    doc << YAML::Key << "strategy";
    doc << YAML::Value;
    doc << toString(hints.strategy);

    doc << YAML::Key << "version";
    doc << YAML::Value << YAML::Flow;
    doc << YAML::BeginSeq;
    doc << hints.major << hints.minor;
    doc << YAML::EndSeq;

    doc << YAML::Key << "debug";
    doc << YAML::Value << hints.debug;

    doc << YAML::Key << "forward";
    doc << YAML::Value << hints.forward;

    doc << YAML::EndMap;
    return doc;
}

void operator>>(const YAML::Node& doc, GLContextHints& hints)
{
    hints.api = fromString<GLContextHints::ClientApi>(
        doc["api"].as<std::string>());
    hints.profile = fromString<GLContextHints::Profile>(
        doc["profile"].as<std::string>());
    hints.strategy = fromString<GLContextHints::Strategy>(
        doc["strategy"].as<std::string>());

    const YAML::Node& version = doc["version"];
    hints.major = version[0].as<int>();
    hints.minor = version[1].as<int>();

    hints.debug = doc["debug"].as<bool>();
    hints.forward = doc["forward"].as<bool>();
}

GLFramebufferHints::GLFramebufferHints()
    : redBits(8),
    greenBits(8),
    blueBits(8),
    alphaBits(8),
    depthBits(24),
    stensilBits(8),
    redAccum(0),
    greenAccum(0),
    blueAccum(0),
    alphaAccum(0),
    auxBuffers(0),
    samples(0),
    refreshRate(0),
    stereo(false),
    srgb(false)
{
}

YAML::Emitter & operator<<(YAML::Emitter &doc, const GLFramebufferHints& hints)
{
    doc << YAML::BeginMap;

    doc << YAML::Key << "bits";
    doc << YAML::Value << YAML::Flow;
    doc << YAML::BeginSeq;
    doc << hints.redBits;
    doc << hints.greenBits;
    doc << hints.blueBits;
    doc << hints.alphaBits;
    doc << hints.depthBits;
    doc << hints.stensilBits;
    doc << YAML::EndSeq;

    doc << YAML::Key << "accum";
    doc << YAML::Value << YAML::Flow;
    doc << YAML::BeginSeq;
    doc << hints.redAccum;
    doc << hints.greenAccum;
    doc << hints.blueAccum;
    doc << hints.alphaAccum;
    doc << YAML::EndSeq;

    doc << YAML::Key << "aux";
    doc << YAML::Value << hints.auxBuffers;
    doc << YAML::Key << "samples";
    doc << YAML::Value << hints.samples;
    doc << YAML::Key << "refresh";
    doc << YAML::Value << hints.refreshRate;
    doc << YAML::Key << "stereo";
    doc << YAML::Value << hints.stereo;
    doc << YAML::Key << "srgb";
    doc << YAML::Value << hints.srgb;

    doc << YAML::EndMap;
    return doc;
}

void operator>>(const YAML::Node& doc, GLFramebufferHints& hints)
{
    const YAML::Node& bits = doc["bits"];
    hints.redBits = bits[0].as<int>();
    hints.greenBits = bits[1].as<int>();
    hints.blueBits = bits[2].as<int>();
    hints.alphaBits = bits[3].as<int>();
    hints.depthBits = bits[4].as<int>();
    hints.stensilBits = bits[5].as<int>();

    const YAML::Node& accum = doc["accum"];
    hints.redAccum = accum[0].as<int>();
    hints.greenAccum = accum[1].as<int>();
    hints.blueAccum = accum[2].as<int>();
    hints.alphaAccum = accum[3].as<int>();

    hints.auxBuffers = doc["aux"].as<int>();
    hints.samples = doc["samples"].as<int>();
    hints.refreshRate = doc["refresh"].as<int>();
    hints.stereo = doc["stereo"].as<bool>();
    hints.srgb = doc["srgb"].as<bool>();
}

GLWindowHints::GLWindowHints()
    : visible(false),
    resizable(false),
    decorated(true),
    width(640),
    height(480),
    title("WarHog engine"),
    fullscreen(false),
    monitor(0)
{
}

YAML::Emitter & operator<<(YAML::Emitter &doc, const GLWindowHints& hints)
{
    doc << YAML::BeginMap;

    doc << YAML::Key << "visible";
    doc << YAML::Value << hints.visible;
    doc << YAML::Key << "resizable";
    doc << YAML::Value << hints.resizable;
    doc << YAML::Key << "decorated";
    doc << YAML::Value << hints.decorated;
    doc << YAML::Key << "width";
    doc << YAML::Value << hints.width;
    doc << YAML::Key << "height";
    doc << YAML::Value << hints.height;
    doc << YAML::Key << "title";
    doc << YAML::Value << hints.title;
    doc << YAML::Key << "fullscreen";
    doc << YAML::Value << hints.fullscreen;
    doc << YAML::Key << "monitor";
    doc << YAML::Value << hints.monitor;

    doc << YAML::EndMap;

    return doc;
}

void operator>>(const YAML::Node& doc, GLWindowHints& hints)
{
    hints.visible = doc["visible"].as<bool>();
    hints.resizable = doc["resizable"].as<bool>();
    hints.decorated = doc["decorated"].as<bool>();
    hints.width = doc["width"].as<int>();
    hints.height = doc["height"].as<int>();
    hints.title = doc["title"].as<std::string>();
    hints.fullscreen = doc["fullscreen"].as<bool>();
    hints.monitor = doc["monitor"].as<int>();
}
