#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "player.h"
#include "moves.h"
#include "enemy.h"


class Menu : public Enemy
{
protected:
    sf::Texture texturemenu;
    sf::Sprite spritemenu;
    bool showmenu = false;

public:
    void setmenu()
    {

        // setting up the texture
        texturemenu.setRepeated(true);
    

        // loading the texture
        if (!texturemenu.loadFromFile("images/lalalal.jpg"))
        {
            std::cout << "Error in loading the page " << std::endl;
        }
        //  spritemenu.setPosition(0, 0);
        spritemenu.setTexture(texturemenu);
    }

    sf::Sprite return_menu()
    {
        return spritemenu;
    }

    void togglemenu()
    {
        if (showmenu)
        {
            showmenu = false;
        }
        else
        {
            showmenu = true;
        }
    }

    bool return_showmenu()
    {
        return showmenu;
    }
};