#include <SFML/Graphics.hpp>

#include "engine.h"

int main()
{
  sf::RenderWindow window(sf::VideoMode(600, 600), "Tebris");

  Engine::Renderer renderer(window);

  renderer.setup();
  renderer.loop();

  return 0;
}
