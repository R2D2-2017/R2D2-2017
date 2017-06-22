/**
 * \file      button.hh
 * \brief     This class will let a button appear in a SFML window.
 * \author    Rene de Kluis, Koen de Groot
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include <SFML/Graphics.hpp>

enum class buttonCommand {ShutDown,StartNode,EndNode};

class Button {
private:
    sf::RenderWindow & window;
    sf::Vector2f position;
    sf::Vector2f size;
    buttonCommand id;
    bool isFocused = false;
    bool isVisable;
    
    bool pressedState = false;
    std::string fontName = "../client/arial.ttf";
    sf::Font font;
    sf::Text buttonText;
    sf::RectangleShape button;
    const float outlineThickness = 2;
    float xScaleDivider = 20;
    float yScaleDivider = 2;

public:
    /**
     * \brief Constructor
     *
     * \param[in]        window      The SFML window
     * \param[in]        position    Position of the button (x,y)
     * \param[in]        size        Size of the button (x,y)
     * \param[in]        id          ID of the button
     * \param[in]        text        Displaytext what comes on the button
     * \param[in]        isVisable   Set the visability of the button, default
     *                               is that the button will be visable, so 
     *                               the default value is true
     */
    Button(sf::RenderWindow & window, sf::Vector2f position, sf::Vector2f size, 
           buttonCommand id, std::string text, bool isVisable = true);
    
    /**
     * \brief Draw the button on the window.
     *
     * This function will draw the button on the window.
     * The button will appear blue if the button is pressed, otherways it 
     * appears white.
     */
    void draw();

    /**
     * \brief Make the button blue.
     *
     * This function sets the button as if it is pressed.
     * The next time the button is drawn it will appear in a pressed state.
     * 
     * \param[in]   b   Boolean to set the state of the button.
     * 
     */
    void setState(bool b);

    /**
     * \brief Set the size of the button.
     *
     * \param[in]    newSize      The new size of the button
     */
    void setSize(sf::Vector2f newSize);

    /**
     * \brief Set the displaytext of the button.
     *
     * \param[in]    newText      The new text to appear on the button.
     */
    void setText(std::string newText);

    /**
     * \brief Set the position of the button.
     *
     * \param[in]    newPosition      The new position of the button.
     */
    void setPosition(sf::Vector2f newPosition);

    /**
     * \brief Set the font of the button.
     *
     * \param[in]    newSize      The new font of the displaytext on the button.
     */
    void setFont(std::string newFont);

    /**
     * \brief Set the visablility of the button.
     *
     * \param[in]    visable      Visability: True for visable, False for 
     *                            invisable.
     */
    void setVisable(bool visable);

    /**
     * \brief Check if the button is pressed.
     *
     * \return This function returns True if the button is pressed, otherwise it
     *         will return False.
     */
    bool isPressed();

    /**
     * \brief Get the position of the button.
     *
     * \return The position of the button
     */
    sf::Vector2f getPosition();

    /**
     * \brief Get the ID of the button.
     *
     * \return The ID of the button
     */
    buttonCommand getId();

    /**
     * \brief Get the size of the button.
     *
     * \return The size of the button
     */
    sf::Vector2f getSize();

    /**
     * \brief Get the global bounds of the button.
     *
     * The bounds of the buttons are recieved of the globalbounds 
	 * of an SFML float rectangle. 
     * {X, Y, Height, Width}
     *
     * \return The global bounds of the button
     */
    sf::FloatRect getBounds();
};
