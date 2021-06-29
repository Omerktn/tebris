#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

namespace Game {

class Tebris {
public:
    Tebris();

    void update();

    std::vector<std::unique_ptr<sf::Drawable>> objects;

private:
    
};

};