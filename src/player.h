#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
class Player
{
protected:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Music music;

public:
    // set the texture
    void set_Texture()
    {
        if (!music.openFromFile("sounds/background.mp3"))
        {
            std::cout << "ERROR ERROR :" << std::endl;
        }

        music.play();

        // setting up the texture
        texture.setRepeated(false);

        // loading the texture
        if (!texture.loadFromFile("images/car.png"))
        {
            std::cout << "Error in loading the page " << std::endl;
        }
        sprite.setOrigin(sf::Vector2f(-500, -300));

        sprite.setTexture(texture);
    }

    sf::Sprite returnme()
    {
        return sprite;
    }
};
