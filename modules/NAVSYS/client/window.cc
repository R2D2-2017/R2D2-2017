#include "window.hh"

Window::Window(sf::VideoMode mode, const sf::String title, sf::Uint32 style):
    sf::RenderWindow(mode, title),
    windowSize(mode.width, mode.height)
{}

void Window::setViewPort(const sf::Vector2f size, const sf::Vector2f center){
    view.setSize(size.x, size.y);
    view.setCenter(center);
    setView(view);
}

void Window::setViewPos(const sf::Vector2f pos){
    view.setCenter(sf::Vector2f((int)pos.x, (int)pos.y));
    setView(view);
}

void Window::moveViewPort(const sf::Vector2f distance){
    view.move(distance);
}

void Window::moveViewPort(const sf::Vector2i distance){
    moveViewPort(sf::Vector2f((float)distance.x, (float)distance.y));
}

void Window::updateView(){
    setView(view);
}
