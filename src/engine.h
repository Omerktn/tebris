#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

namespace Engine {

class Renderer {
public:
    Renderer(sf::RenderWindow& window);

    void setup();
    void loop();
    
private:
    std::unique_ptr<sf::RenderWindow> m_window;
};

};
