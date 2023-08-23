#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "player.h"
#include "moves.h"

class Enemy : public Moves
{
protected:
    int chanceturn = 0;
    bool isCollide = false;
    int n = 0;
    sf::Texture textureenemy;
    sf::Sprite spriteenemy;
    char enemyImages[5][100] = {"images/van.png", "images/taxi.png", "images/semi_trailer.png", "images/pickup_truck.png"};
    int count = 0;

public:
    void create_Enemy()
    {
        n = 0;
        // no repetation
        textureenemy.setRepeated(false);

        //    loading the car image
        if (!textureenemy.loadFromFile(enemyImages[count]))
        {
            std::cout << "Error in loading the page " << std::endl;
        }
        count++;
        spriteenemy.setTexture(textureenemy);

        // random number logic
        int diff = 306 + 14;
        int a = rand() % diff + 230;
        ;

        // setting up the sprite position
        spriteenemy.setPosition(sf::Vector2f(1600, a));

        if (count > 3)
        {
            count = 0;
        }
        else
        {
            count++;
        }
    }

    void move_Enemy()
    {

        if (sprite.getGlobalBounds().intersects(spriteenemy.getGlobalBounds()))
        {
            while (n == 0)
            {
                chanceturn++;
                isCollide = true;
                std::cout << chanceturn;

                std::cout << "game over";
                n = 1;
            }
        }
        else
        {

            spriteenemy.move(sf::Vector2f(-12, 0));
            isCollide == false;
        }

        if (spriteenemy.getPosition().x == -80)
        {
            spriteenemy.move(sf::Vector2f(1600, 230));
            create_Enemy();
        }
    }

    sf::Sprite return_Enemy()
    {
        return spriteenemy;
    }
};
