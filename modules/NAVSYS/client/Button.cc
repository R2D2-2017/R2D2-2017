#include <Button.hh>

Button::Button(sf::Vector2f position, sf::Vector2f size, std::string name) :
	position(position),
	size(size),
	name(name)
{
	if(
		!unpressedButtonTexture.loadFromFile(
				"../bin/images/Unpressed-Button.png",
				sf::IntRect(int(position.x), int(position.y), int(size.x), int(size.y))
			) ||
		!pressedButtonTexture.loadFromFile(
				"../bin/images/Unpressed-Button.png",
				sf::IntRect(int(position.x), int(position.y), int(size.x), int(size.y))
			)
		){
		std::cout << "Could not load button.\n";
	}
	unpressedButtonTexture.setSmooth(true);
	unpressedButton.setTexture(unpressedButtonTexture);
	unpressedButton.setPosition(position);
	pressedButtonTexture.setSmooth(true);
	pressedButton.setTexture(pressedButtonTexture);
	pressedButton.setPosition(position);
	
	if (!font.loadFromFile("../bin/fonts/arial.ttf")) {
		std::cout << "Could not load font.\n";
	}
	buttonText.setFont(font);
	buttonText.setPosition(position);
	buttonText.setString(name);
	
}

const void Button::draw(sf::RenderWindow & window) {
	window.draw(isFocused ? pressedButton : unpressedButton);
	window.draw(buttonText);
}

void Button::setFocus(bool b) {
	isFocused = b;
}

bool Button::getFocus() {
	return isFocused;
}