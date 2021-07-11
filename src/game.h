#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <array>
#include <chrono>

#define BRICK_SIZE 4

namespace Game
{

    class Timer
    {
    public:
        Timer() = delete;
        Timer(int period_ms);

        void restart();
        bool is_finished();

        void change_period(int new_period_ms);

    private:
        int m_period_ms;

        std::chrono::milliseconds last_period_started;
    };

    class BrickShape
    {
    public:
        std::array<std::array<char, BRICK_SIZE>, BRICK_SIZE> shape = {0};
        size_t height;
        size_t width;

        void rotate_clockwise();
        void calculate_height_and_width();
        void align_to_upper_left();

    private:
        void slide_left();
        void slide_up();
    };

    class Brick
    {
    public:
        Brick() = delete;
        Brick(BrickShape t_shape, std::shared_ptr<sf::Texture> t_texture, sf::Vector2f t_pos);

        BrickShape shape;
        std::shared_ptr<sf::Texture> texture;
        sf::Vector2f position;
        std::vector<sf::Sprite> sprites;

        void apply_sprite_positions();

        void move_right();
        void move_left();
        void move_up();
        void move_down();

    private:
        constexpr static const float single_brick_size = 50.0f;
    };

    class Scene
    {
    public:
        Scene() = default;

        virtual void update() = 0;

        std::map<std::string, std::shared_ptr<sf::Drawable>> objects;
        std::vector<Brick> brick_objects;

    protected:
        template <typename ShapeType, typename... ArgType>
        std::shared_ptr<ShapeType> add_shape(std::string name, ArgType... Args);

        sf::Transformable *get_transformable(std::shared_ptr<sf::Drawable> shape);

        std::shared_ptr<sf::Texture> load_texture(std::string path);

        bool is_key_listenable(sf::Keyboard::Key key, int delay_ms = default_delay_ms);

    private:
        std::vector<std::shared_ptr<sf::Texture>> textures;

        std::unordered_map<sf::Keyboard::Key, Timer> key_timers;
        constexpr static int default_delay_ms = 125;
    };

    class Tebris : public Scene
    {
    public:
        Tebris();

        void update() override;

    private:
        std::array<BrickShape, 7> brick_shapes;

        void initialize_bricks();

        const float single_brick_size = 50.0f;

        float shape1_scale = 1.0f;
        bool shape1_dir = true;
    };

};