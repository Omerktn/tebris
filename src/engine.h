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

        void attach_game(std::unique_ptr<Game::Tebris> tebris);

    private:
        std::unique_ptr<sf::RenderWindow> m_window;
        std::unique_ptr<Game::Tebris> m_game;
    };

};
