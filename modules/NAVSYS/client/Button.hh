#include <iostream>
#include <SFML\Graphics.hpp>
#include "Mouse.hh"

class Button {
private:
    sf::RenderWindow & window;
    sf::Vector2f position;
    sf::Vector2f size;
    int id;
    bool isFocused = false;
    std::string fontName = "../client/arial.ttf";
    sf::Font font;
    sf::Text buttonText;
    sf::RectangleShape button;
    
public:
    Button(sf::RenderWindow & window, sf::Vector2f position, sf::Vector2f size, int id, std::string text);
    const void draw();
    void setFocus(bool b);
    bool getFocus();
    
    void setSize(sf::Vector2f newSize);
    void setText(std::string newText);
    void setPosition(sf::Vector2f newPosition);
    void setFont(std::string newFont);

    bool isPressed();
    
    sf::Vector2f getPosition();
    int getId();
    sf::Vector2f getSize();
    sf::FloatRect getBounds();
};