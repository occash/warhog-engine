#include "basemodule.h"

class ModuleChecker : public noise::module::Module
{
public:
    ModuleChecker(noise::module::Module *m)
        : noise::module::Module(0),
          _valid(true)
    {
        //Null pointer is not valid
        if (!m)
        {
            _valid = false;
            return;
        }

        _valid = checkSources(m);
    }

    double GetValue(double x, double y, double z) const { return 0.0; }
    int GetSourceModuleCount() const { return 0; }

    operator bool() const { return _valid; }

    bool checkSources(noise::module::Module *m) const
    {
        bool ok = true;
        const noise::module::Module **sources =
            m->*(&ModuleChecker::m_pSourceModule);

        int srcNum = m->GetSourceModuleCount();
        for (int i = 0; i < srcNum; ++i)
        {
            if (!sources[i])
                return false;

            ok &= checkSources(const_cast<noise::module::Module *>(sources[i]));
        }

        return ok;
    }

private:
    bool _valid;
};

BaseModule::BaseModule(QString name, noise::module::Module *module, QObject *parent)
    : QObject(parent),
      _name(name),
      _module(module),
      _sources(module->GetSourceModuleCount(), nullptr)
{
}

BaseModule::~BaseModule()
{
    delete _module;
}

BaseModule *BaseModule::source(int id) const
{
    return _sources[id];
}

void BaseModule::setSource(int id, BaseModule *source)
{
    noise::module::Module *m = module();
    if (source)
    {
        noise::module::Module& sm = *source->module();
        m->SetSourceModule(id, sm);
        _sources[id] = source;
    }
    else
    {
        noise::module::Module *pm = nullptr;
        noise::module::Module& sm = *pm;
        m->SetSourceModule(id, sm);
        _sources[id] = nullptr;
    }
}

bool BaseModule::isValid() const
{
    return ModuleChecker(module());
}

QString BaseModule::name() const
{
    return _name;
}

noise::module::Module *BaseModule::module() const
{
    return _module;
}
