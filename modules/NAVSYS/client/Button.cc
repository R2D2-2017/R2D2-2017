#include "Button.hh"

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

sf::IntRect Button::getBounds() {
	sf::IntRect boundingBox(position.x, position.y, size.x, size.y);
	return boundingBox;
}


void Button::setSize(sf::Vector2f newSize){
	size = newSize;
}
void Button::setText(std::string newText){
	name = newText;
}
void Button::setPosition(sf::Vector2f newPosition){
	position = newPosition;
}


sf::Vector2f Button::getPosition(){
	return position;
}
std::string Button::getText(){
	return name;
}
sf::Vector2f Button::getSize(){
	return size;
}

