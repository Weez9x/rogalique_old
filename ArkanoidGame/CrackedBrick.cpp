#include "CrackedBrick.h"
#include "GameSettings.h"
#include <iostream>

namespace Arkanoid
{
    CrackedBrick::CrackedBrick(float x, float y, float width, float height, int typeIndex)
        : Brick(x, y, width, height, typeIndex)
    {
        static const std::vector<std::string> crackedNames =
        {
            "blue broken.png",
            "green broken.png",
            "yellow broken.png",
            "orange broken.png",
            "red broken.png"
        };

        int idx = typeIndex;

        if (idx < 0) idx = 0;
        if (idx >= (int)crackedNames.size())
            idx = (int)crackedNames.size() - 1;

        std::string fullPath = TEXTURES_PATH + crackedNames[idx];
        if (!crackedTexture.loadFromFile(fullPath))
        {
            std::cerr << "Failed to load cracked texture: " << fullPath << std::endl;
        }
    }

    void CrackedBrick::destroy()
    {
        hitsRemaining--;

        if (hitsRemaining == 1 && !cracked)
        {
            if (crackedTexture.getSize().x > 0)
                shape.setTexture(&crackedTexture);

            cracked = true;
        }
        else if (hitsRemaining <= 0)
        {
            active = false;
        }
    }
}
