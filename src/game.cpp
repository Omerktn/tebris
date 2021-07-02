#include "game.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <utility>

namespace Game
{

    template<typename ShapeType, typename ...ArgType>
    std::shared_ptr<ShapeType> Scene::add_shape(std::string name, ArgType...Args) {
        auto shape = std::make_shared<ShapeType>(Args...);
        objects.insert({name, shape});
        return shape;
    }

    sf::Transformable * Scene::get_transformable(std::shared_ptr<sf::Drawable> shape) {
        return dynamic_cast<sf::Transformable *>(shape.get());
    }

    Tebris::Tebris()
    {
        auto shape1 = add_shape<sf::CircleShape>("shape1", 100.f, 8);
        shape1->setFillColor(sf::Color::Yellow);
        get_transformable(shape1)->setPosition(200.f, 200.f);

        auto shape2 = add_shape<sf::CircleShape>("shape2", 100.f);
        shape2->setFillColor(sf::Color::Green);
        get_transformable(shape2)->setPosition(300.f, 200.f);

        auto shape3 = add_shape<sf::RectangleShape>("shape3", sf::Vector2f(150.f, 50.f));
        shape3->setFillColor(sf::Color::Blue);
        get_transformable(shape3)->setPosition(300.f, 300.f);

        auto shape4 = add_shape<sf::CircleShape>("shape4", 75.f);
        get_transformable(shape4)->setPosition(25.f, 25.f);
    }

    void Tebris::update()
    {
        get_transformable(objects["shape2"])->rotate(0.25f);

        get_transformable(objects["shape1"])->setScale(shape1_scale, 1.0f);

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