#include "window.hh"

Window::Window(sf::VideoMode mode, const sf::String title):
    sf::RenderWindow(mode, title),
    windowSize(mode.width, mode.height)
{}

void Window::setViewPort(sf::Vector2f size, sf::Vector2f center){
    view.setSize(size.x, size.y);
    view.setCenter(center);
    setView(view);
}

void Window::setViewPos(sf::Vector2f pos){
    view.setCenter(sf::Vector2f((int)pos.x, (int)pos.y));
    setView(view);
}

