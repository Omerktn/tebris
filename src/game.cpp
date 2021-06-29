#include "game.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <utility>

namespace Game
{

    Tebris::Tebris()
    {
        auto shape3 = std::make_unique<sf::CircleShape>(100.f, 8);
        shape3->setFillColor(sf::Color::Yellow);
        dynamic_cast<sf::Transformable *>(shape3.get())->setPosition(200.f, 200.f);
        objects.insert({"shape3", std::move(shape3)});

        auto shape1 = std::make_unique<sf::CircleShape>(100.f);
        shape1->setFillColor(sf::Color::Green);
        dynamic_cast<sf::Transformable *>(shape1.get())->setPosition(300.f, 200.f);
        objects.insert({"shape1", std::move(shape1)});

        auto shape2 = std::make_unique<sf::RectangleShape>(sf::Vector2f(150.f, 50.f));
        shape2->setFillColor(sf::Color::Blue);
        dynamic_cast<sf::Transformable *>(shape2.get())->setPosition(300.f, 300.f);
        objects.insert({"shape2", std::move(shape2)});
    }

    void Tebris::update()
    {
        dynamic_cast<sf::Transformable *>(objects["shape2"].get())->rotate(0.25f);

        dynamic_cast<sf::Transformable *>(objects["shape1"].get())->setScale(shape1_scale, 1.0f);

        if (shape1_dir)
            shape1_scale += 0.001f;
        else
            shape1_scale -= 0.001f;

        if (shape1_scale >= 2.0f || shape1_scale <= -2.0f)
        {
            shape1_dir = !shape1_dir;
        }
    }

};