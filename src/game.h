#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <map>
#include <string>
#include <array>

namespace Game
{

    class Scene
    {
    public:
        Scene() = default;

        virtual void update() = 0;

        std::map<std::string, std::shared_ptr<sf::Drawable>> objects;
        sf::Sprite one_sprite;

    protected:
        template <typename ShapeType, typename... ArgType>
        std::shared_ptr<ShapeType> add_shape(std::string name, ArgType... Args);

        sf::Transformable *get_transformable(std::shared_ptr<sf::Drawable> shape);
    };

    struct BrickShape
    {
        std::array<std::array<char, 4>, 4> shape = {0};
    };

    class Brick
    {
        BrickShape shape;
    };

    class Tebris : public Scene
    {
    public:
        Tebris();

        void update() override;

    private:
        std::array<BrickShape, 7> bricks;

        void initialize_bricks();

        float shape1_scale = 1.0f;
        bool shape1_dir = true;
    };

};