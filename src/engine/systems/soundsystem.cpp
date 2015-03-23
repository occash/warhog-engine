#include "soundsystem.h"

using namespace entityx;

//TODO:Add Effects

SoundSystem::SoundSystem()
{
}
SoundSystem::~SoundSystem()
{
	result = system->close();
	ERRCHECK(result);
	result = system->release();
	ERRCHECK(result);
}

void  SoundSystem::createSound(SoundSource* sound_source)
{
	FMOD::Sound *sound;
	result = system->createSound("SecretGarden.mp3", FMOD_3D, 0, &sound);
	result = sound->set3DMinMaxDistance(sound_source->minDistance * distanceFactor, sound_source->maxDistance  * distanceFactor);
	ERRCHECK(result);
	result = sound->setMode(FMOD_3D_INVERSEROLLOFF);
	ERRCHECK(result);
	sound_source->setSound(sound);
}
void SoundSystem::configure(EventManager& events)
{
	events.subscribe<EntityCreatedEvent>(*this);
	events.subscribe<EntityDestroyedEvent>(*this);
	events.subscribe<ComponentAddedEvent<SoundComponent>>(*this);
	events.subscribe<ComponentRemovedEvent<SoundComponent>>(*this);
	events.subscribe<ComponentAddedEvent<ListenerComponent>>(*this);
	events.subscribe<ComponentRemovedEvent<ListenerComponent>>(*this);
	//fmod initiallisation:
	result = System_Create(&system);      // Create the main system object.
	ERRCHECK(result);
	result = system->getVersion(&version);
	ERRCHECK(result);
	if (version < FMOD_VERSION)
	{
		printf("FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION);
	}
	ERRCHECK(result);
	result = system->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	//TODO:first argument is count of max channel. To write algorithm of detect channel  count
	ERRCHECK(result);
	result = system->set3DSettings(0.0, distanceFactor, 1.0f);
	//TODO:Enable dopler effect. For it we must have velocity object. Now it disable - first argument 
	ERRCHECK(result);
}

void SoundSystem::update(EntityManager& entities, EventManager& events, double dt)
{
	//Setup sound
    auto sounds = entities.entities_with_components<SoundComponent,TransformComponent>();
	auto soundObject = sounds.begin();
	if (soundObject == sounds.end())
		return;
	auto soundCom = (*soundObject).component<SoundComponent>();
	auto soundSource = soundCom->soundSource;
	auto sound = soundSource->sound;
	auto channel = soundCom->soundSource->channel;
	glm::vec3 glmSoundPosition;
	auto soundTransform = (*soundObject).component<TransformComponent>();
	glmSoundPosition = soundTransform->position();
	soundCom->setPos(glmSoundPosition.x*distanceFactor, glmSoundPosition.y*distanceFactor, glmSoundPosition.z*distanceFactor);
	//Setup listener
	auto listeners = entities.entities_with_components<ListenerComponent, TransformComponent>();
	auto listenerObject = listeners.begin();
	if (listenerObject == listeners.end())
		return;
	auto listenerCom = (*listenerObject).component<ListenerComponent>();
	glm::vec3 glmListenerPosition;
	auto listenerTransform = (*listenerObject).component<TransformComponent>();	
	glmListenerPosition = listenerTransform->position();
	auto listener = listenerCom->listener;
	listenerCom->setPos(glmListenerPosition.x*distanceFactor, glmListenerPosition.y*distanceFactor, glmListenerPosition.z*distanceFactor);
	//Play sound:
	bool isPlaying;
	result = channel->isPlaying(&isPlaying);
	if (!isPlaying)
	{
		result = system->playSound(sound, 0, true, &channel);
	}
	result = channel->set3DAttributes(&soundSource->pos, 0);//second argument velocity is null. Need to Dopler
	ERRCHECK(result);
	result = channel->setPaused(false);
	ERRCHECK(result);
	soundCom->soundSource->channel = channel;
	ERRCHECK(result);
	result = system->set3DListenerAttributes(0, &listener->pos, 0, &listener->forward, &listener->up);
	//TODO:velocity,forward,up for listener
	ERRCHECK(result);
	result = system->update();//Update FMOD system 
	ERRCHECK(result);
}
// void RenderSystem::geometryPass(std::shared_ptr<EntityManager> entities, MatrixBlock& m)
void SoundSystem::receive(const EntityCreatedEvent& event)
{

}

void SoundSystem::receive(const EntityDestroyedEvent& event)
{

}

void SoundSystem::receive(const ComponentAddedEvent<SoundComponent>& event)
{

}

void SoundSystem::receive(const ComponentRemovedEvent<SoundComponent>& event)
{
}

void SoundSystem::receive(const ComponentAddedEvent<ListenerComponent>& event)
{
}

void SoundSystem::receive(const ComponentRemovedEvent<ListenerComponent>& event)
{
}

