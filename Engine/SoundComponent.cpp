#include "pch.h"
#include "SoundComponent.h"
#include "Logger.h"

namespace EngineGame
{
SoundComponent::SoundComponent(GameObject* gameObject) : Component(gameObject) {}

void SoundComponent::AddSound(sf::SoundBuffer* buffer)
{
    if (buffer == nullptr)
    {
        Logger::Instance()->Warning("SoundComponent: buffer is null");
        return;
    }

    buffers.push_back(buffer);
}
void SoundComponent::PlayNext()
{
    if (buffers.empty())
    {
        Logger::Instance()->Warning("SoundComponent: no sounds to play");
        return;
    }

    sound.setBuffer(*buffers[currentSoundIndex]);
    sound.play();

    currentSoundIndex = (currentSoundIndex + 1) % buffers.size();
}
void SoundComponent::Play()
{
    sound.play();
}
void SoundComponent::SetVolume(float volume)
{
    sound.setVolume(volume);
}
void SoundComponent::SetGroupName(const std::string& name)
{
    groupName = name;
}
const std::string& SoundComponent::GetGroupName() const
{
    return groupName;
}
void SoundComponent::Update(float deltaTime) {}
void SoundComponent::Render() {}
} // namespace EngineGame