#include <SFML/Graphics.hpp>
#include <optional>

int main() {
    // Create a window with VideoMode using Vector2u
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Timber");

    // Main loop
    while (window.isOpen()) {
        // Poll events using std::optional<sf::Event>
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // Clear the window
        window.clear(sf::Color::Black);

        // Draw a rectangle (tree placeholder)
        sf::RectangleShape tree(sf::Vector2f(100.f, 300.f));
        // Define brown color manually (RGB: 139, 69, 19)
        tree.setFillColor(sf::Color(139, 69, 19));
        tree.setPosition(sf::Vector2f(350.f, 300.f));
        window.draw(tree);

        // Display the window
        window.display();
    }

    return 0;
}