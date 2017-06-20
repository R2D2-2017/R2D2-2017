/**
* \file      message-box.hh
* \brief     Class that gives runtime information on the SFML-window.
* \author    Rene de Kluis
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See ../../LICENSE
*/

#pragma once

#include <SFML/Graphics.hpp>


class MessageBox {
private:
    sf::RenderWindow & window;
    sf::Vector2f position;

    sf::Text messageText;
    sf::Font font;
    sf::Clock clock;

    std::string fontName = "../client/arial.ttf";
    std::string message = "Succesfully started up";

public:


    /**
     * \brief Constructor.
     *
     * \param[in]    window      The SFML-window
     * \param[in]    position    The position of the messagebox on the SFML-window   
     *
     */
    MessageBox(sf::RenderWindow & window, sf::Vector2f position);


    /**
     * \brief Draw the messagebox.
     *
     * This function will draw the messagebox on the SFML-window.
     *
     */
    void draw();


    /**
     * \brief Set a new message.
     *
     * This function will set a new message that must appear in the messagebox.
     *
     * \param[in]    newMessage      The new message that must appear in the messagebox
     *
     */
    void setMessage(std::string newMessage);

};
