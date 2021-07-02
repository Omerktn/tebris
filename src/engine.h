#pragma once

#include "game.h"

#include <SFML/Graphics.hpp>
#include <memory>

namespace Engine
{

    class Renderer
    {
    public:
        Renderer(std::unique_ptr<sf::RenderWindow> window);

        void setup();
        void loop();

        void attach_scene(std::shared_ptr<Game::Scene> tebris);

    private:
        std::unique_ptr<sf::RenderWindow> m_window;
        std::shared_ptr<Game::Scene> m_game;
    };

};
