#include "game.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

namespace Game
{

    Tebris::Tebris()
    {
        std::unique_ptr<sf::CircleShape> shape1 = std::make_unique<sf::CircleShape>(100.f);
        shape1->setFillColor(sf::Color::Green);
        objects.push_back(std::move(shape1));
    }

    void Tebris::update()
    {
    }

};