/**
 * \file
 * \brief     This file constains a class that adds a view to the
 *            sf::RenderWindow.
 * \author    Stefan de Beer
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include <SFML/Graphics.hpp>

/**
 * \brief This class adds a viewport to sf::REndewrWindow.
 */
class Window : public sf::RenderWindow{
private:
    sf::View view;
public:
    /**
     * \brief The constructor for creating a window.
     *
     * \param[in] mode  The video mode to use
     * \param[in] title The title of the window instance
     * \param[in] style The window style to use
     */
    Window(sf::VideoMode mode, const sf::String title,
           sf::Uint32 style = sf::Style::Default);

    /**
     * \brief Initializes the viewport
     *
     * \param[in] center On what point the viewport should be centered.
     * \param[in] size   The horizontal and vertical size of the viewport.
     */
    void setViewPort(const sf::Vector2f center, const sf::Vector2f size);

    /**
     * \brief A function for moving the viewport. This function accepts
     * a sf::Vector2f containing the distance.
     *
     * \param[in] distance The distance the viewport should be moved.
     */
    void moveViewPort(const sf::Vector2f distance);

    /**
     * \brief A function for moving the viewport. This function accepts
     * a sf::Vector2i containing the distance.
     *
     * \param[in] distance The distance the viewport should be moved.
     */
    void moveViewPort(const sf::Vector2i distance);

    /**
     * \brief A function for moving the viewport to a certain position. This
     * function accepts a sf::Vector2f containing the position.
     *
     * \param[in] pos The position the viewport should move to.
     */
    void setViewPos(const sf::Vector2f pos);

    /**
     * \brief A function for moving the viewport to a certain position. This
     * funtion accepts a sf::Vector2i containing the position.
     *
     * \param[in] pos The position the viewport should move to.
     */
    void setViewPos(const sf::Vector2i pos);

    /**
     * \brief A function for applying the changes made to the viewport.
     */
    void updateView();

    /**
     * \brief Returns the view of the window.
     *
     * \return The view of the window
     */
    sf::View getViewPort();
};
