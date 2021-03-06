#include "game.h"
#include "engine.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <chrono>

#define KEY_PRESSED(key) sf::Keyboard::isKeyPressed(sf::Keyboard::key)

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

        Brick a_brick(brick_shapes[3], yellow_texture, sf::Vector2f(50.0f, 50.0f));
        a_brick.apply_sprite_positions();
        brick_objects.push_back(a_brick);

        current_brick = brick_objects.begin();
    }

    void Tebris::update()
    {
        if ((KEY_PRESSED(Down) || KEY_PRESSED(S)) && is_key_listenable(sf::Keyboard::Down))
        {
            current_brick->move_down();
            current_brick->apply_sprite_positions();
        }
        else if ((KEY_PRESSED(Up) || KEY_PRESSED(W)) && is_key_listenable(sf::Keyboard::Up))
        {
            current_brick->move_up();
            current_brick->apply_sprite_positions();
        }

        if ((KEY_PRESSED(Right) || KEY_PRESSED(D)) && is_key_listenable(sf::Keyboard::Right))
        {
            current_brick->move_right();
            current_brick->apply_sprite_positions();
        }
        else if ((KEY_PRESSED(Left) || KEY_PRESSED(A)) && is_key_listenable(sf::Keyboard::Left))
        {
            current_brick->move_left();
            current_brick->apply_sprite_positions();
        }

        if (KEY_PRESSED(R) && is_key_listenable(sf::Keyboard::R, 200))
        {
            current_brick->shape.rotate_clockwise();
            current_brick->apply_sprite_positions();
        }
    }

    bool Scene::is_key_listenable(sf::Keyboard::Key key, int delay_ms)
    {
        auto it = key_timers.find(key);

        if (it == key_timers.end())
        {
            key_timers.insert({key, Timer(delay_ms)});
            return true;
        }

        auto &timer = it->second;
        if (timer.is_finished())
        {
            timer.restart();
            return true;
        }

        return false;
    }

    Brick::Brick(BrickShape t_shape, std::shared_ptr<sf::Texture> t_texture, sf::Vector2f t_pos)
        : shape(t_shape), texture(t_texture), position(t_pos)
    {
        for (size_t i = 0; i < BRICK_MATRIX_SIZE; i++)
        {
            for (size_t j = 0; j < BRICK_MATRIX_SIZE; j++)
            {
                char cell = shape.shape[i][j];
                if (cell)
                {
                    auto sprite = sf::Sprite();
                    sprite.setTexture(*texture);
                    sprite.setScale(sf::Vector2f(single_brick_size, single_brick_size));
                    sprite.setPosition(position + sf::Vector2f(j * single_brick_size, i * single_brick_size));

                    sprites.push_back(std::move(sprite));
                }
            }
        }
    };

    void Brick::debug_print_pos()
    {
        std::cout << "Position X: " << position.x << "  Y: " << position.y
                  << "  --  Width:" << shape.width << "  Height:" << shape.height << '\n';
    }

    void Brick::move_right()
    {
        auto new_position = position + sf::Vector2f(single_brick_size, 0.0f);
        if (new_position.x + (shape.width * single_brick_size) > right_border)
            return;

        position = new_position;
        debug_print_pos();
    }

    void Brick::move_left()
    {
        auto new_position = position + sf::Vector2f(-single_brick_size, 0.0f);
        if (new_position.x < left_border)
            return;

        position = new_position;
        debug_print_pos();
    }

    void Brick::move_up()
    {
        auto new_position = position + sf::Vector2f(0.0f, -single_brick_size);
        if (new_position.y < upper_border)
            return;

        position = new_position;
        debug_print_pos();
    }

    void Brick::move_down()
    {
        auto new_position = position + sf::Vector2f(0.0f, single_brick_size);
        if (new_position.y + (shape.height * single_brick_size) > lower_border)
            return;

        position = new_position;
        debug_print_pos();
    }

    void Brick::apply_sprite_positions()
    {
        size_t sprite_index = 0;

        for (size_t i = 0; i < BRICK_MATRIX_SIZE; i++)
        {
            for (size_t j = 0; j < BRICK_MATRIX_SIZE; j++)
            {
                char cell = shape.shape[i][j];
                if (cell)
                {
                    sf::Sprite &sprite = sprites[sprite_index];
                    sprite.setPosition(position + sf::Vector2f(j * single_brick_size, i * single_brick_size));
                    sprite_index++;
                }
            }
        }
    }

    void BrickShape::rotate_clockwise()
    {
        for (int i = 0; i < BRICK_MATRIX_SIZE / 2; i++)
        {
            for (int j = i; j < BRICK_MATRIX_SIZE - i - 1; j++)
            {
                int temp = shape[i][j];
                shape[i][j] = shape[BRICK_MATRIX_SIZE - 1 - j][i];
                shape[BRICK_MATRIX_SIZE - 1 - j][i] = shape[BRICK_MATRIX_SIZE - 1 - i][BRICK_MATRIX_SIZE - 1 - j];
                shape[BRICK_MATRIX_SIZE - 1 - i][BRICK_MATRIX_SIZE - 1 - j] = shape[j][BRICK_MATRIX_SIZE - 1 - i];
                shape[j][BRICK_MATRIX_SIZE - 1 - i] = temp;
            }
        }

        align_to_upper_left();

        size_t height_tmp = height;
        height = width;
        width = height_tmp;
    }

    void BrickShape::slide_left()
    {
        for (size_t j = 0; j < BRICK_MATRIX_SIZE - 1; j++)
        {
            for (size_t i = 0; i < BRICK_MATRIX_SIZE; i++)
            {
                shape[i][j] = shape[i][j + 1];
            }
        }

        for (size_t i = 0; i < BRICK_MATRIX_SIZE; i++)
        {
            shape[i][BRICK_MATRIX_SIZE - 1] = 0;
        }
    }

    void BrickShape::slide_up()
    {
        for (size_t i = 0; i < BRICK_MATRIX_SIZE - 1; i++)
        {
            for (size_t j = 0; j < BRICK_MATRIX_SIZE; j++)
            {
                shape[i][j] = shape[i + 1][j];
            }
        }

        for (size_t j = 0; j < BRICK_MATRIX_SIZE; j++)
        {
            shape[BRICK_MATRIX_SIZE - 1][j] = 0;
        }
    }

    void BrickShape::align_to_upper_left()
    {
        // Align to left
        size_t i = 0;
        while (true)
        {
            if (shape[i][0])
            {
                break;
            }

            if (i == BRICK_MATRIX_SIZE - 1)
            {
                slide_left();
                i = 0;
            }
            else
            {
                ++i;
            }
        }

        // Align to upper
        size_t j = 0;
        while (true)
        {
            if (shape[0][j])
            {
                break;
            }

            if (j == BRICK_MATRIX_SIZE - 1)
            {
                slide_up();
                j = 0;
            }
            else
            {
                ++j;
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
        brick_shapes[5].shape[1] = {1, 1, 0, 0};
        brick_shapes[5].shape[2] = {1, 0, 0, 0};
        brick_shapes[5].shape[3] = {0, 0, 0, 0};
        // Z to left
        brick_shapes[6].shape[0] = {1, 0, 0, 0};
        brick_shapes[6].shape[1] = {1, 1, 0, 0};
        brick_shapes[6].shape[2] = {0, 1, 0, 0};
        brick_shapes[6].shape[3] = {0, 0, 0, 0};

        brick_shapes[0].calculate_height_and_width();
        brick_shapes[1].calculate_height_and_width();
        brick_shapes[2].calculate_height_and_width();
        brick_shapes[3].calculate_height_and_width();
        brick_shapes[4].calculate_height_and_width();
        brick_shapes[5].calculate_height_and_width();
        brick_shapes[6].calculate_height_and_width();
    }

    void BrickShape::calculate_height_and_width()
    {
        height = 0;
        width = 0;

        bool keep_looking = true;
        for (int i = BRICK_MATRIX_SIZE - 1; i >= 0 && keep_looking; --i)
        {
            for (int j = BRICK_MATRIX_SIZE - 1; j >= 0 && keep_looking; --j)
            {
                if (shape[i][j])
                {
                    height = i + 1;
                    keep_looking = false;
                }
            }
        }

        keep_looking = true;
        for (int j = BRICK_MATRIX_SIZE - 1; j >= 0 && keep_looking; --j)
        {
            for (int i = BRICK_MATRIX_SIZE - 1; i >= 0 && keep_looking; --i)
            {
                if (shape[i][j])
                {
                    width = j + 1;
                    keep_looking = false;
                }
            }
        }
    }

    Timer::Timer(int period_ms) : m_period_ms(period_ms)
    {
        using namespace std::chrono;
        last_period_started = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    }

    void Timer::restart()
    {
        using namespace std::chrono;
        last_period_started = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    }

    bool Timer::is_finished()
    {
        using namespace std::chrono;
        const auto now_t = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

        if ((now_t - last_period_started) > std::chrono::milliseconds(m_period_ms))
        {
            return true;
        }

        return false;
    }

    void Timer::change_period(int new_period_ms)
    {
        m_period_ms = new_period_ms;
        restart();
    }
};