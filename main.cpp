#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>

using namespace sf;
using namespace std;

// Function declartions
void updateBranches(int seed);
const int NUM_BRANCHES{6};
std::unique_ptr<Sprite> branches[NUM_BRANCHES];

// Where is the player/branch?
//  Left or Right?

enum class side { Left, Right, None };
side branchPositions[NUM_BRANCHES];

int main() {
  RenderWindow window;
  window.create(VideoMode({1920u, 1080u}), "Timber!!!", State::Fullscreen);

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

  // Time Bar
  RectangleShape timeBar;
  float timeBarStartWidth{400.0f};
  float timeBarHeight{125.0f};
  timeBar.setSize(Vector2(timeBarStartWidth, timeBarHeight));
  timeBar.setFillColor(Color::Red);
  timeBar.setPosition(
      {1920 / 2.0f - timeBarStartWidth / 2.0f, 1080 - timeBarHeight - 20});
  Time gameTimeTotal;
  float timeRemaining{6.0f};
  float timeBarWidthPerSecond{timeBarStartWidth /
                              timeRemaining};  // 6 seconds for the game

  bool paused{true};

  int score{0};
  Font font;
  if (!font.openFromFile("../fonts/KOMIKAP_.ttf")) {
    std::cerr << "Error loading font" << std::endl;
    return 1;  // or handle the error appropriately
  }

  Text messageText{font};
  Text scoreText{font};

  messageText.setFont(font);
  scoreText.setFont(font);

  messageText.setString("Press Enter to start!");
  scoreText.setString("Score = 0");
  messageText.setCharacterSize(75);
  scoreText.setCharacterSize(100);
  messageText.setFillColor(Color::White);
  scoreText.setFillColor(Color::White);

  // Position the text
  FloatRect textRect = messageText.getLocalBounds();
  messageText.setOrigin({textRect.position.x + textRect.size.x / 2.0f,
                         textRect.position.y + textRect.size.y / 2.0f});
  messageText.setPosition({1920 / 2.0f, 1080 / 2.0f});
  scoreText.setPosition({20, 20});

  // Seed random number generator once
  srand(static_cast<unsigned>(time(0)));

  // Prepare 5 branches
  Texture textureBranch;
  if (!textureBranch.loadFromFile("../graphics/branch.png")) {
    std::cerr << "Failed to load branch.png\n";
    return 1;
  }
  // Set the texture for each branch sprite
  for (int i = 0; i < NUM_BRANCHES; i++) {
    branches[i] = std::make_unique<Sprite>(textureBranch);
    branches[i]->setPosition({-2000, -2000});  // Start off-screen
    // Set the sprite's origin to the center
    // We can then spin it around without changing its position
    branches[i]->setOrigin({220, 20});
  }

  // Main game loop
  while (window.isOpen()) {
    while (auto event = window.pollEvent()) {
      if (event->is<Event::Closed>()) {
        window.close();
      }
      if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
        paused = false;

        // Reset the game state
        score = 0;
        timeRemaining = 6.0f;
      }

      if (const auto* keyPressed = event->getIf<Event::KeyPressed>()) {
        if (keyPressed->code == Keyboard::Key::Escape) {
          window.close();
        }
      }
    }
    if (!paused) {
      Time dt = clock.restart();

      // Subtract from the time remaining
      timeRemaining -= dt.asSeconds();
      timeBar.setSize({timeBarWidthPerSecond * timeRemaining, timeBarHeight});
      if (timeRemaining <= 0.0f) {
        // Pause the game
        paused = true;
        messageText.setString("Out of time!");
        FloatRect textRect = messageText.getLocalBounds();
        messageText.setOrigin({textRect.position.x + textRect.size.x / 2.0f,
                               textRect.position.y + textRect.size.y / 2.0f});

        messageText.setPosition({1920 / 2.0f, 1080 / 2.0f});
      }

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
          spriteClouds[i].setPosition({spriteClouds[i].getPosition().x +
                                           (cloudSpeed[i] * dt.asSeconds()),
                                       spriteClouds[i].getPosition().y});
          // Has the cloud reached the right hand edge of the screen?
          if (spriteClouds[i].getPosition().x > 1920) {
            // Set it up ready to be a whole new cloud next frame
            cloudActive[i] = false;
          }
        }
      }

      stringstream ss;
      ss << "Score = " << score;
      scoreText.setString(ss.str());

      for (int i = 0; i < NUM_BRANCHES; i++) {
        float height = static_cast<float>(i * 150);
        if (branchPositions[i] == side::Left)  // Note: "Left" not "LEFT"
        {
          // Move the sprite to the left side
          branches[i]->setPosition(
              {610.f, height});  // Use -> and {} for position
          // Flip the sprite round the other way
          branches[i]->setRotation(
              sf::radians(180.f));  // SFML 3.0 uses radians
        } else if (branchPositions[i] ==
                   side::Right)  // Note: "Right" not "RIGHT"
        {
          // Move the sprite to the right side
          branches[i]->setPosition(
              {1330.f, height});  // Use -> and {} for position
          // Set the sprite rotation to normal
          branches[i]->setRotation(sf::radians(0.f));  // SFML 3.0 uses radians
        } else {
          // Hide the branch
          branches[i]->setPosition(
              {3000.f, height});  // Use -> and {} for position
        }
      }
    }

    window.clear();
    window.draw(spriteBackground);
    window.draw(spriteClouds[0]);
    window.draw(spriteClouds[1]);
    window.draw(spriteClouds[2]);
    for (int i = 0; i < NUM_BRANCHES; i++) {
      window.draw(*branches[i]);
    }
    window.draw(spriteTree);
    window.draw(spriteBee);
    window.draw(scoreText);
    window.draw(timeBar);
    if (paused) {
      window.draw(messageText);
    }

    window.display();
  }

  return 0;
}

void updateBranches(int seed) {
  // Move all branches down one place
  for (int j = NUM_BRANCHES - 1; j > 0; j--) {
    branchPositions[j] = branchPositions[j - 1];
  }
  srand((int)time(0) + seed);
  int r = (rand() % 5);
  switch (r) {
    case 0:
      branchPositions[0] = side::Left;
      break;
    case 1:
      branchPositions[0] = side::Right;
      break;
    default:
      branchPositions[0] = side::None;
      break;
  }
}