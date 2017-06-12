#include <iostream>
#include <SFML\Graphics.hpp>

class Button {
private:
	sf::Vector2f position;
	sf::Vector2f size;
	std::string name;
	bool isFocused = false;
	sf::Font font;
	sf::Text buttonText;

	sf::Texture unpressedButtonTexture;
	sf::Texture pressedButtonTexture;
	sf::Sprite pressedButton;
	sf::Sprite unpressedButton;
public:
	Button(sf::Vector2f position, sf::Vector2f size, std::string name);
	const void draw(sf::RenderWindow & window);
	void setFocus(bool b);
	bool getFocus();

};