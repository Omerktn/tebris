#include "engine.h"
#include "game.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

int main()
{
  auto window = std::make_unique<sf::RenderWindow>(sf::VideoMode(600, 600), "Tebris");

  Engine::Renderer renderer(std::move(window));

  auto game = std::make_shared<Game::Tebris>();
  renderer.attach_scene(game);

  renderer.setup();
  renderer.loop();

  return 0;
}
