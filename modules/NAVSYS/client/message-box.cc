#include "message-box.hh"





MessageBox::MessageBox(sf::RenderWindow & window, sf::Vector2f position, sf::View viewPort):
    window(window),
    position(position),
    viewPort(viewPort)
{
    if (!font.loadFromFile(fontName)) {
        std::cerr << "Requested font could not be loaded.\n";
    }
    messageText.setFont(font);
    messageText.setPosition(position);
    messageText.setString(message);
    messageText.setColor(sf::Color::White);
}


void MessageBox::update(){
    messageText.setString(message);
    window.draw(messageText);
}

void MessageBox::setMessage(std::string newMessage) {
    message = newMessage;
}

