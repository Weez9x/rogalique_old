#include "pch.h"
#include "AudioComponent.h"

namespace EngineGame
{
AudioComponent::AudioComponent(GameObject* gameObject) : Component(gameObject) {}

void AudioComponent::Update(float deltaTime) {}

void AudioComponent::Render() {}

void AudioComponent::SetMusic(sf::Music* newMusic)
{
    music = newMusic;
}

void AudioComponent::PlayMusic(bool loop)
{
    if (music == nullptr)
    {
        return;
    }

    music->setLoop(loop);
    music->play();
}

void AudioComponent::SetVolume(float volume)
{

    if (volume < 0.f)
    {
        volume = 0.f;
    }

    if (volume > 100.f)
    {
        volume = 100.f;
    }

    if (music != nullptr)
    {
        music->setVolume(volume);
    }
}

void AudioComponent::StopMusic()
{
    if (music == nullptr)
    {
        return;
    }

    music->stop();
}
} // namespace EngineGame