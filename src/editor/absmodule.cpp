#include "absmodule.h"

#include <noise/module/abs.h>

AbsModule::AbsModule(QObject *parent)
    : BaseModule("Abs", new noise::module::Abs(), parent)
{

}

AbsModule::~AbsModule()
{

}
