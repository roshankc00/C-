#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "player.h"
class Moves : public Player
{

public:
    void move_left()
    {
        if (sprite.getPosition().y > -14)
        {

            sprite.move(sf::Vector2f(0, -4));
        }
    }
    void move_right()
    {
        if (sprite.getPosition().y < 306)
        {

            sprite.move(sf::Vector2f(0, 4));
        }
    }
};
