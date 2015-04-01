#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H
#include <entityx/System.h>
#include  <fmod/fmod.hpp>
#include <map>
#include "../components/soundcomponent.h"
#include "../components/listenercomponent.h"
#include "../components/transformcomponent.h"
#include "../soundsource.h"

struct SoundInfo;

class SoundSystem : public entityx::System<SoundSystem>,
    public entityx::Receiver<SoundSystem>
{
private:
    FMOD::System *_system = NULL;
    unsigned int version;//installed version FMOD
    FMOD_VECTOR convertToFMODVector(glm::vec3 v);
public:
    SoundSystem();
    ~SoundSystem();

    FMOD_RESULT result;//for error_code
    void createSound(SoundSource *soundSource);
    void configure(entityx::EventManager& events) override;
    void update(entityx::EntityManager& entities,
                entityx::EventManager& events, double dt) override;
};
#endif
