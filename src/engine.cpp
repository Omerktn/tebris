#include "engine.h"

#include <SFML/Graphics.hpp>
#include <iostream>

namespace Engine
{

    Renderer::Renderer(std::unique_ptr<sf::RenderWindow> window)
    {
        m_window = std::move(window);
    }

    void Renderer::setup()
    {
    }

    void Renderer::loop()
    {
        while (m_window->isOpen())
        {
            sf::Event event;
            while (m_window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    m_window->close();
            }

            m_window->clear();

            for (auto &object : m_game->objects)
            {
                m_window->draw(*(object.second));
            }

            m_game->update();
            m_window->display();
        }
    }

    void Renderer::attach_game(std::unique_ptr<Game::Tebris> tebris)
    {
        m_game = std::move(tebris);
    }

};
