
#include "Mouse.hh"

sf::Vector2f Vector2fFromVector2i(sf::Vector2i vector) {
    return sf::Vector2f(static_cast<float>(vector.x), static_cast<float>(vector.y));
}

sf::Vector2f getMousePosition(sf::RenderWindow & window) {
    return Vector2fFromVector2i(sf::Mouse::getPosition(window));
}
bool GetMouseClick() {
    return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

