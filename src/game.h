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

    protected:
        template <typename ShapeType, typename... ArgType>
        std::shared_ptr<ShapeType> add_shape(std::string name, ArgType... Args);

        sf::Transformable *get_transformable(std::shared_ptr<sf::Drawable> shape);
    };

    class Tebris : public Scene
    {
    public:
        Tebris();

        void update() override;

    private:
        float shape1_scale = 1.0f;
        bool shape1_dir = true;
    };

    struct BrickShape
    {
        std::array<std::array<int, 4>, 4> shape;
    };

};