#include "engine.h"

#include <SFML/Graphics.hpp>

namespace Engine
{

    Renderer::Renderer(sf::RenderWindow &window)
    {
        m_window.reset(&window);
    }

    void Renderer::setup()
    {
    }

    void Renderer::loop()
    {
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);

        while (m_window->isOpen())
        {
            sf::Event event;
            while (m_window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    m_window->close();
            }

            m_window->clear();
            m_window->draw(shape);
            m_window->display();
        }
    }

};
