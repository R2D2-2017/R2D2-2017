#include "Button.hh"

Button::Button(sf::RenderWindow & window, sf::Vector2f position, sf::Vector2f size, int id, std::string text) :
    window(window),
    position(position),
    size(size),
    id(id)
{
    button.setSize(size);
    button.setOutlineColor(sf::Color::Red);
    button.setOutlineThickness(2);
    button.setPosition(position);
    
    if (!font.loadFromFile(fontName)) {
        std::cout << "Requested font could not be loaded.\n";
    }
    buttonText.setFont(font);
    buttonText.setPosition(position);
    buttonText.setString(text);
    buttonText.setColor(sf::Color::Black);
    buttonText.setScale(
        float(((1 / buttonText.getGlobalBounds().width) * (size.x-(size.x/20)))),
        float((1 / buttonText.getGlobalBounds().height) * size.y/2)
    );
}

const void Button::draw() {
    if (isFocused) {
        button.setFillColor(sf::Color::Blue);
    }
    window.draw(button);
    button.setFillColor(sf::Color::White);
    window.draw(buttonText);
}

void Button::setFocus(bool b) {
    isFocused = b;
}

bool Button::getFocus() {
    return isFocused;
}

sf::FloatRect Button::getBounds() {
    sf::FloatRect boundingBox(position.x, position.y, size.x, size.y);
    return boundingBox;
}


void Button::setSize(sf::Vector2f newSize){
    size = newSize;
}
void Button::setText(std::string newText){
    buttonText.setString(newText);
}
void Button::setPosition(sf::Vector2f newPosition){
    position = newPosition;
}

void Button::setFont(std::string newFont) {
    font.loadFromFile(newFont);
}

bool Button::isPressed() {
    if (GetMouseClick()) {
        if (getBounds().contains(getMousePosition(window))) {
            if (button.getFillColor().a > 0) {
                isFocused = true;
                return true;
            }
        }
    }
    isFocused = false;
    return false;
}

sf::Vector2f Button::getPosition(){
    return position;
}
int Button::getId(){
    return id;
}
sf::Vector2f Button::getSize(){
    return size;
}

