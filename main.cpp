#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int main() {
  RenderWindow window;
  window.create(VideoMode({800u, 600u}), "Timber!!!", State::Fullscreen);

  Texture textureBackground;
  if (!textureBackground.loadFromFile("../graphics/background.png")) {
    std::cerr << "Failed to load background.png\n";
    return 1;
  }
  Sprite spriteBackground(textureBackground);
  spriteBackground.setPosition({0, 0});

  Texture textureTree;
  if (!textureTree.loadFromFile("../graphics/tree.png")) {
    std::cerr << "Failed to load tree.png\n";
    return 1;
  }

  Sprite spriteTree(textureTree);
  spriteTree.setPosition({810, 0});

  Texture textureBee;
  if (!textureBee.loadFromFile("../graphics/bee.png")) {
    std::cerr << "Failed to load bee.png\n";
    return 1;
  }

  Sprite spriteBee(textureBee);
  spriteBee.setTexture(textureBee);
  spriteBee.setPosition({0, 800});

  bool beeActive{false};
  float beeSpeed{0.0f};

  Texture textureCloud;
  if (!textureCloud.loadFromFile("../graphics/cloud.png")) {
    std::cerr << "Failed to load cloud.png\n";
    return 1;
  }

  Sprite spriteCloud1(textureCloud);
  Sprite spriteCloud2(textureCloud);
  Sprite spriteCloud3(textureCloud);

  spriteCloud1.setTexture(textureCloud);
  spriteCloud2.setTexture(textureCloud);
  spriteCloud3.setTexture(textureCloud);

  spriteCloud1.setPosition({0, 0});
  spriteCloud2.setPosition({200, 250});
  spriteCloud3.setPosition({0, 500});

  bool cloud1Active{false};
  bool cloud2Active{false};
  bool cloud3Active{false};

  float cloud1Speed{0.0f};
  float cloud2Speed{0.0f};
  float cloud3Speed{0.0f};

  while (window.isOpen()) {
    while (auto event = window.pollEvent()) {
      if (event->is<Event::Closed>()) window.close();

      if (const auto* keyPressed = event->getIf<Event::KeyPressed>()) {
        if (keyPressed->code == Keyboard::Key::Escape) window.close();
      }
    }

    window.clear();
    window.draw(spriteBackground);
    window.draw(spriteCloud1);
    window.draw(spriteCloud2);
    window.draw(spriteCloud3);
    window.draw(spriteTree);
    window.draw(spriteBee);
    window.display();
  }

  return 0;
}