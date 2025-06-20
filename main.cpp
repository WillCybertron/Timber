#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
  RenderWindow window;
  window.create(VideoMode({800u, 600u}), "Timber!!!", State::Fullscreen);

  while (window.isOpen()) {
    while (auto event = window.pollEvent()) {
      if (event->is<Event::Closed>()) window.close();

      if (const auto* keyPressed = event->getIf<Event::KeyPressed>()) {
        if (keyPressed->code == Keyboard::Key::Escape) window.close();
      }
    }

    window.clear();
    window.display();
  }

  return 0;
}