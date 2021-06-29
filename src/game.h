#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <map>
#include <string>

namespace Game
{

    class Tebris
    {
    public:
        Tebris();

        void update();

        std::map<std::string, std::unique_ptr<sf::Drawable>> objects;

    private:
        float shape1_scale = 1.0f;
        bool shape1_dir = true;
    };

};