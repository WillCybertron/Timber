#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
  RenderWindow window;
  window.create(VideoMode({800u, 600u}), "Timber!!!", State::Fullscreen);

  Texture textureBackground;
  textureBackground.loadFromFile("../graphics/background.png");

  Sprite spriteBackground(textureBackground);
  spriteBackground.setPosition({0, 0});

  Texture textureTree;
  textureTree.loadFromFile("../graphics/tree.png");

  Sprite spriteTree(textureTree);
  spriteTree.setPosition({810, 0});

  while (window.isOpen()) {
    while (auto event = window.pollEvent()) {
      if (event->is<Event::Closed>()) window.close();

      if (const auto* keyPressed = event->getIf<Event::KeyPressed>()) {
        if (keyPressed->code == Keyboard::Key::Escape) window.close();
      }
    }

    window.clear();
    window.draw(spriteBackground);
    window.draw(spriteTree);
    window.display();
  }

  return 0;
}