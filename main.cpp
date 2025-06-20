#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
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
  spriteBee.setPosition({0, 800});

  bool beeActive{false};
  float beeSpeed{0.0f};

  Texture textureCloud;
  if (!textureCloud.loadFromFile("../graphics/cloud.png")) {
    std::cerr << "Failed to load cloud.png\n";
    return 1;
  }

  Sprite spriteClouds[3] = {Sprite(textureCloud), Sprite(textureCloud),
                            Sprite(textureCloud)};
  spriteClouds[0].setPosition({0, 0});
  spriteClouds[1].setPosition({200, 250});
  spriteClouds[2].setPosition({0, 500});

  bool cloudActive[3] = {false, false, false};
  float cloudSpeed[3] = {0.0f, 0.0f, 0.0f};

  // Different height ranges for each cloud
  int heightRanges[3][2] = {{0, 150}, {-150, 150}, {-150, 300}};

  Clock clock;

  // Seed random number generator once
  srand(static_cast<unsigned>(time(0)));

  while (window.isOpen()) {
    while (auto event = window.pollEvent()) {
      if (event->is<Event::Closed>()) {
        window.close();
      }

      if (const auto* keyPressed = event->getIf<Event::KeyPressed>()) {
        if (keyPressed->code == Keyboard::Key::Escape) {
          window.close();
        }
      }
    }

    Time dt = clock.restart();

    if (!beeActive) {
      // How fast the bee moves
      beeSpeed = (rand() % 200) + 200;
      // How high the bee flies
      float height = static_cast<float>(rand() % 500) + 500;
      spriteBee.setPosition({2000, height});
      beeActive = true;
    } else {
      // Move the bee
      spriteBee.setPosition(
          {spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),
           spriteBee.getPosition().y});

      if (spriteBee.getPosition().x < -100) {
        beeActive = false;
      }
    }

    // Update clouds
    for (int i = 0; i < 3; i++) {
      if (!cloudActive[i]) {
        // How fast is the cloud
        cloudSpeed[i] = (rand() % 200);
        // How high is the cloud
        float height = (rand() % (heightRanges[i][1] - heightRanges[i][0])) +
                       heightRanges[i][0];
        spriteClouds[i].setPosition({-200, height});
        cloudActive[i] = true;
      } else {
        spriteClouds[i].setPosition(
            {spriteClouds[i].getPosition().x + (cloudSpeed[i] * dt.asSeconds()),
             spriteClouds[i].getPosition().y});
        // Has the cloud reached the right hand edge of the screen?
        if (spriteClouds[i].getPosition().x > 1920) {
          // Set it up ready to be a whole new cloud next frame
          cloudActive[i] = false;
        }
      }
    }

    window.clear();
    window.draw(spriteBackground);
    window.draw(spriteClouds[0]);
    window.draw(spriteClouds[1]);
    window.draw(spriteClouds[2]);
    window.draw(spriteTree);
    window.draw(spriteBee);
    window.display();
  }

  return 0;
}