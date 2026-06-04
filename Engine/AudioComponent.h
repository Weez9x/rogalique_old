#pragma once
#include "Component.h"
#include <SFML/Audio.hpp>
#include <string>

namespace EngineGame
{
class AudioComponent : public Component
{
public:
    AudioComponent(GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

    void SetMusic(sf::Music* newMusic);
    void PlayMusic(bool loop = false);
    void StopMusic();

private:
    // Music is owned by ResourceSystem; this component only controls playback.
    sf::Music* music = nullptr;
};
} // namespace EngineGame
