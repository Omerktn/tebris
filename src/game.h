#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

namespace Game
{

    class Tebris
    {
    public:
        Tebris();

        void update();

        std::vector<std::unique_ptr<sf::Drawable>> objects;

    private:
        float shape1_scale = 1.0f;
        bool shape1_dir = true;
    };

};