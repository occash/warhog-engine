#include "soundsystem.h"
#include <glm/gtx/rotate_vector.hpp>

using namespace entityx;

//TODO:Add Effects


FMOD_VECTOR SoundSystem::convertToFMODVector(glm::vec3 v)
{
    FMOD_VECTOR fmodVect = { v.x, v.y, v.z };
    return fmodVect;
}
SoundSystem::SoundSystem()
{
}
SoundSystem::~SoundSystem()
{
    result = _system->close();
    ERRCHECK(result);
    result = _system->release();
    ERRCHECK(result);
}


void  SoundSystem::createSound(SoundSource *sound_source)
{
    FMOD::Sound *sound;
    result = _system->createSound("SecretGarden.mp3", FMOD_3D, 0, &sound);
    result = sound->set3DMinMaxDistance(sound_source->getMinDistance(), 0.0f);
    ERRCHECK(result);
    result = sound->setMode(FMOD_3D_INVERSEROLLOFF);
    ERRCHECK(result);
    sound_source->setSound(sound);
}
void SoundSystem::configure(EventManager& events)
{
    //fmod initiallisation:
    result = System_Create(&_system);      // Create the main system object.
    ERRCHECK(result);
    result = _system->getVersion(&version);
    ERRCHECK(result);
    if (version < FMOD_VERSION)
        printf("FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION);
    ERRCHECK(result);
    result = _system->init(512, FMOD_INIT_3D_RIGHTHANDED | FMOD_INIT_VOL0_BECOMES_VIRTUAL, 0);    // Initialize FMOD.
    //TODO:first argument is count of max channel. To write algorithm of detect channel  count
    ERRCHECK(result);
    result = _system->set3DSettings(0.0, 1.0f, 1.0f);
    //TODO:Enable dopler effect. For it we must have velocity object. Now it disable - first argument
    ERRCHECK(result);
}

void SoundSystem::update(EntityManager& entities, EventManager& events, double dt)
{
    //Setup sound
    auto sounds = entities.entities_with_components<SoundComponent, TransformComponent>();
    auto soundObject = sounds.begin();
    if (soundObject == sounds.end())
        return;
    auto soundCom = (*soundObject).component<SoundComponent>();
    auto soundSource = soundCom->getSoundSource();
    auto sound = soundSource->getSound();
    auto channel = soundSource->getChannel();
    glm::vec3 glmSoundPosition;
    auto soundTransform = (*soundObject).component<TransformComponent>();
    glmSoundPosition = soundTransform->position();
    soundCom->setPos(glmSoundPosition);
    //Setup listener
    auto listeners = entities.entities_with_components<ListenerComponent, TransformComponent>();
    auto listenerObject = listeners.begin();
    if (listenerObject == listeners.end())
        return;
    auto listenerCom = (*listenerObject).component<ListenerComponent>();
    glm::vec3 glmListenerPosition;
    auto listenerTransform = (*listenerObject).component<TransformComponent>();
    glmListenerPosition = listenerTransform->position();
    //auto listener = listenerCom->listener;
    listenerCom->setPos(glmListenerPosition);
    //Play sound:
    bool isPlaying;
    result = channel->isPlaying(&isPlaying);
    if (!isPlaying)
        result = _system->playSound(sound, 0, true, &channel);
    FMOD_VECTOR soundPos = convertToFMODVector(soundCom->getPos());
    result = channel->set3DAttributes(&soundPos, 0);//second argument velocity is null. Need to Dopler
    ERRCHECK(result);
    result = channel->setPaused(false);
    ERRCHECK(result);
    soundCom->getSoundSource()->setChannel(channel);
    ERRCHECK(result);
    FMOD_VECTOR listenerPos = convertToFMODVector(listenerCom->getPos());
    glm::vec3 glmListenerForward = listenerCom->getForward();
    glm::vec3 glmListenerUp = listenerCom->getUp();
    glmListenerForward = listenerTransform->rotateVector(glmListenerForward);
    glmListenerUp = listenerTransform->rotateVector(glmListenerUp);
    //glmListenerForward = glm::rotate()
    FMOD_VECTOR listenerForward = convertToFMODVector(glmListenerForward);
    FMOD_VECTOR listenerUp = convertToFMODVector(glmListenerUp);
    result = _system->set3DListenerAttributes(0, &listenerPos, 0, &listenerForward, &listenerUp);
    //TODO:velocity,forward,up for listener
    ERRCHECK(result);
    result = _system->update();//Update FMOD system
    ERRCHECK(result);
}
