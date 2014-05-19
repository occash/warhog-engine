#ifndef INFOCOMPONENT_H
#define INFOCOMPONENT_H

#include "../global.h"
#include <entityx/entityx.h>

using namespace entityx;

class ENGINE_EXPORT InfoComponent : public Component<InfoComponent>
{
public:
    InfoComponent(const std::string& n);
    ~InfoComponent();

    bool isEnabled;
    bool isStatic;
    std::string name;
    std::string tag;
    int layer;
};

#endif
