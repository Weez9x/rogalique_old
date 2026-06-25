#pragma once
#include "Component.h"
#include <SFML/Audio.hpp>
#include <string>

namespace EngineGame
{
class SoundComponent : public Component
{
public:
    SoundComponent(GameObject* gameObject);

    void AddSound(sf::SoundBuffer* buffer);
    // void AddSound(sf::SoundBuffer* buffer);
    void PlayNext();
    void Play();
    void SetVolume(float volume);
    void SetGroupName(const std::string& name);
    const std::string& GetGroupName() const;

    void Update(float deltaTime) override;
    void Render() override;

private:
    sf::Sound sound;
    std::vector<sf::SoundBuffer*> buffers;
    std::string groupName;
    int currentSoundIndex = 0;
};
} // namespace EngineGame