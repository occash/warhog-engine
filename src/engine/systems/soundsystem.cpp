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

    result = _system->release();

}


void  SoundSystem::createSound(SoundSource *soundSource)
{
    FMOD::Sound *sound;
    FMOD::Channel *channel;
    char *fileName = soundSource->getFileName();
    result = _system->createSound(fileName, FMOD_3D, 0, &sound);
    result = sound->set3DMinMaxDistance(soundSource->getMinDistance(), 0.0f);

    result = sound->setMode(FMOD_3D_INVERSEROLLOFF);
    result = _system->playSound(sound, 0, true, &channel);

    soundSource->setSound(sound);
    soundSource->setChannel(channel);
}
void SoundSystem::configure(EventManager& events)
{
    //fmod initiallisation:
    result = System_Create(&_system);      // Create the main system object.

    result = _system->getVersion(&version);

    if (version < FMOD_VERSION)
        printf("FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION);

    result = _system->init(512, FMOD_INIT_3D_RIGHTHANDED | FMOD_INIT_VOL0_BECOMES_VIRTUAL, 0);    // Initialize FMOD.
    //TODO:first argument is count of max channel. To write algorithm of detect channel  count

    result = _system->set3DSettings(0.0, 1.0f, 1.0f);
    //TODO:Enable dopler effect. For it we must have velocity object. Now it disable - first argument

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
    if (soundSource->isPlaying())
    {
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
        bool isChannelPlaying;
        bool isLooping = soundSource->isLooping();
        result = channel->isPlaying(&isChannelPlaying);
        if (isLooping && !isChannelPlaying)
            result = _system->playSound(sound, 0, true, &channel);
        FMOD_VECTOR soundPos = convertToFMODVector(soundCom->getPos());
        result = channel->set3DAttributes(&soundPos, 0);//second argument velocity is null. Need to Dopler

        result = channel->setPaused(false);
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
    }
    else
        channel->setPaused(true);
    soundCom->getSoundSource()->setChannel(channel);
    result = _system->update();//Update FMOD system
}
