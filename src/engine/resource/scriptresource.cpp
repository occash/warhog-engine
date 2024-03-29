#include "scriptresource.h"

#include <sstream>

bool ScriptResource::load(std::istream& in, Object *&resource) const
{
    Script *script = new Script();

    unsigned int engineSize = 0,
                 nameSize = 0,
                 sourceSize = 0;

    in.read((char *)&engineSize, sizeof(unsigned int));
    script->engine.resize(engineSize);
    in.read(const_cast<char *>(script->engine.data()), script->engine.size());
    in.read((char *)&nameSize, sizeof(unsigned int));
    script->name.resize(nameSize);
    in.read(const_cast<char *>(script->name.data()), script->name.size());
    in.read((char *)&sourceSize, sizeof(unsigned int));
    script->source.resize(sourceSize);
    in.read(const_cast<char *>(script->source.data()), script->source.size());

    resource = script;

    return true;
}

bool ScriptResource::save(std::ostream& out, Object *resource) const
{
    const Script *script = reinterpret_cast<const Script *>(resource);

    unsigned int engineSize = script->engine.size(),
                 nameSize = script->name.size(),
                 sourceSize = script->source.size();

    out.write((char *)&engineSize, sizeof(unsigned int));
    out.write(script->engine.c_str(), script->engine.size());
    out.write((char *)&nameSize, sizeof(unsigned int));
    out.write(script->name.c_str(), script->name.size());
    out.write((char *)&sourceSize, sizeof(unsigned int));
    out.write(script->source.c_str(), script->source.size());

    return true;
}
