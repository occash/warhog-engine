#include "infocomponent.h"


InfoComponent::InfoComponent(const std::string& n)
    : isEnabled(true),
    isStatic(false),
    name(n),
    tag("untagged"),
    layer(0)
{
}

InfoComponent::~InfoComponent()
{
}
