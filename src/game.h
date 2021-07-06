#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <map>
#include <string>
#include <array>

#define BRICK_SIZE 4

namespace Game
{

    struct BrickShape
    {
        std::array<std::array<char, BRICK_SIZE>, BRICK_SIZE> shape = {0};
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

    private:
        std::vector<std::shared_ptr<sf::Texture>> textures;
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