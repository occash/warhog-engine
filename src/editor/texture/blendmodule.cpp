#include "blendmodule.h"

BlendModule::BlendModule(QObject *parent)
    : BaseModule("Blend", new noise::module::Blend(), parent)
{

}

BlendModule::~BlendModule()
{

}
