/**
 * \file
 * \author    Stefan de Beer
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "window.hh"

Window::Window(sf::VideoMode mode, const sf::String title, sf::Uint32 style):
    sf::RenderWindow(mode, title)
{}

void Window::setViewPort(const sf::Vector2f size, const sf::Vector2f center){
    view.setSize(size.x, size.y);
    view.setCenter(center);
}

void Window::setViewPos(const sf::Vector2f pos){
    view.setCenter(sf::Vector2f((int)pos.x, (int)pos.y));
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
