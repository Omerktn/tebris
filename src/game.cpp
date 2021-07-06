#include "game.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <utility>
#include <iostream>

namespace Game
{

    template <typename ShapeType, typename... ArgType>
    std::shared_ptr<ShapeType> Scene::add_shape(std::string name, ArgType... Args)
    {
        auto shape = std::make_shared<ShapeType>(Args...);
        objects.insert({name, shape});
        return shape;
    }

    sf::Transformable *Scene::get_transformable(std::shared_ptr<sf::Drawable> shape)
    {
        return dynamic_cast<sf::Transformable *>(shape.get());
    }

    std::shared_ptr<sf::Texture> Scene::load_texture(std::string path)
    {
        auto texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile(path, sf::IntRect(0, 0, 1, 1)))
        {
            std::cerr << "Cannot load the texture: '" << path << "'\n";
        }
        textures.push_back(texture);
        return texture;
    }

    Tebris::Tebris()
    {
        initialize_bricks();

        auto yellow_texture = load_texture("../graphics/Yellow_box.png");

        Brick a_brick(brick_shapes[4], yellow_texture, sf::Vector2f(25.0f, 25.0f));

        a_brick.apply_sprite_positions();

        brick_objects.push_back(a_brick);
    }

    void Tebris::update()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            brick_objects[0].position += sf::Vector2f(0.0f, 0.1f);
            brick_objects[0].apply_sprite_positions();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            brick_objects[0].position += sf::Vector2f(0.0f, -0.1f);
            brick_objects[0].apply_sprite_positions();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            brick_objects[0].position += sf::Vector2f(0.1f, 0.0f);
            brick_objects[0].apply_sprite_positions();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            brick_objects[0].position += sf::Vector2f(-0.1f, 0.0f);
            brick_objects[0].apply_sprite_positions();
        }
    }

    Brick::Brick(BrickShape t_shape, std::shared_ptr<sf::Texture> t_texture, sf::Vector2f t_pos)
        : shape(t_shape), texture(t_texture), position(t_pos)
    {
        for (size_t i = 0; i < BRICK_SIZE; i++)
        {
            for (size_t j = 0; j < BRICK_SIZE; j++)
            {
                char cell = shape.shape[i][j];
                if (cell)
                {
                    auto sprite = sf::Sprite();
                    sprite.setTexture(*texture);
                    sprite.setScale(sf::Vector2f(single_brick_size, single_brick_size));

                    sprite.setPosition(position + sf::Vector2f(i * single_brick_size, j * single_brick_size));

                    sprites.push_back(std::move(sprite));
                }
            }
        }
    };

    void Brick::apply_sprite_positions()
    {
        size_t sprite_index = 0;

        for (size_t i = 0; i < BRICK_SIZE; i++)
        {
            for (size_t j = 0; j < BRICK_SIZE; j++)
            {
                char cell = shape.shape[i][j];
                if (cell)
                {
                    sf::Sprite &sprite = sprites[sprite_index];
                    sprite.setPosition(position + sf::Vector2f(i * single_brick_size, j * single_brick_size));
                    sprite_index++;
                }
            }
        }
    }

    void Tebris::initialize_bricks()
    {
        // Long boy
        brick_shapes[0].shape[0] = {1, 0, 0, 0};
        brick_shapes[0].shape[1] = {1, 0, 0, 0};
        brick_shapes[0].shape[2] = {1, 0, 0, 0};
        brick_shapes[0].shape[3] = {1, 0, 0, 0};
        // Square
        brick_shapes[1].shape[0] = {1, 1, 0, 0};
        brick_shapes[1].shape[1] = {1, 1, 0, 0};
        brick_shapes[1].shape[2] = {0, 0, 0, 0};
        brick_shapes[1].shape[3] = {0, 0, 0, 0};
        // L
        brick_shapes[2].shape[0] = {1, 0, 0, 0};
        brick_shapes[2].shape[1] = {1, 0, 0, 0};
        brick_shapes[2].shape[2] = {1, 1, 0, 0};
        brick_shapes[2].shape[3] = {0, 0, 0, 0};
        // Half-cross
        brick_shapes[3].shape[0] = {1, 0, 0, 0};
        brick_shapes[3].shape[1] = {1, 1, 0, 0};
        brick_shapes[3].shape[2] = {1, 0, 0, 0};
        brick_shapes[3].shape[3] = {0, 0, 0, 0};
        // Reversed L shape
        brick_shapes[4].shape[0] = {0, 1, 0, 0};
        brick_shapes[4].shape[1] = {0, 1, 0, 0};
        brick_shapes[4].shape[2] = {1, 1, 0, 0};
        brick_shapes[4].shape[3] = {0, 0, 0, 0};
        // Z to right
        brick_shapes[5].shape[0] = {0, 1, 0, 0};
        brick_shapes[5].shape[1] = {0, 1, 0, 0};
        brick_shapes[5].shape[2] = {1, 0, 0, 0};
        brick_shapes[5].shape[3] = {1, 0, 0, 0};
        // Z to left
        brick_shapes[6].shape[0] = {1, 0, 0, 0};
        brick_shapes[6].shape[1] = {1, 0, 0, 0};
        brick_shapes[6].shape[2] = {0, 1, 0, 0};
        brick_shapes[6].shape[3] = {0, 1, 0, 0};
    }

};