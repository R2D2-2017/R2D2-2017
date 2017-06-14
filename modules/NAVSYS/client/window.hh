/**
 * \file
 * \brief     this file constains a class that adds a view to the rf::RenderWindow
 * \author    Stefan de Beer
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include "SFML/Graphics.hpp"

/**
 *\brief This class adds a viewport to sf::REndewrWindow
 */
class Window : public sf::RenderWindow{
private:
    sf::View view;
public:
    /**
     * \brief The constructor for creating a window
     * \param[in] mode  the video mode to use
     * \param[in] title the window title
     * \param[in] style the window style to use
     */
    Window(sf::VideoMode mode, const sf::String title, sf::Uint32 style = sf::Style::Default);

    /**
     *\brief initializes the viewport
     *\param[in] center on what point the viewport schould be centerted
     *\param[in] size   the horizontal and vertical size of the viewport
     */
    void setViewPort(const sf::Vector2f center, const sf::Vector2f size);

    /**
     *\brief a function for moving the viewport 
     *\param[in] distance the distance the viewport should be moved
     */
    void moveViewPort(const sf::Vector2f distance);
    /**
     *\brief a function for moving the viewport 
     *\param[in] distance the distance the viewport should be moved
     */
    void moveViewPort(const sf::Vector2i distance);

    /**
     *\brief a function fow moving the viewport to a position
     *\param[in] pos the position the viewport should move to
     */ 
    void setViewPos(const sf::Vector2f pos);
    /**
     *\brief a function fow moving the viewport to a position
     *\param[in] pos the position the viewport should move to
     */
    void setViewPos(const sf::Vector2i pos);
    /**
     *\brief a function for applying the changes made to the viewport
     */
    void updateView();
};



