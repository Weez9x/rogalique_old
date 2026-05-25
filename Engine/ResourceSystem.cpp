#include "pch.h"
#include "ResourceSystem.h"
#include "Logger.h"

namespace EngineGame
{
ResourceSystem* ResourceSystem::Instance()
{
    static ResourceSystem resourceSystem;
    return &resourceSystem;
}

void ResourceSystem::LoadMusic(const std::string& name, std::string sourcePath)
{
    if (musics.find(name) != musics.end())
    {
        return;
    }

    sf::Music* newMusic = new sf::Music();
    if (newMusic->openFromFile(sourcePath))
    {
        musics.emplace(name, newMusic);
    }
    else
    {
        delete newMusic;
    }
}

sf::Music* ResourceSystem::GetMusicShared(const std::string& name) const
{
    auto it = musics.find(name);

    if (it == musics.end())
    {
        throw std::runtime_error("Music not found: " + name);
    }

    return it->second;
}

void ResourceSystem::DeleteSharedMusic(const std::string& name)
{
    auto musicPair = musics.find(name);

    sf::Music* deletingMusic = musicPair->second;
    musics.erase(musicPair);
    delete deletingMusic;
}

void ResourceSystem::LoadTexture(const std::string& name, std::string sourcePath, bool isSmooth)
{
    if (textures.find(name) != textures.end())
    {
        return;
    }

    sf::Texture* newTexture = new sf::Texture();

    if (newTexture->loadFromFile(sourcePath))
    {
        newTexture->setSmooth(isSmooth);
        textures.emplace(name, newTexture);
        Logger::Instance()->Info("Texture loaded: " + name);
    }
    else
    {
        delete newTexture;

        Logger::Instance()->Error("Failed to load texture: " + sourcePath + ". Fallback texture created.");

        textures.emplace(name, CreateFallbackTexture({16, 16}, isSmooth));
    }
}
const sf::Texture* ResourceSystem::GetTextureShared(const std::string& name) const
{
    auto it = textures.find(name);

    if (it == textures.end())
    {
        throw std::runtime_error("Texture not found: " + name);
    }

    return it->second;
}
sf::Texture* ResourceSystem::GetTextureCopy(const std::string& name) const
{
    return new sf::Texture(*textures.find(name)->second);
}
void ResourceSystem::DeleteSharedTexture(const std::string& name)
{
    auto texturePair = textures.find(name);

    sf::Texture* deletingTexure = texturePair->second;
    textures.erase(texturePair);
    delete deletingTexure;
}

void ResourceSystem::LoadTextureMap(const std::string& name, std::string sourcePath, sf::Vector2u elementPixelSize,
                                    int totalElements, bool isSmooth)
{
    if (textureMaps.find(name) != textureMaps.end())
    {
        return;
    }
    if (totalElements <= 0)
    {
        Logger::Instance()->Warning("Texture map totalElements <= 0. Fallback to 1 element.");
        totalElements = 1;
    }

    auto textureMapElements = new std::vector<sf::Texture*>();

    sf::Texture textureMap;

    if (textureMap.loadFromFile(sourcePath))
    {
        auto textureSize = textureMap.getSize();
        int loadedElements = 0;

        for (int y = 0; y <= textureSize.y - elementPixelSize.y; y += elementPixelSize.y)
        {
            if (loadedElements == totalElements)
            {
                break;
            }

            for (int x = 0; x <= textureSize.x - elementPixelSize.x; x += elementPixelSize.x)
            {
                if (loadedElements == totalElements)
                {
                    break;
                }

                sf::Texture* newTextureMapElement = new sf::Texture();

                if (newTextureMapElement->loadFromFile(sourcePath,
                                                       sf::IntRect(x, y, elementPixelSize.x, elementPixelSize.y)))
                {
                    newTextureMapElement->setSmooth(isSmooth);
                    textureMapElements->push_back(newTextureMapElement);
                }
                else
                {
                    delete newTextureMapElement;
                }

                loadedElements++;
            }
        }

        EngineGame::Logger::Instance()->Info("Texture map loaded: " + name);
    }
    else
    {
        EngineGame::Logger::Instance()->Error("Failed to load texture map: " + sourcePath +
                                              ". Fallback texture map created.");

        for (int i = 0; i < totalElements; ++i)
        {
            sf::Image fallbackImage;
            fallbackImage.create(elementPixelSize.x, elementPixelSize.y, sf::Color::Magenta);

            sf::Texture* fallbackTexture = new sf::Texture();
            fallbackTexture->loadFromImage(fallbackImage);
            fallbackTexture->setSmooth(isSmooth);

            textureMapElements->push_back(fallbackTexture);
        }
    }

    textureMaps.emplace(name, *textureMapElements);
}
const sf::Texture* ResourceSystem::GetTextureMapElementShared(const std::string& name, int elementIndex) const
{
    auto it = textureMaps.find(name);

    if (it == textureMaps.end())
    {
        throw std::runtime_error("Texture map not found: " + name);
    }

    if (elementIndex < 0 || elementIndex >= it->second.size())
    {
        throw std::runtime_error("Texture map index out of range");
    }

    return it->second[elementIndex];
}
sf::Texture* ResourceSystem::GetTextureMapElementCopy(const std::string& name, int elementIndex) const
{
    auto textureMap = textureMaps.find(name);
    auto textures = textureMap->second;
    return new sf::Texture(*textures[elementIndex]);
}
int ResourceSystem::GetTextureMapElementsCount(const std::string& name) const
{
    auto textureMap = textureMaps.find(name);
    auto textures = textureMap->second;
    return textures.size();
}
void ResourceSystem::DeleteSharedTextureMap(const std::string& name)
{
    auto textureMap = textureMaps.find(name);
    auto deletingTextures = textureMap->second;

    for (int i = 0; i < deletingTextures.size(); i++)
    {
        delete deletingTextures[i];
    }

    textureMaps.erase(textureMap);
}

void ResourceSystem::Clear()
{
    DeleteAllMusics();
    DeleteAllTextures();
    DeleteAllTextureMaps();
}

sf::Texture* ResourceSystem::CreateFallbackTexture(sf::Vector2u size, bool isSmooth)
{
    if (size.x == 0 || size.y == 0)
    {
        size = {16, 16};
    }

    sf::Image image;
    image.create(size.x, size.y, sf::Color::Magenta);

    sf::Texture* texture = new sf::Texture();
    texture->loadFromImage(image);
    texture->setSmooth(isSmooth);

    return texture;
}

void ResourceSystem::DeleteAllMusics()
{
    std::vector<std::string> keysToDelete;

    for (const auto& musicPair : musics)
    {
        keysToDelete.push_back(musicPair.first);
    }

    for (const auto& key : keysToDelete)
    {
        DeleteSharedMusic(key);
    }
}

void ResourceSystem::DeleteAllTextures()
{
    std::vector<std::string> keysToDelete;

    for (const auto& texturePair : textures)
    {
        keysToDelete.push_back(texturePair.first);
    }

    for (const auto& key : keysToDelete)
    {
        DeleteSharedTexture(key);
    }
}
void ResourceSystem::DeleteAllTextureMaps()
{
    std::vector<std::string> keysToDelete;

    for (const auto& textureMapPair : textureMaps)
    {
        keysToDelete.push_back(textureMapPair.first);
    }

    for (const auto& key : keysToDelete)
    {
        DeleteSharedTextureMap(key);
    }
}
} // namespace EngineGame